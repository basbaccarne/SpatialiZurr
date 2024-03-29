// This is the first integrated test that combines the MQTT and the motor control
// The script connects to WiFi, then to MQTT, waits for a message and then drives the motors
// The motors in this test are stepper motors
// The stepper motors were not strong enough to drive the vehicle

// load libraries voor wifi en MQTT
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

// set passwords for WiFi & MQTT server
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
char mqttUsername[] = SECRET_MQTT_USER;
char mqttPass[] = SECRET_MQTT_PASS;

// define clients
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// set MQTT server information
const char broker[] = "spatializurr.cloud.shiftr.io";
int port = 1883;

// set topics to subscribe to
const String topic = "robotcontrol";
String subtopic1 = topic + "/width";
String subtopic2 = topic + "/depth";
String subtopic3 = topic + "/resolution";
String subtopic4 = topic + "/status";
String subtopic5 = topic + "/motortime";

// declare variable to story the incoming MQTT payload
String payload;

// key room dimension variables & calculated values steps & lanes
float width = 0;
float depth = 0;
float resolution = 0;
int status = 0;
float motortime = 0;
int steps;
int lanes;

// motor delay (between steps)
int motordelay = 100; // how long the motor runs
int waitdelay = 1000; // how long the motor waits

// Motor 1
int motor1pin1 = A0;
int motor1pin2 = A1;
// Motor 2
int motor2pin1 = A2;
int motor2pin2 = A3;
// Speed controls board 1
int enA = 9;
int enB = 10;

// Motor 3
int motor3pin1 = A4;
int motor3pin2 = A5;
// Motor 4
int motor4pin1 = A6;
int motor4pin2 = A7;
// Speed controls board 2
int enA2 = 5;
int enB2 = 6;

// Variables to control delay & speed
int speed = 255;  // 0 = off and 255 = max speed

void setup() {
  Serial.begin(9600);

  // connect to WiFi
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  // set MQTT username and password for authentication
  mqttClient.setUsernamePassword(mqttUsername, mqttPass);

  // connect to the MQTT server
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1)
      ;
  }
  Serial.println("You're connected to the MQTT broker!");

  // subscribe to the topics
  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  mqttClient.subscribe(topic);
  mqttClient.subscribe(subtopic1);
  mqttClient.subscribe(subtopic2);
  mqttClient.subscribe(subtopic3);
  mqttClient.subscribe(subtopic4);
  mqttClient.subscribe(subtopic5);

  // set the message receive callback function:
  // Trigger the 'onMqttMessage' function when mqttClient.poll() (in the loop function) detects a message
  mqttClient.onMessage(onMqttMessage);

  // set the motor control pins as output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
  pinMode(enA2, OUTPUT);
  pinMode(enB2, OUTPUT);
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();

  // set the speed of the motors
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  analogWrite(enA2, speed);
  analogWrite(enB2, speed);
}

// function that triggers when a signal comes in
void onMqttMessage(int messageSize) {
  // print out the topic and some message details
  Serial.println("Received a message: ");
  String topic = mqttClient.messageTopic();
  // Serial.println(topic);
  // Serial.print(mqttClient.messageTopic());
  // Serial.print("', length ");
  // Serial.print(messageSize);
  // Serial.println(" bytes:");

  // read the incoming data and store it into the payload variable
  String payloadString = "";
  for (int i = 0; i < messageSize; i++) {
    payloadString += (char)mqttClient.read();
  }
  payload = payloadString;

  // check the topic of the payload and store it in the correct variable
  if (topic == subtopic1) {
    width = payload.toFloat();
    Serial.print("Ik sloeg de width op met waarde: ");
    Serial.println(width);
  } else if (topic == subtopic2) {
    depth = payload.toFloat();
    Serial.print("Ik sloeg de depth op met waarde: ");
    Serial.println(depth);
  } else if (topic == subtopic3) {
    resolution = payload.toFloat();
    Serial.print("Ik sloeg de resolution op met waarde: ");
    Serial.println(resolution);
  } else if (topic == subtopic4) {
    status = payload.toInt();
    Serial.print("Ik sloeg de status op met waarde: ");
    Serial.println(status);
  } else if (topic == subtopic5) {
    motortime = payload.toInt();
    Serial.print("Ik sloeg de motorspeed op met waarde: ");
    Serial.println(motortime);
  }

  // if all the data is present (status is the last variable sent):
  if (status == 1) {
    // calculate the steps
    Serial.println("Here we go!");
    Serial.println("#############################################");
    steps = width * resolution;
    lanes = depth * resolution;
    Serial.print("We will ride ");
    Serial.print(steps);
    Serial.print(" steps and ");
    Serial.print(lanes);
    Serial.println(" lanes. What an adventure!");

    // run the stepper function
    arduinoStepper(steps, lanes);
  }
}

// function to drive the Arduino based in the MQTT commandos calculated as an amount of steps and lanes
void arduinoStepper(int steps, int lanes) {

  // keep going as long as the status is 1
  while (status == 1) {

    // do this every lane
    for (int l = 0; l < lanes; l++) {

      // do this every step
      for (int s = 0; s < steps; s++) {
        // go forward for the even lanes
        if ((l % 2) == 0) {
          motorcontrol("forwards", l, s);
          delay(waitdelay);
        }
        // go backwards for the uneven lanes
        if ((l % 2) != 0) {
          motorcontrol("backwards", l, s);
          delay(waitdelay);
        }
      }  // end of step loop

      if (l != lanes - 1) {
        motorcontrol("left", 0, 0);
        delay(waitdelay);
      }
    }  // end of lane loop

    // end this shit!
    Serial.println("end");
    status = 0;
  }  // end of while loop
}

void motorcontrol(String direction, int lane, int step) {
  if (direction == "forwards") {
    // Go forward
    Serial.print("Lane ");
    Serial.print(lane);
    Serial.print(" | Step ");
    Serial.println(step);
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

    delay(motortime);

    // Stop after delay
    Serial.println("stop");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, LOW);
  }

  else if (direction == "backwards") {
    Serial.print("Lane ");
    Serial.print(lane);
    Serial.print(" | Step ");
    Serial.println(step);
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);

    delay(motortime);

    // Stop after delay
    Serial.println("stop");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, LOW);
  }

  else if (direction == "left") {
    Serial.println("lane switch!");
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);
    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

    delay(motortime*10);

    // Stop after delay
    Serial.println("stop");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, LOW);
  }
}
