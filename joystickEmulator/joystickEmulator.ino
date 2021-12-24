/*
 *  Included from ZIP from this link
 *  (Sketch -> Include Library -> Add .Zip)
 *  https://github.com/MHeironimus/ArduinoJoystickLibrary/archive/version-2.0.zip
 *  
 *  Documentation on the library
 *  https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0
 */

#include <Joystick.h>
#include <Wire.h>
#include "buttonMasks.h"
#define NUM_BYTES_EXPECTED 4  // we receive 4 bytes (32 bits)
Joystick_ usrJoystick;

#define AXIS_MIN  0x00
#define AXIS_MAX  0xFF

void setup(){
    // True indicated it auto sends controller state
    //     to the computer
    usrJoystick.begin(true);
    usrJoystick.setXAxisRange(AXIS_MIN,AXIS_MAX);
    usrJoystick.setYAxisRange(AXIS_MIN,AXIS_MAX);


    Wire.begin(0b0000001);
    Wire.onReceive(i2cRecieveHandler);
    Serial.begin(9600);
    
}

// almost like an interrupt routine
void i2cRecieveHandler(int numBytes){
    Serial.print("I2C MSG RECIEVED:  ");
    uint8_t numBytesRecieved = 0;
    byte dataRecieved[NUM_BYTES_EXPECTED];
    
    while(Wire.available()){
        dataRecieved[numBytesRecieved] = Wire.read();
        numBytesRecieved++;
    }
    
    Serial.print(dataRecieved[0], BIN);
    Serial.print(" | ");
    Serial.print(dataRecieved[1], BIN);
    Serial.print(" | ");
    Serial.print(dataRecieved[2], HEX);
    Serial.print(" | ");
    Serial.println(dataRecieved[3], HEX);

    // L, R, and C buttons are stored in the SECOND byte
    // A,B,Z,START, and D pad are stored in FIRST byte
    // Joystick X axis is stored in THIRD byte
    // Joystick Y axis is stored in FOURTH byte
    
    // A button is 0th bit of 0th byte
    usrJoystick.setButton(0, dataRecieved[1] & C_DOWN_MASK);
    usrJoystick.setButton(1, dataRecieved[1] & C_RIGHT_MASK);
    usrJoystick.setButton(2, dataRecieved[1] & C_LEFT_MASK);
    usrJoystick.setButton(3, dataRecieved[1] & C_UP_MASK);
    
    usrJoystick.setButton(4, dataRecieved[1] & L_MASK);
    usrJoystick.setButton(5, dataRecieved[1] & R_MASK);
    usrJoystick.setButton(6, dataRecieved[0] & A_MASK);
    usrJoystick.setButton(7, dataRecieved[0] & B_MASK);
    usrJoystick.setButton(8, dataRecieved[0] & START_MASK);
    usrJoystick.setButton(9, dataRecieved[0] & Z_MASK);
    
    
}
//bool state = false;
void loop(){}
