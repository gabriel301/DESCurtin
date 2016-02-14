#include "keygen.h"
#include <iostream>

using namespace std;
//This file contains all functions needed to generate the subkeys
//All Sub-keys
unsigned int keys[16][48];

//This function shifts the 2 28 bits key half
void shiftKey(unsigned int* key, int round)
{

    int shiftedBits[2]; //Array to store the shifted bits
    unsigned int left[28],right[28]; //arrays to store the key
    unsigned long numShifted; //Number of bits that will be shifted

    int shifts = LEFT_SHIFTS[round];

    //Split the key in two halves
    for(int i=0;i<28;i++)
        left[i] = key[i];

    for(int i=28;i<56;i++)
        right[i-28] = key[i];


    //Left side shift
     for(int i=0;i<shifts;i++)
        shiftedBits[i] = left[i];  //Extract the most significant bits


     numShifted = bit2long(left,28); //Convert the bit array in a number
     numShifted = numShifted<<shifts;   //Shift n bits, according to LEFT_SHIFTS table
     long2bin(left,numShifted,28);   // Convert the number in bits

     for(int i=0;i<shifts;i++)
         left[28-shifts+i] = shiftedBits[i]; //Put back the shifted bits in the end of array


    //right side shift
     for(int i=0;i<shifts;i++)
         shiftedBits[i] = right[i];  //Extract the most significant bits

     numShifted = bit2long(right,28); //Convert the bit array in a number
     numShifted = numShifted<<shifts;   //Shift n bits, according to LEFT_SHIFTS table
     long2bin(right,numShifted,28);   // Convert the number in bits
     for(int i=0;i<shifts;i++)
         right[28-shifts+i] = shiftedBits[i]; //Put back the shifted bits in the end of array


    //Join back the key
    for(int i=0;i<28;i++)
        key[i]=left[i];

    for(int i=28;i<56;i++)
        key[i] = right[i-28];

}

//This function performs the Permutation Choice 1
//The input is a 64 bits array, and the output is a 56 bits array
void keyPermutation1(unsigned int *key, unsigned int *newKey)
{

    for(int i=0;i<56;i++)
        newKey[i] = key[PC1[i]-1]; //Select the value according PC1 table in tables.h file

}

//This function performs the Permutation Choice 2
//The input is a 56 bits array, and the output is a 48 bits array
void keyPermutation2(unsigned int *key, unsigned int *subkey)
{

    for(int i=0;i<48;i++)
        subkey[i] = key[PC2[i]-1]; //Select the value according PC2 table in tables.h file

}

void keyGeneration(string txtkey)
{
    unsigned int key64[64];
    unsigned int key[56];
    unsigned int subkey[48];

    //If key > 8, it cut the remaining chars
    if(txtkey.length()>8)
        txtkey.resize(8);
    else if (txtkey.length()<8) //if key<8, it fills the string with a substring of the key
        txtkey+= txtkey.substr(0,8-txtkey.length());

    //Converting chars in binary
    char2bit(txtkey,key64);


    //Compressing the 64 bits key in 56 bits key
    keyPermutation1(key64, key);

    //Generating all sub-keys
    for(int i=0;i<16;i++)
    {
        shiftKey(key,i); // Shift the key
        keyPermutation2(key,subkey); //Contracts the key

        for(int j=0;j<48;j++)
        {
            keys[i][j] = subkey[j]; //Copy the subkey generated to keys' matrix
        }

    }
}


void keyGeneration(unsigned int* key64)
{

    unsigned int key[56];
    unsigned int subkey[48];

    keyPermutation1(key64, key);

    //Generating all sub-keys
    for(int i=0;i<16;i++)
    {
        shiftKey(key,i); // Shift the key
        keyPermutation2(key,subkey); //Contracts the key

        for(int j=0;j<48;j++)
        {
            keys[i][j] = subkey[j]; //Copy the subkey generated to keys' matrix
        }

    }
}

