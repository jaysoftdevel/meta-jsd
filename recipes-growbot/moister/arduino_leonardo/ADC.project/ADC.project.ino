#define MAX_VAL 600
char received_data;

int i=0;

void setup()
{
  //Serial1.begin(9600); // open serial port, set the baud rate to 9600 bps
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}

void loop()
{
  int valA0 = analogRead(A0);
  int valA1 = analogRead(A1);
  if(Serial.available()>0 || Serial1.available()>0 )  //check for any data received
  { 
    int received_data0 = Serial.read();  //read received data
    char received_data1 = Serial1.read();  //read received data
    if(received_data0 == '0' || received_data1 == '0'){
      Serial1.write(MAX_VAL - valA0);
      Serial.write(MAX_VAL - valA0);
    }
    else if(received_data0 =='1' || received_data1 =='1')
    {
      Serial.write(MAX_VAL - valA1);
      Serial1.write(MAX_VAL - valA1);
    }
    else if(received_data=='2' || received_data1 =='2')
    {
      Serial.write(MAX_VAL - valA0);
      Serial.write(",");
      Serial.write(MAX_VAL - valA1);
    
      Serial1.write(MAX_VAL - valA0);
      Serial1.write(",");
      Serial1.write(MAX_VAL - valA1);
    }
    else{
      Serial.write(received_data0);
      Serial1.write(received_data1);
    }
  }
}
