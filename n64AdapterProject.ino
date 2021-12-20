/* Much inspiration was taken from this project
* https://www.instructables.com/Use-an-Arduino-with-an-N64-controller/
* I STRONGLY disliked the mixed C and assembly, along with the labels and GOTO's
*  and figured there *must* be a way to complete this without those
*  
*  I also tied a 1.5k pullup resistor to the data line...
*  I don't know if this is hurting anything
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





#define EXPECTED_BITS_RETURNED 32
#define N64_PIN 2
// only works on digital pins [0-7]
// this is how the data will be sent
// DDRD is the [D]ata [D]irection [R]egister for port [D]
// By setting a bit inteh DDR, it is set to OUTPUT, clear -> INPUT
//
// The n64 only *really* cares about LOW pulses as the
//		controller has a pullup resistor to 3.3v
// By setting a pin to INPUT, the arduino shorts it to ground (0)
// By setting a pin to OUTPUT, the arduino lets it get pulled up(i think)
// i.e. INPUT -> low signal , OUTPUT -> high signal
#define SET_DDRD(n) DDRD |= 1 << n
#define CLR_DDRD(n) DDRD &= ~(1 << n)
#define N64_CLR(n) SET_DDRD(n)
#define N64_SET(n) CLR_DDRD(n)

#define N64_READ(n) (PIND & 1<<n)

// 1 us per 1 or 0
// 1 -> 0111
// 0 -> 0001

#define N64_0(n) {\
	N64_CLR(n);\
	_delay_us(3);\
	N64_SET(n);\
	_delay_us(1);\
}

#define N64_1(n) {\
	N64_CLR(n);\
	_delay_us(1);\
	N64_SET(n);\
	_delay_us(3);\
}

#define N64_SEND_POLL(n){\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_0(N64_PIN);\
		N64_1(N64_PIN);\
		N64_1(N64_PIN);\
}




void setup() {}


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
	// quick! read the data!
  while(true){
    // if the line is LOW, wait 2 us and read,
    if(!N64_READ(N64_PIN)){
      _delay_us(1.5);
      *rawArrPtr = N64_READ(N64_PIN);
      rawArrPtr++;
      bitsRecieved++;
    }
    if(bitsRecieved > EXPECTED_BITS_RETURNED) break;
  }

  sei();
  interrupts();
  
}
