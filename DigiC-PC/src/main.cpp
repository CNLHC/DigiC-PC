#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio> 
#include <chrono>
#include <thread>
#include "DigiCDriver.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>

#define TESTBYTES 0x33

uint8_t rawData[4] = {
0x16,0x23,0x12, 0x75 };

uint8_t specialData1[15] = { 
	0x73,0xee,0x3d,0xf7,
	0x5c,0x91,0xcd,0x66,
	0x03,0x66,0x58,0x4c,
	0x8d,0xc2,0x9a };

uint8_t specialData0[16] =
{ 0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x00,0x00,0x15,0x15,0x15,0x15,0x15,0x15,0x15 };



int main() {
	Init_libMPSSE(); //This Line is important, DO NOT DELETE it!
	// And it MUST be placed here, at first line in main function. Otherwise, the spi channel can't open.
	//Why? May be the FTDI's black magic.

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0,255);
	DigiCDataUtil u1;
	DigiCDriver d1;
	//std::string fp("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\kio.bmp");
	//std::string fp("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\cut.avi");
	//std::string fp("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\casback.bmp");
	//d1.sendFile(fp);

	//d1.sendDigiCFile(std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\1064.wav.Digic"));
	//d1.sendDigiCFile(std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\cut.avi.Digic"));
	//d1.sendDigiCFile(std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\Sarabande.avi.Digic"));
	//d1.sendDigiCFile(std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\beihang.bmp.Digic"));

	//u1.GenerateDigiCFile(
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\1064.wav"),
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\1064.wav.Digic"));

	//u1.GenerateDigiCFile(
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\Sarabande.avi"),
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\Sarabande.avi.Digic"));

	//u1.GenerateDigiCFile(
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\Sarabande.h264"),
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\Sarabande.h264.Digic"));
	//u1.GenerateDigiCFile(
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\cut.webm"),
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\cut.webm.Digic"));
	//u1.GenerateDigiCFile(
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\beihang.bmp"),
	//	std::string("C:\\Users\\cn\\Desktop\\Project\\DigiC-PC\\beihang.bmp.Digic"));


	//system("pause");
	while (1) {
		d1.sendPacket(specialData0);
		//typDigiCPack a; 
		//a = u1.PacketData(UspecialData0);
		//d1.sendPacket(a);
	}
}
