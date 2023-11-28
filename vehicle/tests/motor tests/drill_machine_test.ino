// this is a test script to test the hacked drill machine motors
// test 1: basic driving the motor
// We bought 4 drill machines & tool them apart
// The drill machines are powerd with a battery that goes through a MOSFET (irfb3607) and drives a motor
// The motor is connected to a planetaty gearbox
// reference (e.g. pinout): https://itp.nyu.edu/physcomp/labs/motors-and-transistors/using-a-transistor-to-control-high-current-loads-with-an-arduino/

const int transistorPin = 3;
 
 void setup() {
   // set  the transistor pin as output:
   pinMode(transistorPin, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
 }
 
 void loop() {
 // Go trhough a couple of the PWM values (the values can go from 5 to 255 (0 to 100%)
 // the MOSFET (irfb3607) operates at 5V. If you try it at 3,3V it only partially closes
   analogWrite(transistorPin, 0);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   analogWrite(transistorPin, 25);
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
   analogWrite(transistorPin, 50);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   analogWrite(transistorPin, 75);
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
     analogWrite(transistorPin, 100);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   analogWrite(transistorPin, 125);
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
     analogWrite(transistorPin, 150);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   analogWrite(transistorPin, 175);
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
 }