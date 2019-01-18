#include "DigiCDriver.h"
#include <string>
#include <sstream>
#include <fstream>
 DigiCDataUtil::DigiCDataUtil() {}


typDigiCPack
DigiCDataUtil::PacketData(uint8_t(&data)[12]) {
	typDigiCPack tOut;
	int symbolIdx = 0;
	char tSymbolLiteral[10];
	std::stringstream ss;
	for (symbolIdx; symbolIdx < 4; ++symbolIdx) {
		int32_t  tSymbol;
		if (symbolIdx == 0) {
			tSymbol =((data[2]) <<24)&(0xFF000000);
			tSymbol += ((data[0]) <<16)&(0x00FF0000);
			tSymbol += ((data[1]) <<8)&(0x0000FF00);
			tSymbol += ((0x9c)&(0x000000FF));
		}
		else if (symbolIdx==3){
			tSymbol =((0x00) <<24)&(0xFF000000);
			tSymbol += ((0x00) <<16)&(0x00FF0000);
			tSymbol += ((0x00) <<8)&(0x0000FF00);
			tSymbol += ((data[11])&(0x000000FF));
		}
		else {
			tSymbol =  ((data[symbolIdx*4-1]) <<24)&(0xFF000000);
			tSymbol += ((data[symbolIdx*4 ]) <<16)&(0x00FF0000);
			tSymbol += ((data[symbolIdx*4+1]) <<8)&(0x0000FF00);
			tSymbol += ((data[symbolIdx*4+2])&(0x000000FF));
		}

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
void 
DigiCDataUtil::GenerateDigiCFile(std::string infp, std::string outfp) {

	std::fstream infs;
	std::fstream outfs;
	int64  inputFileLength;

	infs.open(infp,  std::fstream::binary | std::fstream::in);
	outfs.open(outfp,  std::fstream::binary | std::fstream::out);

	infs.seekg(0,std::ios::end);
	inputFileLength = infs.tellg();
	infs.seekg(0, std::ios::beg);


	bool loopingState=true;

	while(loopingState){
		uint8_t buf[12] = { 0 };
		if (inputFileLength- infs.tellg() >12) 
			infs.read((char*)buf,12);
		else {
			infs.read((char*)buf,inputFileLength-infs.tellg());
			loopingState = false;
		}
		//localStream.write((char*)buf, 14);
		typDigiCPack tPack;
		tPack=PacketData(buf);
		for (auto &i : tPack) 
			outfs << i;
		printf("%.3f%%\n", (double)((double)infs.tellg() * 100 / (double)inputFileLength));
	}
	infs.close();
	outfs.close();
}
