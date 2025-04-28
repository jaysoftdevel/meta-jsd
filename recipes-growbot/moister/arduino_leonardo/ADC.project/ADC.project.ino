#define USB_DEBUG
#define ITERATIONS 10

// Pin configuration
const int atomizerPin = 12; // D12
// State
bool atomizerPin = LOW;

static bool runAtomizer = false;

static int avVal0[ITERATIONS] = {0};
static int avVal1[ITERATIONS] = {0};

void setup()
{
      Serial.begin(115200);
      Serial1.begin(115200);
      pinMode(atomizerPin, OUTPUT);
}

void loop()
{
      int total0 = 0;
      int total1 = 0;

      for (int i = 0; i < ITERATIONS - 1; i++)
      {
            avVal0[i+1] = avVal0[i];
            total0 += avVal0[i+1];
            avVal1[i+1] = avVal1[i];
            total1 += avVal1[i+1];
      }

      // read back into "old" position 0
      avVal0[0] = analogRead(A0);
      avVal1[0] = analogRead(A1);

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
                  Serial.println(total0/ITERATIONS);
                  Serial1.println(total0/ITERATIONS);
            }
            else if (
                received_data0 == '1' ||
                received_data1 == '1')
            {
                  Serial.println(total1/ITERATIONS);
                  Serial1.println(total1/ITERATIONS);
            }
            else if (
                received_data0 == '2' ||
                received_data1 == '2')
            {
                  Serial.print(total0/ITERATIONS);
                  Serial.print(",");
                  Serial.println(total1/ITERATIONS);
                  Serial1.print(total0/ITERATIONS);
                  Serial1.print(",");
                  Serial1.println(total1/ITERATIONS);
            }
            else if (
                  received_data0 == '3' ||
                  received_data1 == '3')
            {
                  runAtomizer = true;
            }

            else if (
                  received_data0 == '4' ||
                  received_data1 == '4')
            {
                  runAtomizer = false;
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
      if(runAtomizer==true){
            // start atomizer
            digitalWrite(atomizerPin, HIGH);
      }
      delay(4000);
      // always set low, before moist measuring to stabelize
      digitalWrite(atomizerPin, LOW);
      delay(1000);
}
