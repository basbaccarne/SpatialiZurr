// More information
// https://freshman.tech/learn-node/

// modules
const http = require('http');
const mqtt = require('mqtt');
const express = require('express');


// server setting & set-up connection
const app = express();
const server = app.listen(7000, () => {
  console.log(`This awesome app is running on port ${server.address().port}`);
});

// Create a new MQTT client instance, and connect to the Shiftr.io broker:
var client = mqtt.connect('mqtt://spatializurr:fJWgFP2u8chjYKCB@spatializurr.cloud.shiftr.io', {
  clientId: 'spatializurr companion app'
});

// Subscribe to a topic and define a callback function to handle incoming messages:
const topic = 'robotcontrol';
client.subscribe(topic, function (err) {
  if (!err) {
    client.on('message', function (topic, message, packet) {
      console.log(message.toString());
      console.log('subscribed to ' + topic);
    });
  }
});

// Send messages to the topic
client.publish(topic+'/width', '3.3', function (err) {});
client.publish(topic+'/depth', '2', function (err) {});
client.publish(topic+'/resulution', '1', function (err) {});
client.publish(topic+'/status', '1', function (err) {});
