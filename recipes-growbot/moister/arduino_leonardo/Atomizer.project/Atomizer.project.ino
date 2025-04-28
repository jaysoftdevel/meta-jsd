// Pin configuration
const int atomizerPin = 12; // D12

// Timing
const unsigned long interval = 5000; // 5 seconds in milliseconds
unsigned long previousMillis = 0;

// State
bool atomizerPin = LOW;

void setup() {
  pinMode(atomizerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if 5 seconds have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // save the last time the pin was toggled

    // Toggle the state
    atomizerPin = !ledState;
    digitalWrite(atomizerPin, ledState);
  }
}
