/* 
 * Much inspiration was taken from this project
 * https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/
 * I STRONGLY disliked the mixed C and assembly, along with the labels and GOTO's
 *  and figured there *must* be a way to complete this without those
 * 
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

#define EXPECTED_BITS_RETURNED 32
#define N64_PIN 7

void setup() {
  Serial.begin(115200);
}


char rawData[EXPECTED_BITS_RETURNED];  // all 32 bits
char *rawArrPtr;
int bitsRecieved = 0;

void loop() {
    rawArrPtr = rawData;
    bitsRecieved = 0;

    // request data
    noInterrupts();
	  cli();
	  N64_SEND_POLL(N64_PIN);
	  // QUICK! the data come in immediately
	  while(true){
		  // if the line is LOW, wait 1.5 us and read
  		if(!N64_READ(N64_PIN)){
  		    _delay_us(1.5);
  			  *rawArrPtr = N64_READ(N64_PIN);
  			  rawArrPtr++;
  			  bitsRecieved++;
  		}
		
		  if(bitsRecieved > EXPECTED_BITS_RETURNED){
		      break;
		  }
	  }

	  sei();
  	interrupts();

    // A button state printed for testing
    Serial.println(rawData[0], BIN);
    delay(10);
}
