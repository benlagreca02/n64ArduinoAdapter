
#include "N64Data.h"

// Pack the raw data (1 byte per bit) into the member
//   variable to minimize I2C transmission
// Inputs:
//		rawArray:  array of 1 bit per byte data to 'pack' into bytes
//		sizeOfRaw: number of items (bytes) in rawArray
void N64Data::pack(byte rawArray[], byte sizeOfRaw){	
  
  // for every BYTE in the raw data (normally [0-31]
  byte currByte = 0b00000000;
  for(int i = 0; i < sizeOfRaw; i++){
    // i am the greatest programmer to have ever lived 
     currByte |= ((rawArray[i] != 0) ? 1 : 0 )<< i % 8;
    if(i%8 == 7){
      m_processedData[i/8] = currByte;
      currByte = 0b00000000;
    }
	}
}


byte N64Data::getPacked(int index){
    return m_processedData[index];
}
