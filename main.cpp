#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include "DES_ECB.h"
#define ull_int unsigned long long int 

using namespace std;

void main() 
{
	string line;

	string path = "D:\\Downlowads\\Crypto\\test.txt";

	int fileSize;
	int plainSize;
	char* buffer;
	int blockNum;

	ifstream file(path, ios::binary);
	if (file.is_open()) {
		file.seekg(0, ios::end);
		fileSize = file.tellg();
		file.seekg(0, ios::beg);
		plainSize = 8;

		//text(String) To 64 bit binary
		while (plainSize < fileSize) {
			plainSize += 8;
		}
		cout << "File Text Size :" << fileSize << endl;
		cout << "Plain Text Size : " << plainSize << endl;
		buffer = new char[plainSize];

		file.read(buffer, fileSize);
		file.close();
		//file read end
		cout << endl;
		cout << "plain text : " << endl;
		for (int i = 0; i < plainSize; i++) {
			if (i > fileSize-1) buffer[i] = ' ';
			cout << buffer[i];
		}
		cout << endl;
		blockNum = plainSize / 8;
		cout << endl << blockNum << " blocks" << endl;

		//Text to binary
		ull_int* blocks = new ull_int[blockNum];
		bufferToblocks(plainSize, buffer, blocks, blockNum);

		string keyText = "abcdefg";

		cout << "Key: " << keyText << endl;
		DES_ECB_encrypt(blocks, blockNum, keyText);
		string resultTextEn = "";
		cout << endl <<"Encrypted" << endl;
		bitTOString(blocks, resultTextEn, blockNum);

		cout << resultTextEn;


		DES_ECB_decrypt(blocks, blockNum, keyText);
		string resultTextDe ="";
		cout << endl;
		
		bitTOString(blocks, resultTextDe, blockNum);
		cout << endl << "Decrypted" << endl;

		cout << resultTextDe;

		cout << endl;
	}

	else {
		cerr << "Unable to open File" << endl;
		return;
	}
	delete[] buffer;
}