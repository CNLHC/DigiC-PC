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
	this->mSPIChannelConf.ClockRate = 30000000;
	this->mSPIChannelConf.LatencyTimer =1;
	this->mSPIChannelConf.configOptions =
		SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3;
	this->mSPIChannelConf.Pin = 0x00000000;
	FT_STATUS status = SPI_OpenChannel(0, &mHandle);
	if (!status == FT_OK) {
		printf("错误:FTDUtil:Constructor:无法打开SPI端口\n");
		throw std::runtime_error("错误:FTDUtil:Constructor:无法打开SPI端口\n");
	}
	printf("FTDUtil:Constructor:SPI设备已经打开\n");
	status = SPI_InitChannel(mHandle,&mSPIChannelConf);
	if (!status == FT_OK) {
		printf("错误:FTDUtil:Constructor:无法初始化SPI端口");
		throw std::runtime_error("错误:FTDUtil:Constructor:无法初始化SPI端口");
	}
	printf("FTDUtil:Constructor:SPI设备已初始化\n");
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
	printf("可用设备数目: %d\n", numDevs);
else
	printf("无法创建设备列表" );
if (numDevs > 0) {
	auto devInfo = new FT_DEVICE_LIST_INFO_NODE[numDevs];
	ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
	if (ftStatus == FT_OK) 
		for (int i = 0; i < numDevs; i++) {
			printf(" 设备%d:\n", i);
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
		SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE |
		SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE);
	APP_CHECK_STATUS(status);
	APP_CHECK_STATUS(status);
	printf("FTDUtil:SPIWriteByte:发送数据%x\n",data);
}
