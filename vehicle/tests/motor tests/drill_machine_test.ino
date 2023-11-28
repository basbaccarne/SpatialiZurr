// this is a test script to test the hacked drill machine motors
// test 1: basic driving the motor

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