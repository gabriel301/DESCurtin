#include "functions.h"
//This file contains all functions performed in one round of DES (Feisal Cipher)

//This function performs the Expansion/Permutation function (E/P)
//The input is a 32 bits array, and the output is a 48 bits array
void Expansion_Function(unsigned int *oldBlock, unsigned int *expandedBlock)
{
    for(int i=0;i<48;i++)
        expandedBlock[i] = oldBlock[EP[i]-1];
}

//This function performs the SBox substitution
//The input is a 48 bits array, and the output is a 32 bits array
void SBox_Function(unsigned int *oldBlock, unsigned int *compressedBlock)
{
    int beg,end,row,col,index;
    unsigned int aux[4]; //Auxiliary array that stored the Sbox value in binary
    beg = 0; //flag to the beginning of the 48 bits array
    end = 5; //flag to the end of the 48 bits array
    index = 0; //flag that controls the array that stores substitutions
    unsigned int rowBin[2], colBin[4]; // arrays that store both row and column of Sbox in binary
    //Execute this until the end of 48 bits array
    while(end<48)
    {
        //Extract both first and last bits in a range of 6 bits
        rowBin[0] = oldBlock[beg];
        rowBin[1] = oldBlock[end];

        //Extract the 4 bits in the middle of beg and end
        for(int i=beg+1,j=0;i<end;i++,j++)
        {
            colBin[j] = oldBlock[i];
        }

        //Convert Row and Col to numbers
        row = bit2int(rowBin,2);
        col = bit2int(colBin,4);

        //Select the correspondent Sbox number and transforms it in binary
        switch(end)
        {
            case 5:
                   int2bin(aux,(int)S1[row][col],4);
                   break;
            case 11:
                   int2bin(aux,(int)S2[row][col],4);
                   break;
            case 17:
                   int2bin(aux,(int)S3[row][col],4);
                   break;
            case 23:
                   int2bin(aux,(int)S4[row][col],4);
                   break;
            case 29:
                   int2bin(aux,(int)S5[row][col],4);
                   break;
            case 35:
                   int2bin(aux,(int)S6[row][col],4);
                   break;
            case 41:
                   int2bin(aux,(int)S7[row][col],4);
                   break;
            case 47:
                   int2bin(aux,(int)S8[row][col],4);
                   break;

        }

        //Append the 4 bits array generated to the 32 bits array
        for(int j=0;j<4;j++,index++)
            compressedBlock[index] = aux[j];


        beg+=6;
        end+=6;

    }
}

//This function performs the Permutation
//The input is a 32 bits array, and the output is a 32 bits array
void Permutation_Function(unsigned int* block)
{
    unsigned int aux[32];
    for(int i=0;i<32;i++)
        aux[i] = block[P[i]-1];

    for(int i=0;i<32;i++)
    {
        block[i] = aux[i];
    }
}

//This function performs the F function
//The input is a 32 bits array, and the output is a 32 bits array
void F_Function(unsigned int* block,int round)
{
    unsigned int aux[48];

    //Expand the 32 bits array in a 48 bits array
    Expansion_Function(block,aux);

    //XOR between the extended array and the round key (pre-computated)
    for(int i=0;i<48;i++)
        aux[i] = aux[i]^keys[round][i];

    //S-boxes substitutions
    SBox_Function(aux,block);

    //Permutation
    Permutation_Function(block);
}


//This function performs the K function
//The input is a 64 bits array, and the output is a 64 bits array
void K_Function(unsigned int* block,int round)
{
    unsigned int left[32], right[32], auxleft[32];

    //Splitting the block in two halves
    for(int i=0;i<32;i++)
        left[i] = block[i];

    for(int i=32;i<64;i++)
    {
        right[i-32] = block[i];
        auxleft[i-32] = block[i]; //Stored the old value of the right side to perform the swap later
    }

    //Applies the F function in the right side
    F_Function(right,round);

    for(int i=0;i<32;i++)
    {
         right[i] = left[i]^right[i]; //XOR between left side and right side
         left[i] = auxleft[i]; // swap the left side value to the old right side value
    }

    //Merges the sides
    for(int i=0;i<32;i++)
    {
       block[i] = left[i] ;
    }

    for(int i=32;i<64;i++)
    {
        block[i]=right[i-32];
    }



}
