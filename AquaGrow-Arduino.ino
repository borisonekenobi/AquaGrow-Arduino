const int dry = 595; // value for dry sensor
const int wet = 239; // value for wet sensor

const unsigned int PUMP_PIN = 3;
const unsigned int SENSOR_PIN = A0;

int min = 0;
int max = 80;

void setup() {
  pinMode(PUMP_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) read_cmd(Serial.readString());

  float sensorVal = analogRead(A0);
  float percentageHumidity = ((sensorVal - dry) / (wet - dry)) * 100;

  if (percentageHumidity > 100) percentageHumidity = 100.0;
  if (percentageHumidity < 0) percentageHumidity = 0.0;

  Serial.write(String(percentageHumidity).c_str(), 5);
  
  if (percentageHumidity <= min)
    digitalWrite(PUMP_PIN, HIGH);
  else if (percentageHumidity >= max)
    digitalWrite(PUMP_PIN, LOW);

  delay(1000);
}

void read_cmd(String cmd)
{
  cmd.trim();

  const int splitIndex = cmd.indexOf('<');
  if (splitIndex < 1) return;

  const auto minStr = cmd.substring(0, splitIndex);
  const auto maxStr = cmd.substring(splitIndex + 1, sizeof(cmd));

  if (!is_valid_num(minStr.c_str()) || !is_valid_num(maxStr.c_str())) {return;}

  min = atoi(minStr.c_str());
  max = atoi(maxStr.c_str());
}

bool is_valid_num(const char* str)
{
  for (int i = 0; i < strlen(str); ++i)
    if (!isDigit(str[i])) return false;

  return true;
}
