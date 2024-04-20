int relay = 13;
int sensor = 3; // outside sensor
int sensor1 = 4; // inside sensor
int sensor2 = 5; // middle sensor
volatile int mode = 0;


unsigned long previousMillis = 0;    // Stores the last time the variable was updated
unsigned long interval = 1000;       // Interval (in milliseconds) at which the variable will increment

int minute = 0;
int second = 0;
int people = 0;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
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
    // Serial.println("Minute passed");
    minute++;
    second = 0;
  }

  if (minute >= 1) {
    minute = 0;
  }

  bool val = digitalRead(sensor) == HIGH;     // outside sensor
  bool val1 = digitalRead(sensor1) == HIGH;   // inside sensor
  bool val2 = digitalRead(sensor2) == HIGH;   // middle sensor

  if (mode == 0) {        // first scene
    if (val) {    // first, detect any movement from outside sensor or
    
      mode = 1;
      Serial.println("outside-detect");
    }

    if (val1) {    // detect any movement from insides sensor
      mode = 10;
      Serial.println("inside-detect");
    }
  }


  if (mode == 1) {
    if (val2) {    // if outside sensor has movement, wait to detect movement from middle sensor
     mode = 2;
    }
  }

   if (mode == 2) {
    if (val1) {    // if middle sensor has movement, wait to detect movement from inside sensor
      mode = 3;
    }
   }

   if(mode == 3){
      if (val1 == false) {    // if inside sensor has movement, wait for inside sensor to get low
        mode = 4;
      }
   }


   if (mode == 4) {
      people++;
      Serial.println("count");

      if(people > 200) {
        people = 200;
      }
      mode = 0;            // go back to first scene
   }


   if(mode == 10) {
      if (val2) {    // if inside sensor has movement, wait to detect movement from middle sensor
       mode = 12;
      }
   }

  if (mode == 12) {
    if (val) {    // if middle sensor has movement, wait to detect movement from outside sensor
      mode = 13;
    }
  }

  if(mode == 13){
    if (val == false) {    // if outside sensor has movement, wait for outside sensor to get low
      mode = 14;
    }
  }

  if (mode == 14) {
      people--;
      // Serial.println("count");

      if(people < 0) {
        people = 0;
      }
      mode = 0;            // go back to first scene
  }



  if (people == 0) {
    // Serial.println("relay is off");
    digitalWrite(relay, HIGH); // deactivate relay
  }
  else {
    // Serial.println("relay is on");
    digitalWrite(relay, LOW); // activate relay
  }

}
