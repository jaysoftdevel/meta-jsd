const int AirValue = 520;   //you need to replace this value with Value_1
const int WaterValue = 260;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue0, soilMoistureValue1 = 0;
char received_data;

int i=0;

void setup()
{
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
}

const char* getState(int val){
  if(val > WaterValue && val < (WaterValue + intervals))
  {
    return("Very Wet");
  }
  else if(val > (WaterValue + intervals) && val < (AirValue - intervals))
  {
    return("Wet");
  }
  else if(val < AirValue && val > (AirValue - intervals))
  {
    return("Dry");
  }
  // fallback
  return "";
}

void loop()
{
  if(Serial.available()>0)  //check for any data received
  { 
    received_data = Serial.read();  //read received data      
    if(received_data=='0'){
      soilMoistureValue0 = analogRead(A0);
      Serial.print(soilMoistureValue0);
      Serial.print(",");
      Serial.print(getState(soilMoistureValue0));
      Serial.write('\r');
    }
    else if(received_data=='1')
    {
      soilMoistureValue1 = analogRead(A1);
      Serial.print(soilMoistureValue1);
      Serial.print(",");
      Serial.print(getState(soilMoistureValue1));
      Serial.write('\r');
    }
    else if(received_data=='2')
    {
      soilMoistureValue0 = analogRead(A0);
      soilMoistureValue1 = analogRead(A1);
      Serial.print(soilMoistureValue0);
      Serial.print(",");
      Serial.print(getState(soilMoistureValue0));
      Serial.print(",");
      Serial.print(soilMoistureValue1);
      Serial.print(",");
      Serial.print(getState(soilMoistureValue1));
      Serial.write('\r');
    }
  }
}
