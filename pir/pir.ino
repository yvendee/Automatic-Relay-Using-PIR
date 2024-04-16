int relay = 13;
int sensor = 3; // outside sensor
int sensor1 = 4; // inside sensor
int mode = 0;

unsigned long previousMillis = 0;    // Stores the last time the variable was updated
unsigned long interval = 1000;       // Interval (in milliseconds) at which the variable will increment

int minute = 0;
int second = 0;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(sensor1,INPUT);
  Serial.begin(9600);
  digitalWrite(relay, HIGH);

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

    minute = 0;
  }

 // outside
  int val = digitalRead(sensor);
  if (mode == 0) {
    if (val == HIGH) {    // detect movement
      mode = 1;
    }
  }

 // inside
  int val1 = digitalRead(sensor1)
  if (mode == 1) {
   if (val1 == HIGH) {    // detect movement
     mode = 2;
   }
  }

   if (mode == 2) {
      digitalWrite(relay, LOW); // activate relay
      mode = 3;
   }

   if (mode == 3) {
     if (val1 == HIGH) {    // inside detect movement
        mode = 4;
     }
   }

   if(mode == 4) {
      if (val == HIGH) {    // outside detect movement
        mode = 5;
     }
   }

   if (mode == 5) {
     digitalWrite(relay, HIGH); // deactivate relay
     mode = 0;
   }

}