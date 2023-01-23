// load libraries for wifi en MQTT
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

// set passwords for shiftr & SSID
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
char mqttUsername[] = SECRET_MQTT_USER;
char mqttPass[] = SECRET_MQTT_PASS;
char direction[] = "0";

// set-up wifi client
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// set-up MQTT server information en topic to subscribe to
const char broker[] = "spatializurr.cloud.shiftr.io";
int        port     = 1883;
const char topic[]  = "robotconrol";

// set-up variables for the delay
const long interval = 1000;
unsigned long previousMillis = 0;

// function to print what was received from MQTT
void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
}

void setup() {
  // open serial connection
  Serial.begin(9600);

  // connect to SSID
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  // authenticate with MQTT username and password
  mqttClient.setUsernamePassword(mqttUsername, mqttPass);

  // connect to the MQTT server
  Serial.print("Verbinden met de MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ...");

  // when MQTT stuff breaks ...
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  // when MQTT stuff works ...
  Serial.println("Verbonden met de MQTT broker! Hoera!");

  // Subscribe to topic
  mqttClient.onMessage(onMqttMessage);
  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  mqttClient.subscribe(topic); 
}

void loop() {
  // poll regularly to avoid being disconnected by the broker
  mqttClient.poll();

  // settings for delay
  unsigned long currentMillis = millis();
}

// function that runs when a message is received
void onMqttMessage(int messageSize) {
  // when a message is received, print metadata to serial
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // define character variable for MQTT capture
  char robotcontrol[messageSize];

  // get data and store in a 'robotcontrol' variable
  while (mqttClient.available()) {
    for (int i = 0; i < messageSize; i++) {
      robotcontrol[i] = (char)mqttClient.read(); // Read the characters into an array
      }
    }
    // print the robotcontrol variable
    Serial.println(robotcontrol);

    // parse the robot control variable
    // to be done
}
