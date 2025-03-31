const int dry = 595; // value for dry sensor
const int wet = 239; // value for wet sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorVal = analogRead(A0);
 
  float percentageHumididy = (sensorVal - dry) / (wet - dry); 

  Serial.print("Soil Moisture: ");
  Serial.print(percentageHumididy * 100);
  Serial.println("%");
  
  delay(100);
}
