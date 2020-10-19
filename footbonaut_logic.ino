#define NO_OF_PINS  16

// Globals
const int MIN_TIME = 500;
const int MAX_TIME = 8000;

// Pin Maps
const int controlPin[16] = {22, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 53};
const int triggerType = LOW;// relay type!
int loopDelay = 100; // how long to pause in loop
const int potPin = A0; // location of potentiometer

int value; // potentiometer value
int time_pause; // time to pause based on read

void setup() {
  // Initalize channels 
  for(int i=0; i < NO_OF_PINS; i++)
  {
    pinMode(controlPin[i], OUTPUT);// set pin as output

    // set initial state OFF variable on pin type
    if(triggerType ==LOW){
      digitalWrite(controlPin[i], HIGH); 
    }else{
       digitalWrite(controlPin[i], LOW); 
    }
  }

  // Initalize potentiometer
  pinMode(potPin, INPUT); // 
  randomSeed(analogRead(1)); // set random seed off of analog static

  Serial.begin(9600);// initialize serial monitor with 9600 baud
}

void loop() {

  // Throw a random value 
  int i = random(0, NO_OF_PINS-1);
  
  //Read and save analog value from potentiometer
  value = analogRead(potPin);          
  // Map that to between min/max time
  time_pause = map(value, 0, 1023, MIN_TIME, MAX_TIME);

  // Turn on the relay channel for the duration of time
  channelControl(i, 1,time_pause); 
  // Shut off channel quickly
  channelControl(i, 0, 10); 

 Serial.println("==============="); // logging
 
 // give a short delay between cycles
 delay(loopDelay);
          
}

void channelControl(int relayChannel, int action, int t)
{
  int state =LOW;
  String statTXT =" ON";

  // Mode for LOW type relays
  if(triggerType == LOW)
  {    
    // If Request OFF
    if (action ==0)
    {
      state = HIGH;
      statTXT = " OFF";
    }
  
  }
  
  // Mode for HIGH type relays
  else{
    // If Request ON
    if (action ==1)
    {
      state = HIGH;     
    }
    else{
      statTXT = " OFF";    
    }
  }
  
  // Write to pin
  digitalWrite(controlPin[relayChannel], state);
  // Wait indicated time
  if(t >0 )
  {
    delay(t);
  }

  // Update logs
  Serial.print ("Channel: ");
  Serial.print(relayChannel); 
  Serial.print(statTXT);
  Serial.print(" - "); 
  Serial.println(t);      
}