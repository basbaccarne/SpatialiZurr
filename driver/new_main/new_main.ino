// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech

int sensorPin1 = A4;
int sensorPin2 = A5;   // select the input pin for the potentiometer
int sensorValue1 = 0;
int sensorValue2 = 0;
int ledPin = 13;  // variable to store the value coming from the sensor

const int StepW = 12;
const int DirW = 13;
const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int StepZ = 4;
const int DirZ = 7;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  pinMode(StepW, OUTPUT);
  pinMode(DirW, OUTPUT);
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);
  pinMode(StepZ,OUTPUT);
  pinMode(DirZ,OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  Serial.print("pin1 ");
  Serial.print(sensorValue1);
  Serial.print( "; pin2 ");
  Serial.println( sensorValue2);
  if (sensorValue1 > 10)
  {
    digitalWrite(DirW, HIGH);
    digitalWrite(DirX, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
    digitalWrite(DirY, HIGH);
    digitalWrite(DirZ, HIGH);
    for(int x = 0; x<200; x++) 
    { // loop for 200 steps
    digitalWrite(StepW,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepW,LOW); 
    delayMicroseconds(500);

    digitalWrite(StepX,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepX,LOW); 
    delayMicroseconds(500);

    digitalWrite(StepY,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepY,LOW); 
    delayMicroseconds(500);

    digitalWrite(StepZ,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepZ,LOW); 
    delayMicroseconds(500);
    }
    
    


  }
}


