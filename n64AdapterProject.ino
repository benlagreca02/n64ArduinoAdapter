
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


#define N64_PIN 7
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

#define N64_POLL(n){\
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

void setup() { 	
	Serial.begin(9600);
}

char rawData[33];  // all 32 bits
char *arrPtr = rawData;
#define NUM_REC_BITS 33
uint8_t  counter = 0;

void loop() {
  *arrPtr = rawData;
  counter = 0;
  
  // watcho jet
  _delay_us(500);
  
  // request data
  N64_POLL(N64_PIN);
	// quick! read the data!
	
	while(1){
		// detect falling edge
    while((N64_READ(N64_PIN))){}
    _delay_us(2);
		*arrPtr = N64_READ(N64_PIN); //read the value
    arrPtr++;                    // move to next item in array
    counter++;
	  if(counter >= NUM_REC_BITS) break;
	}
 
// HYWH YWH YWHYWHWYHWYW
    while(1){}


  
//  Serial.println();
//  for(uint8_t i = 0; i < sizeof(rawData); i++){
//    Serial.print(i);
//    Serial.print("  | ");
//    if(rawData[i]){Serial.println("1");}
//    else{Serial.println("0");}
//  }

}
