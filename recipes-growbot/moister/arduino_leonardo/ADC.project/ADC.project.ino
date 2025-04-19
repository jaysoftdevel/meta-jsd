#define USB_DEBUG
#define ITERATIONS 10

static int avVal0[ITERATIONS] = {0};
static int avVal1[ITERATIONS] = {0};

void setup()
{
      Serial.begin(115200);
      Serial1.begin(115200);
}

void loop()
{
      int total0 = 0;
      int total1 = 0;

      avVal0[0] = analogRead(A0);
      avVal1[0] = analogRead(A1);
  
      for (int i = ITERATIONS - 1; i > 0; i--)
      {
            avVal0[i] = avVal0[i - 1];
            total0 += avVal0[i];
            avVal1[i] = avVal1[i - 1];
            total1 += avVal1[i];
      }

      // overwrite first entry which gets dropped in each
      // iteation and does not influence the calculation
      avVal0[0] = total0 / (ITERATIONS - 1);
      avVal1[0] = total1 / (ITERATIONS - 1);

      if (
          Serial.available() ||
          Serial1.available()) // check for any data received
      {
            char received_data0 = Serial.read();  // read received data
            char received_data1 = Serial1.read(); // read received data
            if (
                received_data0 == '0' ||
                received_data1 == '0')
            {
                  Serial.println(avVal0[0]);
                  Serial1.println(avVal1[0]);
            }
            else if (
                received_data0 == '1' ||
                received_data1 == '1')
            {
                  Serial.println(avVal0[0]);
                  Serial1.println(avVal1[0]);
            }
            else if (
                received_data0 == '2' ||
                received_data1 == '2')
            {
                  Serial.print(avVal0[0]);
                  Serial.print(",");
                  Serial.println(avVal1[0]);
                  Serial1.print(avVal0[0]);
                  Serial1.print(",");
                  Serial1.println(avVal1[0]);
            }
            else
            {
                  Serial.print("# ");
                  Serial.println(received_data0);
                  Serial1.print("# ");
                  Serial1.println(received_data1);
                  return;
            }
      }
      delay(1000);
}
