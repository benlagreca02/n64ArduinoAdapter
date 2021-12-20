# Nintendo 64  Controller Adapter
A small project to use an arduino to interpret the data from a nintendo 64 controller, and emulate a typical USB controller.
**NOTE:** This is still a work in progress as of 12/20/21.
I am hoping to get this project finished before I return to school for the spring at the latest.

## Motivation
After setting up an X-Box 360 controller to play on an emulator for a Nintendo 64, I wondered how difficult it would be to build an adapter for the controller.
I knew the N64 controller only had 3 wires, and I had assumed going in that two were for power and ground respectively, and managing one data line couldn't have been that difficult of a task.
I also knew that there *must* be a 3rd party product already available, but thats no fun.

## Approach
I knew there was no way I had been the first person to think of this, so I started researching.
This had been done by many before me, infact there is a [library to interpret N64 controller data](https://www.arduino.cc/reference/en/libraries/n64controller/) using an arduino.
To be honest I didn't know this existed until now where I'm typing the readme for my own project.
I did however take inspiration from [this tutorial](https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/).
These  are both great projects, however I personally find mixed C and assembly *horrible* to look at.
I attempted to create code that would follow as many good programming practices as possible, while remaining fast enough to keep up with the blazing speed of a Nintendo 64.
## Challenges
Ironically, the modern arduino has quite a hard time keeping up with the Nintendo 64 at first.
The controller's data line is burning by with data going at the microsecond rate. 
A full understanding of the arduino's functions and what goes on "under the hood" is necessary to fully understand what is happening.
The data direction registers and status registers were used directly, as the `digitalRead()` and `digitalWrite()` functions have so much padding, and "saftey" precautions, that they are too slow to keep up with the 25 year old controller.
I challenged myself to not use any mixed C and assembly, as I knew it would be possible.

## Current state
Currently, the arduino can read data from the controller about the current status, however the data is going unused.
This will be fixed very soon (next 3 days hopefully) to allow for full functionality.
