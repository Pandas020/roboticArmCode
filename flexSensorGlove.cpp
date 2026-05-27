// Flex Sensor Glove - ESP32 (Elegoo)
// Pins: D26, D34, D35, D33, D27

#define THUMB_PIN   26 // min value 2000
#define POINTER_PIN 34 // min value 2500
#define MIDDLE_PIN  35 // to be tested
#define RING_PIN    33 // min value 2.7k
#define PINKY_PIN   27 // min value 


void setup() {
  Serial.begin(9600); 
}

void loop() {
  int pointer = analogRead(POINTER_PIN);
  int middle  = analogRead(MIDDLE_PIN);
  int ring    = analogRead(RING_PIN);
  int pinky   = analogRead(PINKY_PIN);
  int thumb =   analogRead(THUMB_PIN);

 
  // Serial.print("max: ");
  // Serial.print(4096);
  // Serial.print(" min: ");
  // Serial.print(0);
  Serial.print(", Thumb:   "); Serial.print(thumb);
  Serial.print(", Pointer: "); Serial.print(pointer);
  Serial.print(", Middle:  "); Serial.print(middle);
  Serial.print(", Ring:    "); Serial.print(ring);
  Serial.print(", Pinky:   "); Serial.print(pinky);
  Serial.println();

  delay(1000);
}

//TODO: IMPLEMENT SERIAL READ?
