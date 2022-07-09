# Nintendo 64  Controller Adapter
A small project to use a pair of common arduinos to interpret the data from a nintendo 64 controller, and emulate a generic USB gamepad.

**NOTE:** This is still a work in progress as of 7/9/22.

## Motivation
I wanted to use a real N64 controller when playing emulators.
I could've bought a 3rd party adapter, but thats no fun.

## Approach
This had been done before with a [library to interpret N64 controller data](https://www.arduino.cc/reference/en/libraries/n64controller/) which I didn't know existed at the time of starting this project.
I did however take inspiration from [this tutorial](https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/).
These  are both great projects, however I wanted to avoid using mixed C and assembly for redability's sake which was the largest hurdle in the project.

## Challenges
Ironically, the modern arduino has quite a hard time keeping up with the Nintendo 64.
The data direction registers and status registers are manipulated directly, as the `digitalRead()` and `digitalWrite()` functions have so much padding, and "saftey" precautions, that they are too slow to keep up with the 25 year old controller.

