#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;
#define OK 0
#define ERR -1
#define KEY 0xa9




int FileConvert(char szOldFile[],char szNewFile[]);
long GetFileSize(char* filename);
void pJ(char str[],char inFile[],char outFile[]);

//chai fen
int cF(char str[],char inFile[],char outFile[]);


int code(char szOldFile[],char szNewFile[],char code[]);
bool decode(char szOldFile[],char szNewFile[],char code[]);

bool isCoded(char src[]);

#endif // CODE_H
