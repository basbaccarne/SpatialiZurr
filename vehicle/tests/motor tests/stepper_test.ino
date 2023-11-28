// This script does x steps forward then y steps sideways then x back

// step distance (in cm)
int step_distance = 5;

// steps to take
int steps = 4;

// lane distance (in cm)
int lane_dist = 5;

// z = delay to take a picture (in milisecond)
int picture_delay = 1000;

// speed of the motor (in miliseconds)
int speed  = 500;

// setting the sensor pins for nano input (read x & y)
// and set variables for the analog reads
int sensorPin1 = A4;
int sensorPin2 = A5;
int sensorValue1 = 0;
int sensorValue2 = 0;

// setting the motor pins
// motors: w, x, y & z
const int StepW = 12;
const int DirW = 13;
const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int StepZ = 4;
const int DirZ = 7;

void setup() {
  // declare the ledPin as output
  Serial.begin(9600);

  // set the motor pins as outputs
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
  // read the value from the sensor: (temp diable)
  // sensorValue1 = analogRead(sensorPin1);
  // sensorValue2 = analogRead(sensorPin2);
  // Serial.print("pin1 ");
  // Serial.print(sensorValue1);
  // Serial.print( "; pin2 ");
  // Serial.println( sensorValue2);

  // go forward (set the direction of each wheel)
  digitalWrite(DirW, HIGH);
  digitalWrite(DirX, LOW); 
  digitalWrite(DirY, LOW);
  digitalWrite(DirZ, HIGH);

  // drive the motor x steps
  for(int y = 0; y < steps; y++) 
    {  
      drive(speed, step_distance);
      delay(picture_delay);
    }

  // go backwards (set the direction of each wheel)
  digitalWrite(DirW, LOW);
  digitalWrite(DirX, HIGH); 
  digitalWrite(DirY, HIGH);
  digitalWrite(DirZ, LOW);
  
  // drive the motor x steps
  for(int y = 0; y < steps; y++){
      drive(speed, step_distance);
      delay(picture_delay);
  }
  
}

// this function drives the motors for a given distance and speed
void drive(int speed, int distance) {
  // go through the steps, defined as distance
  // the speed is the delay between the steps
  for(int x = 0; x < distance * 100; x++) 
    { 
    digitalWrite(StepW,HIGH);
    digitalWrite(StepX,HIGH);
    digitalWrite(StepY,HIGH);
    digitalWrite(StepZ,HIGH);

    delayMicroseconds(speed);

    digitalWrite(StepW,LOW); 
    digitalWrite(StepX,LOW); 
    digitalWrite(StepY,LOW); 
    digitalWrite(StepZ,LOW); 

    delayMicroseconds(speed);

    }
}
