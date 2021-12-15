


/*
*	DATA ENCODING
*	us| 0 1 2 3
*   --------------
*	 0| 0 0 0 1
*	 1| 0 1 1 1
*
*  POLL: 2_0 0000 0011
*  ANSR: 32bits + 1 end bit
*
*/


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

	// SEND OUT THE REQUEST

}
