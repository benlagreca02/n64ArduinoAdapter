# Nintendo 64  Controller Adapter
A small project to use a pair of common Arduinos (Pro-micro, and Uno) to interpret the data from a Nintendo 64 controller, and emulate a generic USB gamepad.

**NOTE:** This is still a work in progress, as joystick data isn't being read properly. I'm assuming its a timing issue, but I haven't gotten around to fully debugging this problem. Assuming it is a timing issue, I could just buy a faster arduino, or possibly replace the whole system with a rasberry pi pico. That would be the "end goal": to have it on one board.

## Approach
This had been done before with a [library to interpret N64 controller data](https://www.arduino.cc/reference/en/libraries/n64controller/) which I didn't know existed at the time of starting this project.
I did however take inspiration from [this tutorial](https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/).
These  are both great projects, however I wanted to avoid using mixed C and assembly for redability's sake which was the largest hurdle in the project.

## Challenges
Ironically, the modern arduino has quite a hard time keeping up with the Nintendo 64 controller.
The data direction registers and status registers are manipulated directly, as the `digitalRead()` and `digitalWrite()` functions have so much padding and "saftey precautions", that they are too slow to keep up with the 25 year old controller. This is why two Arduinos are used, the uno (which is faster) to interpret the data from the controller, and the Pro-micro to emulate the gamepad over USB.
