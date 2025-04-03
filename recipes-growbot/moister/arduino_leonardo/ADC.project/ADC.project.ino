const int AirValue = 520;   //you need to replace this value with Value_1
const int WaterValue = 260;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

void setup()
{
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
}

void loop()
{
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  Serial.print(soilMoistureValue);
  Serial.print(",");
  //Serial.println((WaterValue + intervals));
  //Serial.println((AirValue - intervals));
  
  if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
  {
    Serial.print("Very Wet");
  }
  else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
  {
    Serial.print("Wet");
  }
  else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
  {
    Serial.print("Dry");
  }
  else{
    Serial.print("Optimal moist");
  }
  Serial.write('\r');
  delay(5000);
}
