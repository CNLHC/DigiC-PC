#pragma once
#include <list>
#include"FTDUtil.h"

typedef std::list<int8_t> typDigiCPack;
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
		typDigiCPack PacketData(int8_t(&data)[15]);
};

class DigiCDriver {

public:
	/*!
	constructor
	*/
	DigiCDriver();
	void sendPacket(typDigiCPack& pack);

private:
	FTDUtil mFTDHandle;
	
};

