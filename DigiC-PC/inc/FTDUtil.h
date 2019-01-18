#pragma once
#include "ftd2xx.h"
#include "libMPSSE_spi.h"

class FTDUtil
{
public:
	FTDUtil();
	~FTDUtil();
	int lsDev();
	int lsSPIChannel();
	void SPIWriteByte(uint8 slaveAddress, uint8 address, uint32 data);
	void SPIWriteByteArray(uint8 * Data,long long int);
	ChannelConfig mSPIChannelConf;
	FT_HANDLE mHandle;
private :
};

