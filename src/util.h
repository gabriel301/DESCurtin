#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <string>
#include <cstring>
#include <stack>
#include <iostream>
using namespace std;
//This file contains all the conversion functions
//These functions convert a char string into bits
void char2bit(string str, unsigned int *);

//This Function converts a number into a bit array
void long2bin(unsigned int*, unsigned long,int);
void int2bin(unsigned int*,int,int);

//This Function converts a Bit array into a string
string bit2char (unsigned int*, int);

//This Function converts a Bit array into a number
unsigned long bit2long(unsigned int*, int);
unsigned int bit2int(unsigned int*, int);
#endif // UTIL_H_INCLUDED
