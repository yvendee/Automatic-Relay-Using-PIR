int relay = 13;
int sensor = 3; // outside sensor
int sensor1 = 4; // inside sensor
int sensor2 = 5; // middle sensor
int mode = 0;

unsigned long previousMillis = 0;    // Stores the last time the variable was updated
unsigned long interval = 1000;       // Interval (in milliseconds) at which the variable will increment

int minute = 0;
int second = 0;
int people = 0;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
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


  int val = digitalRead(sensor);     // outside sensor
  int val1 = digitalRead(sensor1)    // inside sensor
  int val2 = digitalRead(sensor2)    //  middle sensor

  if (mode == 0) {        // first scene
    if (val == HIGH) {    // first, detect any movement from outside sensor or
      mode = 1;
    }

    if (va1l == HIGH) {    // detect any movement from insides sensor
      mode = 10;
    }
  }


  if (mode == 1) {
    if (val2 == HIGH) {    // if outside sensor has movement, wait to detect movement from middle sensor
     mode = 2;
    }
  }

   if (mode == 2) {
    if (va1l == HIGH) {    // if middle sensor has movement, wait to detect movement from inside sensor
      mode = 3;
    }
   }

   if (mode == 3) {
      people++;

      if(people > 200) {
        people = 200;
      }
      mode = 0;            // go back to first scene
   }


   if(mode == 10) {
      if (val2 == HIGH) {    // if inside sensor has movement, wait to detect movement from middle sensor
       mode = 12;
      }
   }

  if (mode == 12) {
    if (va1 == HIGH) {    // if middle sensor has movement, wait to detect movement from outside sensor
      mode = 13;
    }
  }

  if (mode == 13) {
      people--;
      if(people < 0) {
        people = 0;
      }
      mode = 0;            // go back to first scene
   }

   if (people > 0) {
     digitalWrite(relay, LOW); // activate relay
     mode = 0;
   }

  if (people == 0) {
     digitalWrite(relay, HIGH); // deactivate relay
     mode = 0;
   }

}