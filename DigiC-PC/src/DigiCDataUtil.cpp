#include "DigiCDriver.h"
#include <string>
#include <sstream>
 DigiCDataUtil::DigiCDataUtil() {}


typDigiCPack
DigiCDataUtil::PacketData(int8_t(&data)[15]) {
	typDigiCPack tOut;
	int symbolIdx = 0;
	char tSymbolLiteral[10];
	std::stringstream ss;
	for (symbolIdx; symbolIdx < 4; ++symbolIdx) {
		int32_t tSymbol = (symbolIdx == 0 ? 0xff : data[symbolIdx * 4 - 1]) << 24;
		tSymbol += ((data[symbolIdx * 4 ]) <<16)&(0x00FF0000);
		tSymbol += ((data[symbolIdx * 4+1 ]) <<8)&(0x0000FF00);
		tSymbol += ((data[symbolIdx * 4 + 2])&(0x000000FF));
		sprintf(tSymbolLiteral, "%08x", tSymbol);


		//reverse
		for (int i = 0; i < 4; i++) 
			std::swap(tSymbolLiteral[i], tSymbolLiteral[7 - i]);

		for (int k = 0; k<8; k++) {
			switch (tSymbolLiteral[k]) {
			case '1':tSymbolLiteral[k] = '4'; break;
			case '2':tSymbolLiteral[k] = '8'; break;
			case '3':tSymbolLiteral[k] = 'c'; break;
			case '4':tSymbolLiteral[k] = '1'; break;
			case '5':tSymbolLiteral[k] = '5'; break;
			case '6':tSymbolLiteral[k] = '9'; break;
			case '7':tSymbolLiteral[k] = 'd'; break;
			case '8':tSymbolLiteral[k] = '2'; break;
			case '9':tSymbolLiteral[k] = '6'; break;
			case 'a':tSymbolLiteral[k] = 'a'; break;
			case 'b':tSymbolLiteral[k] = 'e'; break;
			case 'c':tSymbolLiteral[k] = '3'; break;
			case 'd':tSymbolLiteral[k] = '7'; break;
			case 'e':tSymbolLiteral[k] = 'b'; break;
			case 'f':tSymbolLiteral[k] = 'f'; break;
			}
		}

		for (int i = 0; i < 4; i++) {
			unsigned int t1;
			ss.str("");
			ss << tSymbolLiteral[2 * i];
			ss<<tSymbolLiteral[2*i+1];
			sscanf(ss.str().c_str(), "%x", &t1);
			tOut.push_back(t1);
		}
	}

	return tOut;
}