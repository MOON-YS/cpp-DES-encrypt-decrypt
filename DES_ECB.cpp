#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <bitset>
#include <sstream>
#define ull_int unsigned long long int 
#define ul_int unsigned long int 
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15

using namespace std;
//tables
int roundRotationTable[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
int PC2[48] = {
	13, 16, 10, 23, 0, 4,
	2, 27, 14, 5, 20, 9,
	22, 18, 11, 3, 25, 7,
	15, 6, 26, 19, 12, 1,
	40, 51, 30, 36, 46, 54,
	29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52,
	45, 41, 49, 35, 28, 31
};
int SBOX[8][4][16] = {
	{
		{E, 4, D, 1, 2, F, B, 8, 3, A, 6, C, 5, 9, 0, 7},
		{0, F, 7, 4, E, 2, D, 1, A, 6, C, B, 9, 5, 3, 8},
		{4, 1, E, 8, D, 6, 2, B, F, C, 9, 7, 3, A, 5, 0},
		{F, C, 8, 2, 4, 9, 1, 7, 5, B, 3, E, A, 0, 6, D}
	},
	{
		{F, 0 ,8, E, 6, B, 3, 4, 9, 7, 2, D, C, 0, 5, A},
		{3, D, 4, 7, F, 2, 8, E, C, 0, 1, A, 6, 9, B, 5},
		{0, E, 7, B, A, 4, D, 1, 5, 8, C, 6, 9, 3, 2, F},
		{D, 8, A, 1, 3, F, 4, 2, B, 6, 7, C, 0, 5, E, 9}
	},
	{
		{A, 0, 9, E, 6, 3, F, 5, 1, D, C, 7, B, 4, 2, 8},
		{D, 7, 0, 9, 3, 4, 6, A, 2, 8, 5, E, C, B, F, 1},
		{D, 6, 4, 9, 8, F, 3, 0, B, 1, 2, C, 5, A, E, 7},
		{1, A, D, 0, 6, 9, 8, 7, 4, F, E, 3, B, 5, 2, C}
	},
	{
		{7, D, E, 3, 0, 6, 9, A, 1, 2, 8, 5, B, C, 4, F},
		{D, 8, B, 5, 6, F, 0, 3, 4, 7, 2, C, 1, A, E, 9},
		{A, 6, 9, 0, C, B, 7, D, F, 1, 3, E, 5, 2, 8, 4},
		{3, F, 0, 6, A, 1, D, 8, 9, 4, 5, B, C, 7, 2, E}
	},
	{
		{2, C, 4, 1, 7, A, B, 6, 8, 5, 3, F, D, 0, E, 9},
		{E, B, 2, C, 4, 7, D, 1, 5, 0, F, A, 3, 9, 8, 6},
		{4, 2, 1, B, A, D, 7, 8, F, 9, C, 5, 6, 3, 0, E},
		{B, 8, C, 7, 1, E, 2, D, 6, F, 0, 9, A, 4, 5, 3}
	},
	{
		{C, 1, A, F, 9, 2, 6, 8, 0, D, 3, 4, E, 7, 5, B},
		{A, F, 4, 2, 7, C, 9, 5, 6, 1, D, E, 0, B, 3, 8},
		{9, E, F, 5, 2, 8, C, 3, 7, 0, 4, A, 1, D, B, 6},
		{4, 3, 2, C, 9, 5, F, A, B, E, 1, 7, 6, 0, 8, D}
	},
	{
		{4, B, 2, E, F, 0, 8, D, 3, C, 9, 7, 5, A, 6, 1},
		{D, 0, B, 7, 4, 9, 1, A, E, 3, 5, C, 2, F, 8, 6},
		{1, 4, B, D, C, 3, 7, E, A, F, 6, 8, 0, 5, 9, 2},
		{6, B, D, 8, 1, 4, A, 7, 9, 5, 0, F, E, 2, 3, C}
	},
	{
		{D, 2, 8, 4, 6, F, B, 1, A, 9, 3, E, 5, 0, C, 7},
		{1, F, D, 8, A, 3, 7, 4, C, 5, 6, B, 0, E, 9, 2},
		{7, B, 4, 1, 9, C, E, 2, 0, 6, A, D, F, 3, 5, 8},
		{2, 1, E, 7, 4, A, 8, D, F, C, 9, 0, 3, 5, 6, B}
	}
};
int IP[64] = {
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 21, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 33, 23, 15, 7,
	56, 48, 40, 32, 24, 16, 8, 0,
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6
};
int IPi[64] = {
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25,
	32, 0, 40, 8, 48, 16, 56, 24
};
int EP[48] = {
	31, 0, 1, 2, 3, 4,
	3, 4, 5, 6, 7, 8,
	7, 8, 9, 10, 11, 12,
	11, 12, 13, 14, 15, 16,
	15, 16, 17, 18, 19, 20,
	19, 20, 21, 22, 23, 24,
	23, 24, 25, 26, 27, 28,
	27, 28, 29, 30, 31, 0
};
int PBOX[32] = {
	15, 6, 19, 20, 28, 11, 27, 16,
	0, 14, 22, 25, 4, 17, 30, 9,
	1, 7, 23, 13, 31, 26, 2, 8,
	18, 12, 29, 5, 21, 10, 3, 24
};

ull_int expandIPText48bit(ull_int R) {
	ull_int result = 0;
	for (int i = 0; i < 48; i++) {
		result <<= 1;
		result |= bitset<32>(R).test(EP[i]);
	}
	return result;
}
ull_int transSBOX(ull_int R[]) {
	int x;//b1,b2,b3,b4
	int y;// b0, b5
	ull_int result = 0;
	for (int i = 0; i < 8; i++) {
		x = 0;
		y = 0;
		for (int j = 0; j < 6; j++) {
			if (j == 1 || j == 2 || j == 3 || j == 4) {
				x = bitset<4>(x).set(j - 1, bitset<6>(R[i]).test(j)).to_ulong();
			}
			else {
				if (j == 5)y = bitset<2>(y).set(1, bitset<6>(R[i]).test(j)).to_ulong();
				else y = bitset<2>(y).set(j, bitset<6>(R[i]).test(j)).to_ulong();
			}
		}
		result <<= 4;
		result |= SBOX[i][y][x];
	}
	return result;
}
ull_int transPBOX(ull_int R) {
	ull_int result = 0;
	for (int i = 0; i < 32; i++) {
		result = (bitset<32>(result).set(i, bitset<32>(R).test(PBOX[i])).to_ullong());
	};
	return result;
}
void seperate6x8(ull_int input, ull_int result[]) {
	int count = 0;
	int index = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			result[i] <<= 1;
			result[i] |= bitset<48>(input).test(47);
			input <<= 1;
		}
	}
}
void divideIP32bit(ull_int IPtext, ull_int* L, ull_int* R) {
	*L = IPtext >> 32;
	*R = IPtext << 32;
	*R >>= 32;
}
void circularLeftShift(ull_int* num, int n) {

	bool temp;
	ull_int mask28bit = 0b0000000000000000000000000000000000001111111111111111111111111111;
	for (int i = 0; i < n; i++) {
		temp = bitset<28>(*num).test(27);
		*num <<= 1;
		*num &= mask28bit;
		*num = bitset<28>(*num).set(0, temp).to_ullong();
	}
}
ull_int tpPC2Sub28bit(ull_int subKey) {
	ull_int result = 0;
	for (int i = 0; i < 48; i++) {
		result <<= 1;
		result |= bitset<56>(subKey).test(PC2[i]);
	}
	return result;
}
void initCD(ull_int* c, ull_int* d, ull_int key) {
	//divide key
	ull_int lMask = 0b11111111111111111111111111110000000000000000000000000000;
	ull_int rMask = 0b00000000000000000000000000001111111111111111111111111111;
	*c = (key & lMask) >> 28;
	*d = key & rMask;
}
void genSubKey(int* round, ull_int key, ull_int* c, ull_int* d, ull_int subKeys[]) {

	circularLeftShift(d, roundRotationTable[*round]);
	circularLeftShift(c, roundRotationTable[*round]);

	subKeys[*round] = tpPC2Sub28bit((*c << 28) | *d);
	*round += 1;
}
void keyGen(ull_int blocks[], int blockNum, string keyText, ull_int subKeys[]) {
	//for key
	ull_int key = 0;
	for (int i = 0; i < keyText.length(); i++) {
		key <<= 8;
		key |= bitset<8>(keyText[i]).to_ullong();
	}

	ull_int c, d;


	initCD(&c, &d, key);
	int round = 0;
	//generate 16 subkey
	for (int i = 0; i < 16; i++) {
		genSubKey(&round, key, &c, &d, subKeys);
	}
}
void DES_ECB_encrypt(ull_int blocks[], int blockNum, string keyText) {


	ull_int subKeys[16];


	keyGen(blocks, blockNum, keyText, subKeys);

	//for chiper
	ull_int IPtext;
	ull_int L, R;

	//Loop For all Blocks
	for (int i = 0; i < blockNum; i++) {
		IPtext = blocks[i];
		L = 0;
		R = 0;

		divideIP32bit(IPtext, &L, &R); // L[0] ,R[0] Ready

		// subKey(48bit) done, L , R (32bit) done 
		// excute loop 16 time
		ull_int L_next;
		ull_int R_next;
		for (int j = 0; j < 16; j++) {
			L_next = R;
			ull_int expanded = expandIPText48bit(R);
			R_next = expanded ^ subKeys[j];

			ull_int seperated[8] = { 0,0,0,0,0,0,0,0 };
			seperate6x8(R_next, seperated);

			R_next = transSBOX(seperated);
			R_next = transPBOX(R_next);
			R_next ^= L;

			L = L_next;
			R = R_next;
		}
		L <<= 32;
		R ^= L;//R is 64bit data before inverse IP transform
		blocks[i] = R;
	}
}
void DES_ECB_decrypt(ull_int blocks[], int blockNum, string keyText) {

	ull_int subKeys[16];
	keyGen(blocks, blockNum, keyText, subKeys);

	ull_int L;
	ull_int R;
	ull_int chiper;

	for (int i = 0; i < blockNum; i++) {
		ull_int L_Next;
		ull_int R_Next;
		chiper = blocks[i];
		L_Next = chiper >> 32;
		R_Next = chiper << 32;
		R_Next >>= 32;
		//cout << bitset<64>(blocks[i]) << endl;
		for (int k = 0; k < 16; k++) {

			R = L_Next;

			ull_int expanded = expandIPText48bit(R);
			L = expanded ^ subKeys[15 - k]; //from 15 to 0

			ull_int seperated[8] = { 0,0,0,0,0,0,0,0 };
			seperate6x8(L, seperated);

			L = transSBOX(seperated);
			L = transPBOX(L);
			L ^= R_Next;

			L_Next = L;
			R_Next = R;

		}
		//merge
		L <<= 32;
		L = R ^ L;
		//cout << bitset<64>(blocks[i]) << endl;
		blocks[i] = L;
	}

}
void bitTOString(ull_int blocks[], string &result, int blocksNum) {
	int length = blocksNum;
	string s;
	string bit64;

	for (int i = 0; i < length; i++) {
		bit64 = bitset<64>(blocks[i]).to_string();
		stringstream sstream(bit64);

		while (sstream.good()) {
			bitset<8> bits;
			sstream >> bits;
			char c = char(bits.to_ulong());
			s += c;
		}
		result = s;
	}
}
void bufferToblocks(int plainTextFullSize, char* buffer, ull_int blocks[], int blockNum) {
	int* plain8bit = new int[plainTextFullSize];
	for (int i = 0; i < plainTextFullSize; i++) {
		plain8bit[i] = bitset<64>(buffer[i]).to_ullong();
	}


	for (int i = 0; i < blockNum; i++) {
		blocks[i] = 0b0;
		for (int j = 0; j < 8; j++) {
			blocks[i] <<= 8;
			blocks[i] |= plain8bit[(i * 8) + j];
		}
	}

	delete[] plain8bit;
}