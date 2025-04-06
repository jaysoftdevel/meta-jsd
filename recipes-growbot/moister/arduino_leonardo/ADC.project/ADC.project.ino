#define MAX_VAL 600
char received_data;

int i=0;

void setup()
{
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
}

void loop()
{
  if(Serial.available()>0)  //check for any data received
  { 
    received_data = Serial.read();  //read received data      
    if(received_data=='0'){
      Serial.println(MAX_VAL - analogRead(A0));
    }
    else if(received_data=='1')
    {
      Serial.println(MAX_VAL - analogRead(A1));
    }
    else if(received_data=='2')
    {
      Serial.print(MAX_VAL - analogRead(A0));
      Serial.print(",");
      Serial.println(MAX_VAL - analogRead(A1));
    }
  }
}
