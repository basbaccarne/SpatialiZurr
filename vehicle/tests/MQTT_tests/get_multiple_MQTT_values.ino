// This script can detect and store different MQTT values from different topics

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

// declare variable to story the incoming MQTT payload
String payload;

// declare variables to store the MQTT data into
float width = 0;
float depth = 0;
float resolution = 0;
int status = 0;

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
  mqttClient.subscribe(subtopic1);
  mqttClient.subscribe(subtopic2);
  mqttClient.subscribe(subtopic3);
  mqttClient.subscribe(subtopic4);

  // set the message receive callback function:
  // Trigger the 'onMqttMessage' function when mqttClient.poll() (in the loop function) detects a message
  mqttClient.onMessage(onMqttMessage);
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();
}

// function that triggers when a signal comes in
void onMqttMessage(int messageSize) {
  // print out the topic and some message details
  Serial.println("Received a message...");

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
  }
}
