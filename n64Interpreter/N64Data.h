#define NUM_BYTES 4

#include <Arduino.h>  // for byte type

class N64Data{

	public:	
		void pack(byte rawArray[], byte sizeOfRaw);
		byte getPacked(int index);  // [0 - 3] 
	private:
		byte m_processedData[NUM_BYTES];
};
