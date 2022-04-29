
#define WIND_DIR_PIN A5
#define WIND_SPEED_PIN 2
#define WATER_PIN 3

int rawWindDir = 0;
int rawWindSpeed = 0;
int rawWater = 0;
int windTime = 0;
int tempWindTime = 0;
int wind_debounce_timer = 0;
int last_wind_event = 0;
int current_wind_event = 0;
float volatile windCount = 0;
float volatile MPHWind = 0; 

void setup() {
  pinMode(WIND_DIR_PIN, INPUT);
  pinMode(WIND_SPEED_PIN, INPUT_PULLUP);
  pinMode(WATER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), readWindSpeed, FALLING);

  // Declare all my particle variables
  Particle.variable("RawWind", rawWindDir);
  Particle.variable("RawSpeed", rawWindSpeed);
  Particle.variable("RawWater", rawWater);
  Particle.variable("WindSpeed", MPHWind);

}

void loop() {
   Update();
   // Publish all the variables to particle.
   Particle.publish("RawWind", string(rawWindDir));
   Particle.publish("RawSpeed", string(rawWindSpeed));
   Particle.publish("RawWater", string(rawWater));
   Particle.publish("WindSpeed", string(MPHWind));
}

// Update all the variables. 
void Update() {
  rawWindDir = analogRead(WIND_DIR_PIN);
  if (digitalRead(WATER_PIN) == LOW) {
    rawWater ++;
  }
  calcWindSpeed(); 
}

// Take the raw wind data and make it into miles per hour
// I mostly just copied chucks code. I'm really not sure how or if it works.
void calcWindSpeed() {
  windTime = millis() - tempWindTime;
  noInterrupts();
  tempWindTime = millis();
  int tempWindCount = windCount;
  windCount = 0;
  interrupts();
  MPHWind = ((float)tempWindCount * (float)(windTime / 1000)) * 1.492;
}

// Reads in the wind speed raw data everytime the sensor fully rotates
void readWindSpeed() {
  // Get our current time
  current_wind_event = millis();
  // This is just for the first time the program runs or when variables overflow.
  if (last_wind_event == 0) {
    last_wind_event = current_wind_event;
  }
  // Make sure the sensor isn't bouncing and counting twice
  if (current_wind_event >= wind_debounce_timer) {
    // The thing spun around! Keep track of that!
    windCount++;
    rawWindSpeed++
    // Reset the timer
    wind_debounce_timer = current_wind_event + 10;
  }
}
