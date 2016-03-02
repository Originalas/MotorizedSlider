/* 
 *  Double Rail Easy Motorized Camera Slider Control
 *  Video https://www.youtube.com/watch?v=GOIA8eYxm0Q
*/

  //buttons ///////////////////////////////////////////////////////////////
int inPin = 12;         // the number of the input pin
int inPin2 = 11;  
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;  // the current reading from the input pin
int button2; 
int previous = LOW;    // the previous reading from the input pin
int previous2 = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.

//button
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

//motor
#include <Stepper.h>
int oneway;                      // counter for steps
int onerev = 5000;               // number of steps each direction (edit this for your particular motor)
int microSecDelay = 100;          // delay between steps and speed of the motor  (about as fast as the system can react, higher number = slower)
int microSecDelayStepSpeed = 1000; //turn speed delay, higher -> slower turn
int dirPin = 8;                  // output pin for stepper motor direction
int stepPin = 9;                 // output pin for the pin used to step the motor 
int turn = LOW;

void setup() {
  //buttons ///////////////////////////////////////////////////////////////
  
  pinMode(inPin, INPUT_PULLUP);
  pinMode(inPin2, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);

  //buttons ///////////////////////////////////////////////////////////////
  //mottor ///////////////////////////////////////////////////////////////

  pinMode(dirPin, OUTPUT);       // Assign output mode to pin for direction
  pinMode(stepPin, OUTPUT);      // Assign output mode to pin for setp
  digitalWrite(dirPin, LOW);     // Initialize dir pin 
  digitalWrite(stepPin, LOW);    // Initialize step pin
  oneway = 1;

  //motor  ///////////////////////////////////////////////////////////////
}

void loop()
{

  //buttons ///////////////////////////////////////////////////////////////
  
  reading = digitalRead(inPin);
  button2 = digitalRead(inPin2);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

 // if (button2 == LOW){
      // If button pushed, turn LED on
   //  turn = HIGH;
 // } else {turn = LOW;}


   if (button2 == HIGH && previous2 == LOW && millis() - time > debounce) {
    if (turn == HIGH)
      turn = LOW;
    else
      turn = HIGH;

    time = millis();    
  }

    previous2 = button2;
  
  digitalWrite(outPin, state);
  digitalWrite(dirPin, state);

  previous = reading;
  

  //buttons ///////////////////////////////////////////////////////////////

  //motor ///////////////////////////////////////////////////////////////

  if (turn == HIGH){ 
    digitalWrite(stepPin, HIGH);       // Step motor
    delayMicroseconds(microSecDelay);  // Wait microseconds
    digitalWrite(stepPin, LOW);        // Step motor
    delayMicroseconds(microSecDelay);  // Wait microseconds
    delayMicroseconds(microSecDelayStepSpeed);  // Waint between steps - turn speed
  } else {
    delayMicroseconds(microSecDelayStepSpeed);  // Step speed  
    }
     
  //motor ///////////////////////////////////////////////////////////////
 
}

