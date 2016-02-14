#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "util.h"
#include "keygen.h"
#include "tables.h"

void F_Function(unsigned int*,int);
void Expansion_Function(unsigned int*, unsigned int*);
void SBox_Function(unsigned int*, unsigned int*);
void Permutation_Function(unsigned int*);
void K_Function(unsigned int*,int);
#endif // F_FUNCTIONS_H_INCLUDED
