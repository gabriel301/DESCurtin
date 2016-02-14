#ifndef KEYGEN_H_INCLUDED
#define KEYGEN_H_INCLUDED
#include "tables.h"
#include "util.h"

//All Sub-keys (in keygen.cpp)
extern unsigned int keys[16][48];

void shiftKey(unsigned int*,int);
void keyPermutation1(unsigned int*, unsigned int*);
void keyPermutation2(unsigned int*, unsigned int*);
void keyGeneration(string);
void keyGeneration(unsigned int*);

#endif // KEYGEN_H_INCLUDED
