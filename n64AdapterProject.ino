
/*
* 
* HOW THE n64 CONTROLLER TALKS
* all data ENDS with a HIGH
*	DATA ENCODING
*	us| 0 1 2 3
*   --------------
*	 0| 0 0 0 1
*	 1| 0 1 1 1
*
*  POLL: 0b0 0000 0011
*  ANSR: 32bits + 1 end bit ( i think)
*
*/


#define N64_PIN 2 // Pin 2 and 3 are interrupt pins
// only works on digital pins [0-7]
// this is how the data will be sent
// DDRD is the [D]ata [D]irection [R]egister for port [D]
// By setting a bit, it is set to OUTPUT, clear -> INPUT
// The n64 only *really* cares about LOW pulses as the
//		controller has a pullup resistor to 3.3v
// By setting a pin to INPUT, the arduino shorts it to ground (0)
// By setting a pin to OUTPUT, the arduino lets it drift (i think)
//		and it gets pulled by the pullup resistor(?)
// i.e. INPUT -> n64 0, OUTPUT -> n64 1
#define SET_DDRD(n) DDRD |= 1 << n
#define CLR_DDRD(n) DDRD &= ~(1 << n)
#define N64_CLR(n) SET_DDRD(n)
#define N64_SET(n) CLR_DDRD(n)
#define N64_READ(n) (PIND & 1<<n)

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



#define NUM_REC_BITS 31

char volatile rawData[NUM_REC_BITS];  // all 32 bits
char volatile *arrPtr;
int  volatile counter = 0;

// When there is a falling edge:
//		wait 2 us
//		read and store value at arrPtr
//		increment counter and arrPtr
void fallingISR(){

	// We just got a falling edge!
//  arrPtr++;
  _delay_us(1);
  *arrPtr = N64_READ(N64_PIN);  
  counter++;
}


void setup() { 	
	//Serial.begin(115200);
	//Serial.println("uhhh");
	// wow thats a long name
	attachInterrupt(digitalPinToInterrupt(N64_PIN), fallingISR, FALLING);
  //Serial.println("Ok ISR attached, lets start cooking");
}




void loop() {
    arrPtr = rawData;
    counter = 0;

	// watcho jet
	_delay_us(500);

	// request data
	noInterrupts();
	N64_SEND_POLL(N64_PIN);
	interrupts();
	// quick! read the data!
  do{}while(counter < NUM_REC_BITS);
  

  //Serial.println("Done!");
  Serial.begin(115200);
	for(uint8_t i = 0; i < sizeof(rawData); i++){
		Serial.print(i);
		Serial.print("  | ");
		if(rawData[i]){Serial.println("1");}
		else{Serial.println("0");}
	}


	while(1){};

}
