
#define WIND_DIR A5
#define WIND_SPEED 2
#define WATER 3

int rawWindDir = 0;
int rawWindSpeed = 0;
int rawWater = 0;

void setup() {
  pinMode(WIND_DIR, INPUT);
  pinMode(WIND_SPEED, INPUT_PULLUP);
  pinMode(WATER, INPUT_PULLUP);

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
  rawWindSpeed = analogRead(WIND_DIR);
  if (digitalRead(WIND_SPEED) == LOW) {
    rawWindSpeed ++;
  }
  if (digitalRead(WATER) == LOW) {
    rawWater ++;
  }
}
