# Spatializurr: The VR space scanner
This is the GitHub repo for the Spatializurr project.

Spatializurr is a scanning robot with a 360 cam to capture and map 3D/360 spaces for VR scenes.
It uses an Arduino, a Raspberry Pi, a Ricoh Teta 360 camera and Unity to create a VR experience.

Below you can find a description of the different parts of the project.

# Parts of physical thing (from bottom to top)
## Wheel base
* We're using a **laser cutted base** on which we mount a tripod
* **Motors**: ~~4x nema 17 stepper motors (earlier test with less powerful motors failed)~~  We bought 4 drill machines & took them apart. The drill machines are powerd with a battery that goes through a MOSFET (irfb3607) and drives a motor. The motor is connected to a planetaty gearbox.
* **Motor mounts**: ~~[nema 17 mounting brackets](https://www.hobbyelectronica.nl/product/bracket-nema-17/)~~ We need custom brackets.
* **Wheels**: ~~[Mecanum Wheels 80MM 2 sets of 2 (L+R) (OT3482)](https://www.otronic.nl/nl/mecanum-wiel-omnidirectioneel-wiel-80mm-a-geel-set.html) (might be too small, which would mean they need to be replaced with 3D printed DIY wheels)~~ [100mm Mecanum Wheel Set with 4mm Shaft Connector](https://www.robots4all.be/Webwinkel-Product-175025373/100mm-Mecanum-Wheel-Set-with-4mm-Shaft-Connector-(SPCC).html)
* **Wheel to motor connection**: ~~small 3D printed hubs ([link to the 3D file](https://a360.co/3ZwzRfF))~~ A bolt that is attached to the drill connection
* **Driver**: ~~Motor driver: [Arduino CNC shield](https://www.hobbyelectronica.nl/product/arduino-cnc-shield/)~~ Custom circuit with 4 MOSFETs
* **Power**: ~~currently we're using a heavy adapter connected to the net > needs to be changed to battery pack~~ 4 Drill power packes
* **Status**: rough prototype base laser cutted, drills taken apart, testing custom drive (then: custom mounts)

## Driving the wheel base (Arduino)
* We're using an Arduino with mechanum wheels to drive the wheel base
* The wheel base moves in increments and lines to 'sample' the space
* The Aruino receives width, depth, resolution, motorspeed and status over MQTT
* This is used to calculate the required steps and drive the motor
* [These are the Arduino test scripts](/vehicle/tests/integrated tests)
* ~~info on the CNC shield cna be retreived [here](https://courses.ideate.cmu.edu/16-376/s2020/ref/text/hardware/cnc-shield.html)~~
* **Status**: optimization options: status LCD, audio feedback, position tacking (e.g. using a mouse or rotary angle sensor), communicate status back to the MQTT broker

## Sending room parameters to the Arduino (MQTT)
* We're using MQTT to send the parameters to the Arduino
* The MQTT broker is https://spatializurr.cloud.shiftr.io/
* Topics are robotcontrol/depth, robotcontrol/width, robotcontrol/resolution, robotcontrol/status, robotcontrol/motorspeed
* The data is sent from a JavaScript snippet in this [HTML page](/remote app/index.html) (running on [this server](https://bas.baccarne.be/spatializurr/))
* **status**: update CSS to make it more fancy

## Teta 360 cam (Teta 360 & Raspi)
* We're using a Teta 360* camera to take pictures per increment of the base
* The snapshot command is issues trhough a Raspi over a USB protocol of the Teta cam
* **Status**: the forced delay between snapshots is causing a problem. We're considering switching to a movie that has te be resampled.
* Update: Next approach: try with a physical button push (stepper motor connected to the Arduino)

# Parts of the digital thing
## Transfer and preprocessing Teta data
* The Teta stores data on a SD card in a folder x, and filname structure y
* The data is transfered ..., and processed by ...
* **Status**: not started yet

## Preparing filenames (Python)
* In Python, we calculate a matrix of room coordinates (based on width, depth and resulution)
* This matrix is used to rename the 360* pictures and store them in a place to be imported in Unity
* Resource: [renaming photos in python](https://www.youtube.com/watch?v=4HU5DiGD4lY)
* **Status**: works on sample data and preset variables

## Stiching 360° images to character controller in Unity (Unity)
* First, we attach a sphere to the character controller 
* Next, we're calculating and remapping the coordinates of the character controller (where the head set is)
* Finally, the coodinate loads the correspinding 360* picture and uses this as a mesh inside the sphere
* **Status**: works on sample data and preset variables
