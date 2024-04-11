int relay = 13;
int sensor = 3;

unsigned long previousMillis = 0;    // Stores the last time the variable was updated
unsigned long interval = 1000;       // Interval (in milliseconds) at which the variable will increment

int minute = 0;
int second = 0;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  digitalWrite(relay, LOW);
}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  // Check if it's time to increment the variable and print
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time the variable was updated
    second++;             // Increment the variable
    Serial.print("Second: ");
    Serial.println(second);
  }

  // Check if 2 minutes have passed, then execute the action
  if (second >= 60) {
    Serial.println("Minute passed");
    minute++;
    second = 0;
  }

  if (minute >= 1) {
    // Serial.println("Deactivate relay");
    // will turn off the relay
    digitalWrite(relay, HIGH);
    minute = 0;
  }


  int val = digitalRead(sensor);
  if (val == HIGH) {    // detect movement
    // Serial.println("Activate relay");
    digitalWrite(relay, LOW);
    second = 0;
    minute = 0;
  }

}
