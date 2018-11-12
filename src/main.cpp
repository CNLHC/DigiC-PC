#include<cstdio> 
#include"FTDUtil.h"
#include <chrono>
#include <thread>
#include "spi.h"

int main() {
	Init_libMPSSE(); //This Line is important DO NOT DELETE it!
	FTDUtil FTDHandle;
	FTDHandle.lsSPIChannel();
	while (1) {
	FTDHandle.SPIWriteByte(0, 0, 0x89ABCDEF);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	
	//spi_main();

}
