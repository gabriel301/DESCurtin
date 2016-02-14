#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED
#include "tables.h"
#include "functions.h"

void Initial_Permutation_Function(unsigned int*);
void Inverse_Initial_Permutation_Function(unsigned int*);
void Swap_Function(unsigned int*);
void Encription(unsigned int*);
void Decription(unsigned int*);

#endif // DES_H_INCLUDED
