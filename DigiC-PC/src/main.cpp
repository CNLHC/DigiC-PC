#include<cstdio> 
#include"FTDUtil.h"
#include <chrono>
#include <thread>
#include "spi.h"

int main() {
	Init_libMPSSE(); //This Line is important DO NOT DELETE it!
	FTDUtil FTDHandle;
	FTDHandle.lsSPIChannel();
	uint8 buffer[8] = { 0x12,0x34,0x56,0x78,0xAB,0xCD,0xEF,0xDD };

	while (1) {

	//FTDHandle.SPIWriteByte(0, 0, 0x34ABCDEF);
		FTDHandle.SPIWriteByteArray(buffer,4);
	}

	
	//spi_main();

}
