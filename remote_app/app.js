// modules
const http = require('http');
const mqtt = require('mqtt')

// server settings
const hostname = '127.0.0.1';
const port = 3000;

// server content
const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World');
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

// sun the server
server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});