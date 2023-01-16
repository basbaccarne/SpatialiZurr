// More information
// https://freshman.tech/learn-node/

// modules
const http = require('http');
const mqtt = require('mqtt')
const express = require('express');
const pug = require('pug');

const app = express();
app.set('view engine', 'pug');

// server settings
const server = app.listen(7000, () => {
  console.log(`This awesome app is running on port ${server.address().port}`);
});

// server content (get index.pug in the views folder)
app.get('/', (req, res) => {
  res.render('index');
});

// Create a new MQTT client instance, and connect to the Shiftr.io broker:
var client = mqtt.connect('mqtt://spatializurr:fJWgFP2u8chjYKCB@spatializurr.cloud.shiftr.io', {
  clientId: 'spatializurr'
});

// Subscribe to a topic and define a callback function to handle incoming messages:
client.subscribe('robotconrol', function (err) {
  if (!err) {
    client.on('message', function (topic, message, packet) {
      console.log(message.toString());
    });
  }
});

// Send a message to the topic:
client.publish('robotconrol', 'Hello, MQTT!', function (err) {
  if (!err) {
    console.log('message sent');
  }
});
