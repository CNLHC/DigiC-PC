#include "DigiCDriver.h"
#include"FTDUtil.h"
#include "spi.h"
#include <cassert>

DigiCDriver::DigiCDriver() {
	this->mFTDHandle.lsSPIChannel();
}
void 
DigiCDriver::sendPacket(typDigiCPack &pack) {
	assert(pack.size() == 16);
	uint8_t tSendBuffer[16];
	int idx = 0;
	for (auto i = pack.begin(); i != pack.end(); i++)
		tSendBuffer[idx++] = *i;
	mFTDHandle.SPIWriteByteArray(tSendBuffer, 16);
}




