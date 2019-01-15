#define _USE_MATH_DEFINES
#include <cmath>
#include<cstdio> 
#include <chrono>
#include <thread>
#include "DigiCDriver.h"
#include <cstdlib>

#define TESTBYTES 0x33

int8_t rawData[15] = { 0x62,0x01,0x02,
0x19,0x98,0x10,0x26,
0x00,0x10,0x16,0x23,
0x12,0x75,0x66,0xf6 };
int8_t buffer[32] = { 
	0xFF,0x12,0x34,0x56,0xFF,0x98,0x76,0x54,
	0xFF,0xab,0xcd,0xef,0xFF,0x80,0x58,0x21,
	0x62,0x01,0x02,0x19,0x98,0x10,0x26,0x00,
	0x10,0x24,0x63,0x76,0x56,0x97,0x21,0x96
};
int8_t bufferb[10240];



int main() {
	Init_libMPSSE(); //This Line is important, DO NOT DELETE it!
	// And it MUST be placed here, at first line in main function. Otherwise, the spi channel can't open.
	//Why? May be the FTDI's black magic.
	DigiCDataUtil u1;
	typDigiCPack a;
	a=u1.PacketData(rawData);
	DigiCDriver d1;
	

	while (1) {
		d1.sendPacket(a);

		//for (int n=0; n != 16; n++) {
		//		 bufferb[n]=static_cast<uint8>(std::rand()*1000);  // Note: 1+rand()%6 is biased
		//}
		//FTDHandle.SPIWriteByteArray(buffer,32);
		//FTDHandle.SPIWriteByteArray(bufferb,16);
	}
}
