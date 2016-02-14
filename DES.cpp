#include "DES.h"
//This file contains all other functions to implement DES

//This function performs the Initial Permutation in the block
//The input is a 64 bits array and the output is a 64 bits array
void Initial_Permutation_Function(unsigned int* block)
{
    unsigned int aux[64];
    for(int i=0;i<64;i++)
        aux[i] = block[IP[i]-1];

     for(int i=0;i<64;i++)
     {
          block[i] = aux[i];
     }
}

//This function performs the Inverse Initial Permutation in the block
//The input is a 64 bits array and the output is a 64 bits array
void Inverse_Initial_Permutation_Function(unsigned int* block)
{
     unsigned int aux[64];
     for(int i=0;i<64;i++)
        aux[i] = block[IIP[i]-1];

     for(int i=0;i<64;i++)
     {
          block[i] = aux[i];
     }
}

//This function performs the Swap Function in the block. It Swaps the two halves of 32 bits
//The input is a 64 bits array and the output is a 64 bits array
void Swap_Function(unsigned int* block)
{
     unsigned int left[32], right[32];

    //Splitting the block in two halves
    for(int i=0;i<32;i++)
        left[i] = block[i];


    for(int i=32;i<64;i++)
        right[i-32] = block[i];


    //Merging and Swapping the sides
    for(int i=0;i<32;i++)
    {
       block[i] = right[i] ;
    }

    for(int i=32;i<64;i++)
    {
        block[i]=left[i-32];
    }
}

void Encription(unsigned int* block)
{
    Initial_Permutation_Function(block);

    for(int i=0;i<16;i++)
        K_Function(block,i);
    Swap_Function(block);

    Inverse_Initial_Permutation_Function(block);

}

void Decription(unsigned int* block)
{
    Initial_Permutation_Function(block);
    for(int i=15;i>=0;i--)
        K_Function(block,i);
    Swap_Function(block);
    Inverse_Initial_Permutation_Function(block);
}
