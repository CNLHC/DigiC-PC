#include "FTDUtil.h"
#include "ftd2xx.h"
#include "libMPSSE_spi.h"
#include <stdio.h>
#include <stdexcept>



#define APP_CHECK_STATUS(exp) { if(exp!=FT_OK){printf("%s:%d:%s(): status(0x%x) \
!= FT_OK\n",__FILE__, __LINE__, __FUNCTION__,exp);exit(1);}else{;}};

FTDUtil::FTDUtil()
{
	printf("FTDUtil:Constructor:\nhandle=0x%x\n", this->mHandle);
	this->mSPIChannelConf.ClockRate = 5000000;
	this->mSPIChannelConf.LatencyTimer =1;
	this->mSPIChannelConf.configOptions =
		SPI_CONFIG_OPTION_MODE2 | SPI_CONFIG_OPTION_CS_DBUS3;
	this->mSPIChannelConf.Pin = 0x00000000;
	FT_STATUS status = SPI_OpenChannel(0, &mHandle);
	if (!status == FT_OK) {
		printf("");
		throw std::runtime_error("");
	}
	printf("");
	status = SPI_InitChannel(mHandle,&mSPIChannelConf);
	if (!status == FT_OK) {
		printf("");
		throw std::runtime_error("");
	}
	printf("");
}
FTDUtil::~FTDUtil()
{
}
int FTDUtil::lsDev()
{
FT_STATUS ftStatus;
FT_DEVICE_LIST_INFO_NODE *devInfo;
DWORD numDevs;
ftStatus = FT_CreateDeviceInfoList(&numDevs);
if (ftStatus == FT_OK) 
	printf("", numDevs);
else
	printf("" );
if (numDevs > 0) {
	auto devInfo = new FT_DEVICE_LIST_INFO_NODE[numDevs];
	ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
	if (ftStatus == FT_OK) 
		for (int i = 0; i < numDevs; i++) {
			printf(" �豸%d:\n", i);
			printf(" Flags=0x%x\n", devInfo[i].Flags);
			printf(" Type=0x%x\n", devInfo[i].Type);
			printf(" ID=0x%x\n", devInfo[i].ID);
			printf(" LocId=0x%x\n", devInfo[i].LocId);
			printf(" SerialNumber=%s\n", devInfo[i].SerialNumber);
			printf(" Description=%s\n", devInfo[i].Description);
			printf(" ftHandle=0x%x\n", devInfo[i].ftHandle);
		}
	delete[] devInfo;
 }
return numDevs;
}
int FTDUtil::lsSPIChannel() {
	FT_STATUS tStatus;
	uint32 channels;
	tStatus = SPI_GetNumChannels(&channels);
	APP_CHECK_STATUS(tStatus);
	printf("Number of available SPI channels = %d\n", channels);
	return channels;
}

void FTDUtil::SPIWriteByte(uint8 slaveAddress, uint8 address, uint32 data) {
	uint32 sizeToTransfer = 0;
	uint32 sizeTransfered = 0;
	bool writeComplete = 0;
	uint32 retry = 0;
	bool state;
	FT_STATUS status;
	uint8 buffer[256];
	/* Write command EWEN(with CS_High -> CS_Low) */
	sizeToTransfer = 4;
	sizeTransfered = 0;
	buffer[0] =data>>24;/* SPI_EWEN -> binary 10011xxxxxx (11bits) */
	buffer[1] = data >> 16;
	buffer[2] = data >> 8;
	buffer[3] =data&0x00FF;
	status = SPI_Write(this->mHandle,buffer, sizeToTransfer, &sizeTransfered,
		SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES|
		SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE
	);
	APP_CHECK_STATUS(status);
	APP_CHECK_STATUS(status);
	printf("FTDUtil:SPIWriteByte:��������%x\n",data);
}
void FTDUtil::SPIWriteByteArray(uint8 * Data,long long int sizeToTransfer) {
	uint32 sizeTransfered = 0;
	FT_STATUS status;
	unsigned long long int  actualSizeToTransfer =0;
	uint8 * SendingBuffer = new uint8[2 * sizeToTransfer];
	for (int i = 0; i < sizeToTransfer; i++) {
		switch (Data[i]) {
			case 0x4a:{
				SendingBuffer[actualSizeToTransfer++] = 0x4d;
				SendingBuffer[actualSizeToTransfer++] = 0x4a^0x20;
				break;
			}
			case 0x4d: {
				SendingBuffer[actualSizeToTransfer++] = 0x4d;
				SendingBuffer[actualSizeToTransfer++] = 0x4d^0x20;
				break;
			}
			default: {
				SendingBuffer[actualSizeToTransfer++] = Data[i];
				break;
			}
		}
	}
	status = SPI_Write(this->mHandle,SendingBuffer,actualSizeToTransfer, &sizeTransfered,
		SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES|
		SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE
	);
	APP_CHECK_STATUS(status);
	APP_CHECK_STATUS(status);
	delete [2 * sizeToTransfer]SendingBuffer;
}


