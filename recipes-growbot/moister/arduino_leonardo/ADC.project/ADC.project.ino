#define MAX_VAL 600
#define USB_DEBUG
#define AV_ITERATIONS 6


int avVal0 = 0;
int avVal1 = 0;

void setup()
{
#ifdef USB_DEBUG
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
#endif // USB_DEBUG
  Serial1.begin(115200); // open serial port, set the baud rate to 9600 bps
}

void loop()
{
  int valA0 = analogRead(A0);
  int valA1 = analogRead(A1);
  
  if(
#ifdef USB_DEBUG
    Serial.available() || 
#endif // USB_DEBUG  
    Serial1.available() )  //check for any data received
  { 
#ifdef USB_DEBUG
    char received_data0 = Serial.read();  //read received data
#endif // USB_DEBUG    
    char received_data1 = Serial1.read();  //read received data
    if(
#ifdef USB_DEBUG
      received_data0 == '0' || 
#endif // USB_DEBUG
      received_data1 == '0'){
#ifdef USB_DEBUG
      Serial.println(MAX_VAL - avVal0);
#endif // USB_DEBUG
      Serial1.println(MAX_VAL - avVal0);
    }
    else if(
#ifdef USB_DEBUG
      received_data0 =='1' || 
#endif // USB_DEBUG
      received_data1 =='1')
    {
#ifdef USB_DEBUG
      Serial.println(MAX_VAL - avVal1);
#endif // USB_DEBUG    
      Serial1.println(MAX_VAL - avVal1);
    }
    else if(
#ifdef USB_DEBUG
      received_data0 =='2' || 
#endif // USB_DEBUG  
      received_data1 =='2')
    {
#ifdef USB_DEBUG
      Serial.print(MAX_VAL - avVal0);
      Serial.print(",");
      Serial.println(MAX_VAL - avVal1);
#endif // USB_DEBUG 
      Serial1.print(MAX_VAL - avVal0);
      Serial1.print(",");
      Serial1.println(MAX_VAL - avVal1);
    }
#ifdef USB_DEBUG
    else{
      Serial.print("# ");
      Serial.println(received_data0);
      Serial1.print("# ");
      Serial1.println(received_data1);
    }
#endif // USB_DEBUG

      // collect average data
      delay(1000);
      avVal0=(avVal0+valA0)/2;
      avVal1=(avVal1+valA1)/2;
      
  }
}
