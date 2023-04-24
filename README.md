# VR_space_scanner
A scanning robot with a 360 cam to capture and map 3D/360 spaces for VR scenes

# Parts of physical thing (from bottom to top)
## Wheel base
* We're using a laser cutted base on which we mount a tripod
* **Motors**: 4x DC Motor with JST PH 2.0 connector - 25mm - 12V / 400RPM ([link](https://www.kiwi-electronics.com/nl/dc-motor-met-jst-ph-2-0-connector-25mm-12v-400rpm-10788)) (remark: these are too weak for this weight
* **Motor mounts**: [3D printed clamping mounts](https://a360.co/3KfTK3s) - 25mm motor diameter, M4 nuts & bolts (2 per motor)
* **Wheels**: Mecanum Wheels 80MM 2 sets of 2 (L+R) (OT3482) ([link](https://www.otronic.nl/nl/mecanum-wiel-omnidirectioneel-wiel-80mm-a-geel-set.html))
* **Wheel to motor connection**: small 3D printed hubs ([link to the 3D file](https://a360.co/3Y8MtHl))
* **Driver**: Motor driver: 4x L298N
* **Power**: currently we're using a 12V adapter connected to the net > needs to be changed to battery pack
* **Status**: rough prototype base laser cutted, components mounted, issues: (1) stabalize motor mount (2) wheel attachment (3) LCD, (4) parametricize delays

## Driving the wheel base (Arduino)
* We're using an Arduino with mechanum wheels to drive the wheel base
* The wheel base moves in increments and lines to 'sample' the space
* The Aruino receives width, depth, resolution and status over MQTT
* This is used to calculate the required steps and drive the motor
* [This is the Arduino script](https://github.com/basbaccarne/SpatialiZurr/tree/main/driver/main)
* [Snapshot current hardware](https://github.com/basbaccarne/SpatialiZurr/blob/main/driver/prototype%20wiring.jpg)
* **Status**: optimization options: status LCD, audio feedback, position tacking (e.g. using a mouse or rotary angle sensor)

## Sending room parameters to the Arduino (MQTT)
* We're using MQTT to send the parameters to the Arduino
* The MQTT broker is https://spatializurr.cloud.shiftr.io/
* Topics are robotcontrol/depth, robotcontrol/width, robotcontrol/resolution, robotcontrol/status
* As a dummy, we use [this node.js script](https://github.com/basbaccarne/SpatialiZurr/blob/main/remote_app/app.js)
* To run this just use ```node app.js``` in the command prompt
* **status**: find a better way to send the MQTT data to the broker (webhook?)

## Teta 360 cam (Teta 360 & Raspi)
* We're using a Teta 360* camera to take pictures per increment of the base
* The snapshot command is issues trhough a Raspi over a USB protocol of the Teta cam
* Status: the forced delay between snapshots is causing a problem. We're considering switching to a movie that has te be resampled.
* Update: Next approach: try with a physical button push (stepper motor connected to the Arduino)

# Parts of the digital thing
## Transfer and preprocessing Teta data
* The Teta stores data on a SD card in a folder x, and filname structure y
* The data is transfered ..., and processed by ...
* Status: not started yet

## Preparing filenames (Python)
* In Python, we calculate a matrix of room coordinates (based on width, depth and resulution)
* This matrix is used to rename the 360* pictures and store them in a place to be imported in Unity
* Resource: [renaming photos in python](https://www.youtube.com/watch?v=4HU5DiGD4lY)
* Status: works on sample data and preset variables

## Stiching 360* images to character controller in Unity (Unity)
* First, w attach a sphere to the character controller 
* Next, we're calculating and remapping the coordinates of the character controller (where the head set is)
* Finally, the coodinate loads the correspinding 360* picture and uses this as a mesh inside the sphere
* Status: works on sample data and preset variables
