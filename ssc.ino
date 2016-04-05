#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

const int brakePin = A0;
const int brakeLedPin = 7;
const int rightTurnButtonPin = 2;
const int leftTurnButtonPin = 3;
const int rightTurnLedPin = 4;
const int leftTurnLedPin = 8;
const long blinkInterval = 500;  

int brakeState = 0;
int rightTurnState = 0;
int leftTurnState = 0;

volatile int rightPressed = 0;
volatile int leftPressed = 0;
unsigned long previousRightTime = 0;
unsigned long previousLeftTime = 0;
unsigned long currentTime = 0;

int rightLedState = LOW;
int leftLedState = LOW;

void setup() {
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  pinMode(brakeLedPin, OUTPUT);
  pinMode(brakePin, INPUT);
  pinMode(rightTurnLedPin, OUTPUT);
  pinMode(leftTurnLedPin, OUTPUT);
  pinMode(rightTurnButtonPin, INPUT);
  pinMode(leftTurnButtonPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(rightTurnButtonPin), toggleRight, RISING);
  attachInterrupt(digitalPinToInterrupt(leftTurnButtonPin), toggleLeft, RISING);
}

void loop() {
  
  currentTime = millis();
  
  brakeState = analogRead(brakePin);
  rightTurnState = digitalRead(rightTurnButtonPin);
  leftTurnState = digitalRead(leftTurnButtonPin);

  if(brakeState < 2) {
    digitalWrite(brakeLedPin, LOW);
  }
  else {
    digitalWrite(brakeLedPin, HIGH);
  }

  if(rightPressed % 2 == 0) digitalWrite(rightTurnLedPin, LOW);
  else 
  { 
    flashRight();
  }

  if(leftPressed % 2 == 0) digitalWrite(leftTurnLedPin, LOW);
  else 
  { 
    flashLeft();
  }
  
}

// Logic to flash the right LED
void flashRight() {
  if(currentTime - previousRightTime >= blinkInterval){
    previousRightTime = currentTime;
    
    if (rightLedState == LOW) {
      rightLedState = HIGH;
    } else {
      rightLedState = LOW;
    }
    digitalWrite(rightTurnLedPin, rightLedState);
  }
}

// Logic to flash the left LED
void flashLeft() {
  if(currentTime - previousLeftTime >= blinkInterval){
    previousLeftTime = currentTime;
    
    if (leftLedState == LOW) {
      leftLedState = HIGH;
    } else {
      leftLedState = LOW;
    }
    digitalWrite(leftTurnLedPin, leftLedState);
  }
}

// ISR for right button 
void toggleRight() {
  if(leftPressed % 2 != 0) leftPressed = 0;  
  rightPressed++;
}

// ISR for left button
void toggleLeft() {
  if(rightPressed % 2 != 0) rightPressed = 0;
  leftPressed++;
}

