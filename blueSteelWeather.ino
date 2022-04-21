
#define WIND_DIR_PIN A5
#define WIND_SPEED_PIN 2
#define WATER_PIN 3

int rawWindDir = 0;
int rawWindSpeed = 0;
int rawWater = 0;
int wind_debounce_timer = 0;
int last_wind_event = 0;
int current_wind_event = 0;
int volatile windCount = 0;

void setup() {
  pinMode(WIND_DIR_PIN, INPUT);
  pinMode(WIND_SPEED_PIN, INPUT_PULLUP);
  pinMode(WATER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), readWindSpeed, FALLING);

  //Particle.variable("RawWind", rawWindDir);
  //Particle.variable("RawSpeed", rawWindSpeed);
  //Particle.variable("RawWater", rawWater);

}

void loop() {
   Update();
   //Particle.publish("RawWind", string(rawWindDir));
   //Particle.publish("RawSpeed", string(rawWindSpeed));
   //Particle.publish("RawWater", string(rawWater));
}

void Update() {
  rawWindSpeed = analogRead(WIND_DIR_PIN);
  if (digitalRead(WIND_SPEED_PIN) == LOW) {
    rawWindSpeed ++;
  }
  if (digitalRead(WATER_PIN) == LOW) {
    rawWater ++;
  }
}

void readWindSpeed() {
  current_wind_event = millis();
  if (last_wind_event == 0) {
    last_wind_event = current_wind_event;
  }
  if (current_wind_event >= wind_debounce_timer) {
    windCount++;
    
    int period = current_wind_event - last_wind_event;
    wind_debounce_timer = current_wind_event + 10;
  }
}
