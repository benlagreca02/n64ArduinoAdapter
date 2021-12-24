/* 
 * Much inspiration was taken from this project
 * https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/
 * I STRONGLY disliked the mixed C and assembly, along with the labels and GOTO's
 *  and figured there *must* be a way to complete this without those
 */

/*
 * 
 * HOW THE n64 CONTROLLER TALKS
 * all data ENDS with a HIGH
 *	DATA ENCODING
 *	us| 0 1 2 3
 * ----------------
 *	0 | 0 0 0 1
 *	1 | 0 1 1 1
 *
 *  POLL: 0b0 0000 0011
 *  ANSR: 32bits + 0001*...
 *
*/

#include "n64Macros.h"
#include "N64Data.h"
#include <Wire.h>

#define EXPECTED_BITS_RETURNED 32
#define N64_PIN 7

void setup() {
    // Start i2c comms as MASTER
    Wire.begin();
}

byte rawData[EXPECTED_BITS_RETURNED];  // all 32 bits
byte *rawArrPtr;
int bitsRecieved = 0;
N64Data myN64Data;

void loop() {
    rawArrPtr = rawData;
    bitsRecieved = 0;

    // EXTREMELY time sensitive, especially with such a slow board
    noInterrupts();
	  cli();
	  
	  N64_SEND_POLL(N64_PIN);
	  
	  // QUICK! the data come in immediately
	  while(true){
		    // if the line is LOW, wait 1.5 us and read
  		  if(!N64_READ(N64_PIN)){
  		      _delay_us(1.5);
  			    bitsRecieved++;
  			    *rawArrPtr = N64_READ(N64_PIN);
  			    rawArrPtr++;
  		  }
		
		    if(bitsRecieved > EXPECTED_BITS_RETURNED){
		        break;
		    }
	  }

	  sei();
  	interrupts();

    // clean up the data
	  myN64Data.pack(rawData, sizeof(rawData));
   
    // recall we are the master, slave addr is 1
    Wire.beginTransmission(0b0000001);
    Wire.write(myN64Data.getPacked(0));
    Wire.write(myN64Data.getPacked(1));
    Wire.write(myN64Data.getPacked(2));
    Wire.write(myN64Data.getPacked(3));
    Wire.endTransmission();

    delay(1);
    
}
