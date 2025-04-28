#define USB_DEBUG
#define ITERATIONS 6

// Pin configuration
const int atomizerPin = 12; // D12

static bool runAtomizer = false;

static int avVal0[ITERATIONS] = {0};
static int avVal1[ITERATIONS] = {0};

// Timing control
unsigned long lastSensorCycleMillis = 0;
unsigned long lastAtomizerStartMillis = 0;
unsigned long atomizerDisableMillis = 0;

const unsigned long sensorReadInterval = 10000;  // 10 seconds between sensor cycles
const unsigned long atomizerRunTime = 7000;     // 7 seconds atomizer on time
const unsigned long atomizerDisableBeforeReadTime = 3000; // 3 second stabilization

bool atomizerActive = false;
bool preparingSensorRead = false;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(atomizerPin, OUTPUT);
    digitalWrite(atomizerPin, HIGH); // Atomizer initially OFF (active low)
}

void loop()
{
    unsigned long currentMillis = millis();

    // Handle serial input always
    checkSerial();

    // Handle atomizer normal run (outside of sensor read preparation)
    if (!preparingSensorRead)
    {
        if (runAtomizer && !atomizerActive)
        {
            digitalWrite(atomizerPin, LOW); // Start atomizer (active low)
            lastAtomizerStartMillis = currentMillis;
            atomizerActive = true;
        }
        else if (atomizerActive && (currentMillis - lastAtomizerStartMillis >= atomizerRunTime))
        {
            digitalWrite(atomizerPin, HIGH); // Turn atomizer OFF
            atomizerActive = false;
        }
    }

    // Handle sensor reading preparation
    if (!preparingSensorRead && (currentMillis - lastSensorCycleMillis >= sensorReadInterval))
    {
        // Time to start disabling atomizer for sensor reading
        preparingSensorRead = true;
        atomizerDisableMillis = currentMillis;
        digitalWrite(atomizerPin, HIGH); // Disable atomizer
    }
    else if (preparingSensorRead && (currentMillis - atomizerDisableMillis >= atomizerDisableBeforeReadTime))
    {
        // Now stabilized, do the sensor reading
        performSensorRead();
        lastSensorCycleMillis = currentMillis;
        preparingSensorRead = false;
    }
}

void checkSerial()
{
    if (Serial.available())
    {
        char received_data = Serial.read();
        handleCommand(received_data);
    }
    else if (Serial1.available())
    {
        char received_data = Serial1.read();
        handleCommand(received_data);
    }
}

void handleCommand(char cmd)
{
    int total0 = 0;
    int total1 = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        total0 += avVal0[i];
        total1 += avVal1[i];
    }
    int avg0 = total0 / ITERATIONS;
    int avg1 = total1 / ITERATIONS;

    if (cmd == '0')
    {
        Serial.println(avg0);
        Serial1.println(avg0);
    }
    else if (cmd == '1')
    {
        Serial.println(avg1);
        Serial1.println(avg1);
    }
    else if (cmd == '2')
    {
        Serial.print(avg0);
        Serial.print(",");
        Serial.print(avg1);
        Serial.print(",");
        Serial.println(runAtomizer);
        Serial1.print(avg0);
        Serial1.print(",");
        Serial1.print(avg1);
        Serial1.print(",");
        Serial1.println(runAtomizer);
    }
    else if (cmd == '3')
    {
        runAtomizer = true;
    }
    else if (cmd == '4')
    {
        runAtomizer = false;
    }
    else
    {
        Serial.print("# ");
        Serial.println(cmd);
        Serial1.print("# ");
        Serial1.println(cmd);
    }
}

void performSensorRead()
{
    int newVal0 = analogRead(A0);
    int newVal1 = analogRead(A1);

    // Shift old values
    for (int i = ITERATIONS - 1; i > 0; i--)
    {
        avVal0[i] = avVal0[i - 1];
        avVal1[i] = avVal1[i - 1];
    }

    // Store newest reading
    avVal0[0] = newVal0;
    avVal1[0] = newVal1;
}
