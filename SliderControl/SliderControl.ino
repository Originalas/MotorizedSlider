/* 
 *  Double Rail Easy Motorized Camera Slider Control
 *  Video https://www.youtube.com/watch?v=GOIA8eYxm0Q
*/

  //buttons ///////////////////////////////////////////////////////////////
int inPin = 12;         // the number of the input pin
int inPin2 = 11;  
int inPin3 = 10; 
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;  // the current reading from the input pin
int button2; 
int button3; 
int previous = LOW;    // the previous reading from the input pin
int previous2 = LOW;    // the previous reading from the input pin
int previous3 = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.

//button
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

//motor
#include <Stepper.h>
unsigned int oneway = 1;                      // counter for steps
unsigned int onerev = 15400;               // limit turns by slider length
int microSecDelay = 100;          // delay between steps and speed of the motor  (about as fast as the system can react, higher number = slower)
int microSecDelayStepSpeed = 1000; //turn speed delay, higher -> slower turn
int speed1 = 1000; //turn speed mode 1 / normal
int speed2 = 10000; //turn speed mode 2 / slow timelapse
int dirPin = 8;                  // output pin for stepper motor direction
int stepPin = 9;                 // output pin for the pin used to step the motor 
int turn = LOW;

void setup() {
  //buttons ///////////////////////////////////////////////////////////////
  
  pinMode(inPin, INPUT_PULLUP); //Assign button pin, turn pullup resitor on
  pinMode(inPin2, INPUT_PULLUP);
  pinMode(inPin3, INPUT_PULLUP);
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
  button3 = digitalRead(inPin3);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  // turn direction button
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

  //start/stop button
   if (button2 == HIGH && previous2 == LOW && millis() - time > debounce) {
    if (turn == HIGH)
  {   
    turn = LOW;
    oneway=1; //reset step count
  }else{
      turn = HIGH;
  }
    time = millis();    
  }

    previous2 = button2;

  //speed button
   if (button3 == HIGH && previous3 == LOW && millis() - time > debounce) {
    if (microSecDelayStepSpeed == speed1)
  {   
      microSecDelayStepSpeed = speed2;
   // oneway=1; //reset step count
  }else{
      microSecDelayStepSpeed = speed1;
  }
    time = millis();    
  }

    previous3 = button3;
  
  digitalWrite(outPin, state);
  digitalWrite(dirPin, state);

  previous = reading;
  

  //buttons ///////////////////////////////////////////////////////////////

  //motor ///////////////////////////////////////////////////////////////

  if (turn == HIGH && oneway < onerev){ 
    digitalWrite(stepPin, HIGH);       // Step motor
    delayMicroseconds(microSecDelay);  // Wait microseconds
    digitalWrite(stepPin, LOW);        // Step motor
    delayMicroseconds(microSecDelay);  // Wait microseconds
    delayMicroseconds(microSecDelayStepSpeed);  // Waint between steps - turn speed
    oneway++; //count steps
  } else {
    delayMicroseconds(microSecDelayStepSpeed);  // Step speed  
 
    }
     
  //motor ///////////////////////////////////////////////////////////////
 
}

