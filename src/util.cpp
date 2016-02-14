//This file contains all the conversion functions
#include "util.h"

//This function converts a char string into bits
void char2bit(string str, unsigned int *bitRep)
{
     stack<unsigned int> stk;
     int n = str.length();
          //It takes each char of the string and transform it in a byte (8 bits)
     for(int i=0;i<n;i++)
     {
          // [j+1] -> Matrix Linearization
          for(int j=0;j<8;j++)
            bitRep[(i*8)+j] = (str[i]>>j) & 1; //Bitwise operation to extract the less significant bit of a number.


          //The array is in reverse order, so, we need to fix it
          //i*8 is the base position of array in the round.
          //After transform char into bit, the final position is (i*8)+8;
          for(int j=(i*8);j<(i*8)+8;j++)
          {
            stk.push(bitRep[j]);
          }
          for(int j=(i*8);j<(i*8)+8;j++)
          {
            bitRep[j] = stk.top();
            stk.pop();
          }

     }

}

//This Function converts a Bit array into a number
unsigned long bit2long(unsigned int* p, int arraySize)
{


    unsigned long v=0;
    for (int i=0;i<arraySize; i++) {
        if (p[i] == 1)
            v = (v << 1) | 1;
        else if (p[i] == 0 )
            v <<= 1;

    }

    return v;
}

//This Function converts a Bit array into a string
string bit2char (unsigned int* p, int arraySize)
{

    string str;
    int v=0;
    for (int i=0;i<arraySize; i++) {
        //If i%8==0, we have 8 bits, that is, a character
        if(i>0 && i%8==0)
        {
            str += v;
            v=0;
        }

        //Bitwise operation to convert binary into decimal
        if (p[i] == 1)
            v = (v << 1) | 1;
        else if (p[i] == 0 )
            v <<= 1;

    }
    str += v;
    return str;
}

//This Function converts a number into a bit array
void long2bin(unsigned int* bitArray, unsigned long num, int arraySize)
{

    stack<unsigned int> stk;

    for(int j=0;j<arraySize;j++)
            bitArray[j] = (num>>j) & 1;

    for(int j=0;j<arraySize;j++)
    {
        stk.push(bitArray[j]);
    }

    for(int j=0;j<arraySize;j++)
    {
        bitArray[j] = stk.top();
        stk.pop();
    }

}

//This Function converts a Bit array into a number
unsigned int bit2int(unsigned int* p, int arraySize)
{
    unsigned int v=0;
    for (int i=0;i<arraySize; i++) {
        if (p[i] == 1)
            v = (v << 1) | 1;
        else if (p[i] == 0 )
            v <<= 1;

    }

    return v;
}

//This Function converts a number into a bit array
void int2bin(unsigned int* bitArray,int num, int arraySize)
{

    stack<unsigned int> stk;

    for(int j=0;j<arraySize;j++)
    {
        if(j<=num)
          bitArray[j] = (num>>j) & 1;
        else
            bitArray[j] =0;

    }


    for(int j=0;j<arraySize;j++)
    {
        stk.push(bitArray[j]);
    }

    for(int j=0;j<arraySize;j++)
    {
        bitArray[j] = stk.top();
        stk.pop();
    }

}
