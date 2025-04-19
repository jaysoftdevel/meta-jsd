#define USB_DEBUG

static int avVal0 = 0;
static int avVal1 = 0;

void setup()
{
#ifdef USB_DEBUG
      Serial.begin(115200);
#endif // USB_DEBUG
      Serial1.begin(115200);
}

void loop()
{
      if (
#ifdef USB_DEBUG
          Serial.available() ||
#endif                         // USB_DEBUG
          Serial1.available()) // check for any data received
      {
             int valA0 = analogRead(A0);
             int valA1 = analogRead(A1);

#ifdef USB_DEBUG
            char received_data0 = Serial.read();  // read received data
#endif                                            // USB_DEBUG
            char received_data1 = Serial1.read(); // read received data
            if (
#ifdef USB_DEBUG
                received_data0 == '0' ||
#endif // USB_DEBUG
                received_data1 == '0')
            {
#ifdef USB_DEBUG
                  Serial.println(valA0);
#endif // USB_DEBUG
                  Serial1.println(valA0);
            }
            else if (
#ifdef USB_DEBUG
                received_data0 == '1' ||
#endif // USB_DEBUG
                received_data1 == '1')
            {
#ifdef USB_DEBUG
                  Serial.println(valA1);
#endif // USB_DEBUG
                  Serial1.println(valA1);
            }
            else if (
#ifdef USB_DEBUG
                received_data0 == '2' ||
#endif // USB_DEBUG
                received_data1 == '2')
            {
#ifdef USB_DEBUG
                  Serial.print(valA0);
                  Serial.print(",");
                  Serial.println(valA1);
#endif // USB_DEBUG
                  Serial1.print(valA0);
                  Serial1.print(",");
                  Serial1.println(valA1);
            }
#ifdef USB_DEBUG
            else
            {
                  Serial.print("# ");
                  Serial.println(received_data0);
                  Serial1.print("# ");
                  Serial1.println(received_data1);
                  return;
            }
#endif // USB_DEBUG

            // collect average data
            //delay(1000);
            // avVal0 = (avVal0 + valA0) / 2;
            // avVal1 = (avVal1 + valA1) / 2;
      }
}
