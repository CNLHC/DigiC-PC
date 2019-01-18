#include "DigiCDriver.h"
#include"FTDUtil.h"
#include "spi.h"
#include <cassert>
#include <fstream>
#include<sstream>

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

void 
DigiCDriver::sendPacket(uint8 * data) {
	mFTDHandle.SPIWriteByteArray(data, 16);
}

void 
DigiCDriver::sendPackets(typDigiCPackList &packList) {
	uint8_t *tSendBuffer = new  uint8[16 * packList.size()];
	int idx = 0;
	for (auto &pack:packList)
		for (auto i = pack.begin(); i != pack.end(); i++)
			tSendBuffer[idx++] = *i;

	mFTDHandle.SPIWriteByteArray(tSendBuffer, 16*packList.size());
	delete[16 * packList.size()]tSendBuffer;
}
void 
DigiCDriver::sendMultiplePacket(std::list<typDigiCPack> & packets) {
	uint8_t tSendBuffer[10240];
	int symbolIdx=0;
	for (auto pack = packets.begin(); pack != packets.end();pack ++) {
		assert((*pack).size() == 16);
		int tidx = 0;
		for (auto byte = (*pack).begin(); byte != (*pack).end(); byte++) {
			tSendBuffer[tidx + 16 * symbolIdx] = *byte;
			tidx++;
		}
		symbolIdx ++;
		if (symbolIdx == 640) {
			mFTDHandle.SPIWriteByteArray(tSendBuffer,10240);
		}
	}
	//TODO
}

void 
DigiCDriver::sendFile(std::string filePath) {

	std::fstream fs;
	fs.open(filePath,  std::fstream::binary | std::fstream::in);
	std::fstream localStream;
	localStream.open("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\StreamingTest.mp4",  std::fstream::binary | std::fstream::out);
	fs.seekg(0,std::ios::end);
	int64 fileSize = fs.tellg();
	fs.seekg(0, std::ios::beg);
	printf("Encoding file:%s\n", filePath.c_str());
	typDigiCPackList tPackList;

	//uint8_t rawData[14] = { 0x16,0x23,0x12,0x75,0x62,0x01,0x02,0x19 };
	//typDigiCPack t;
	//fs.read((char *)(rawData + 8), 6);
	//t=mDataUtil.PacketData(rawData);
	//this->sendPacket(t);
	bool loopingState=true;



	while(loopingState){
		uint8_t buf[12] = { 0 };
		if (fileSize - fs.tellg() >12) 
			fs.read((char*)buf,12);
		else {
			fs.read((char*)buf,fileSize-fs.tellg());
			loopingState = false;
		}
		//localStream.write((char*)buf, 14);
		typDigiCPack tPack;
		tPack=mDataUtil.PacketData(buf);
		tPackList.push_back(tPack);
		if (tPackList.size() > 3000) {
			this->sendPackets(tPackList);
			tPackList.clear();
			//localStream.flush();
		}
		printf("%.3f%%\n", (double)((double)fs.tellg() * 100 / (double)fileSize));
	}
	this->sendPackets(tPackList);
	printf("Sending complete");
}

void DigiCDriver::sendDigiCFile(std::string DigiCFilePath) {
	int64 chunkSize = 500 * 16;
	std::fstream fs;
	fs.open(DigiCFilePath, std::fstream::binary | std::fstream::in);
	fs.seekg(0,std::ios::end);
	int64 fileSize = fs.tellg();
	fs.seekg(0, std::ios::beg);
	bool loopingState=true;
	if (fileSize % 16 != 0)
		printf("DigiC file may be corrupt\n");
	auto ChunkBuffer = new uint8[chunkSize];
	while (loopingState) {
		int64 res = fileSize - fs.tellg();
		if (res < chunkSize) {
			auto lastSendBuffer = new uint8[res];
			fs.read((char *)lastSendBuffer, res);
			this->mFTDHandle.SPIWriteByteArray(lastSendBuffer, res);
			delete[res]lastSendBuffer;
			loopingState = false;
		}
		else {
			fs.read((char *)ChunkBuffer,chunkSize);
			this->mFTDHandle.SPIWriteByteArray(ChunkBuffer,chunkSize);
		}
		printf("%.3f%%\n", (double)((double)fs.tellg() * 100 / (double)fileSize));
	}
}
