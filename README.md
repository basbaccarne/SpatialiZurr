# VR_space_scanner
A scanning robot with a 360 cam to capture and map 3D/360 spaces for VR scenes

# Parts of physical thing (from bottom to top)
## Wheel base
* We're using a laser cutted base on which we mount a tripod
* Status: rough prototype base laser cutted, not mounted yet

## Driving the wheel base (Arduino)
* We're using an Arduino with mechanum wheels to drive the wheel base
* The wheel base moves in increments and lines to 'sample' the space
* [This is the components list](4WD_base.md)
* [This is the Arduino script](https://github.com/basbaccarne/SpatialiZurr/blob/main/driver/arduino_TT_motor_with_L298N.INO)
* [Snapshot current hardware](https://github.com/basbaccarne/SpatialiZurr/blob/main/driver/prototype%20wiring.jpg)
* Status: the TT motors we used are not heavy enough, we ordered new ones (N20 motor - 75:1 - 6V 400 rpm)
* Status: while waiting for delivery: using a computer mouse to track positioning ;)

## Teta 360 cam (Teta 360 & Raspi)
* We're using a Teta 360* camera to take pictures per increment of the base
* The snapshot command is issues trhough a Raspi over a USB protocol of the Teta cam
* Status: the forced delay between snapshots is causing a problem. We're considering switching to a movie that has te be resampled.

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
