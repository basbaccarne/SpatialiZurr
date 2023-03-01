// load the mqtt module
const mqtt = require('mqtt');

// create a new MQTT client instance, and connect to the Shiftr.io broker:
var client = mqtt.connect('mqtt://spatializurr:fJWgFP2u8chjYKCB@spatializurr.cloud.shiftr.io', {
  clientId: 'spatializurr companion app'
});

// subscribe to a topic
const topic = 'robotcontrol';
client.subscribe(topic, function (err) {
  if (!err) {
    client.on('message', function (topic, message, packet) {
      console.log(message.toString());
      console.log('subscribed to ' + topic);
    });
  }
});
console.log('subscribed to ' + topic);

// send messages to the topic
console.log('sending messages ...');
client.publish(topic+'/width', '3.3', function (err) {});
client.publish(topic+'/depth', '2', function (err) {});
client.publish(topic+'/resolution', '1', function (err) {});
client.publish(topic+'/status', '1', function (err) {});

console.log('messages sent');

setTimeout(function() {
  console.log('Exitting');
  process.exit(0);
}, 400);



// redundant: code to set up a web server

/*
const express = require('express');
const http = require('http');
const app = express();
const server = app.listen(7000, () => {
  console.log(`This awesome app is running on port ${server.address().port}`);
});
*/
