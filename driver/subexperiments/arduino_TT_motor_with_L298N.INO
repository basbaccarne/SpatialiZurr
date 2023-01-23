// code to drive l298n motor driver
// this script makes the driver go trhough the follow sequence: forward, backward, left, right and stop.

// Some notes:
// Mechanum wheel must be placed in a way that the rollers point inwards to the center of the object
// Full mechanum control requires 2 motor drivers to control the 4 motors independently
// In this scenario we work with only 1 motor driver, so we need to make decisions regarding the required movements
// For the SpatialiZurr, We need: forward, backward, left & right
// Therefore, we need to cross-wire out motors (left-back with right-front on control 1 & right-back with left-front on control 2)

// set-up:

// Motor 1: right-front & left-back are on unit 1 (speed controlled by enA) > IN1 & IN2 connected to digital 2 & 3
int motor1pin1 = 2;
int motor1pin2 = 3;
// Motor 2: left-front & right-back are on unit 2 (speed controlled by enB) > IN3 & IN4 connected to digital 4 & 5
int motor2pin1 = 4;
int motor2pin2 = 5;
// Speed controls are on digital 9 & digital 10
int enA = 9;
int enB = 10;

// Variables to control delay & speed
int delay_ms = 1000; // delay is milliseconds
int speed = 255; // 0 = off and 255 = max speed

void setup() {
  // set the motor control pins as output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enA, OUTPUT); 
  pinMode(enB, OUTPUT); 
}

void loop() {
  // control the speed of the motors
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  // Go forward
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  delay(delay_ms);

  // Go backward
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  delay(delay_ms);

  // Go left
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  
  delay(delay_ms);

  // Go right
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  
  delay(delay_ms);

  // STOP
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(delay_ms);

}
