#define NO_OF_PINS  12
//int outputPins[NO_OF_PINS] = {22, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 53}; currently breaking with 16 channels
int outputPins[NO_OF_PINS] = {30,32,34,36, 39, 41, 43, 45, 47, 49, 51, 53};
int idx = 0;
  
void setup() {
  // use for text output
  // Serial.begin(9600);

  // Use random analog noise for the randomSeed
  randomSeed(analogRead(0));

  // Initalize all pins
  for (int i=0; i < NO_OF_PINS; i++){
    pinMode(outputPins[i], OUTPUT);
  } 
}

void loop() {

  // Select a random pin
  idx = random(0, NO_OF_PINS);
  int pin_to_write = outputPins[idx];

  // write to the pin
  digitalWrite(pin_to_write, HIGH);

  // Wait, turn off, pause quickly to notice repeats
  delay(2000);
  digitalWrite(pin_to_write, LOW);
  delay(100);

}
