// this is to reduce clutter in the 'main' file
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

