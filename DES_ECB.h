#pragma once
#include<string>
#include<bitset>
#include <sstream>
#define ull_int unsigned long long int

using namespace std;
#ifndef DES_ECB

void DES_ECB_encrypt(ull_int blocks[], int blockNum, string keyText);
void DES_ECB_decrypt(ull_int blocks[], int blockNum, string keyText);
void bitTOString(ull_int blocks[], string &result, int blocksNum);
void bufferToblocks(int plainTextFullSize, char* buffer, ull_int blocks[], int blockNum);
#endif DES_ECB