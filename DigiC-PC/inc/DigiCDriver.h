#pragma once
#include <list>
#include"FTDUtil.h"

typedef std::list<int8_t> typDigiCPack;
typedef std::list<std::list<int8_t>> typDigiCPackList;
class DigiCDataUtil {

	public:
		/*!
		constructor
		*/
		DigiCDataUtil();

		/*£¡
		Generate a Digic-Packtet
		\param data Bytes to transform. must be an length-15 int8_t array
		*/
		typDigiCPack PacketData(uint8_t(&data)[14]);
};

class DigiCDriver {

public:
	/*!
	constructor
	*/
	DigiCDriver();
	void sendPacket(typDigiCPack& pack);
	void sendMultiplePacket(std::list<typDigiCPack> & packets);
	void sendFile(std::string filePath);
	void sendPackets(typDigiCPackList &packList);

private:
	FTDUtil mFTDHandle;
	DigiCDataUtil mDataUtil;
	
};

