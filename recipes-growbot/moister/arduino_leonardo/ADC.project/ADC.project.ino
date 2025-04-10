#define MAX_VAL 600
char received_data;

int i=0;

void setup()
{
  Serial1.begin(115200); // open serial port, set the baud rate to 9600 bps
}

void loop()
{
  if(Serial1.available()>0)  //check for any data received
  { 
    received_data = Serial.read();  //read received data      
    if(received_data=='0'){
      Serial1.println(MAX_VAL - analogRead(A0));
    }
    else if(received_data=='1')
    {
      Serial1.println(MAX_VAL - analogRead(A1));
    }
    else if(received_data=='2')
    {
      Serial1.print(MAX_VAL - analogRead(A0));
      Serial1.print(",");
      Serial1.println(MAX_VAL - analogRead(A1));
    }
    else{
      Serial1.println(received_data);
    }
  }
}
