#include <iostream>
#include "DES.h"
#include <fstream>
using namespace std;


int main()
{
    /*unsigned int plaintext[64] =
    {
        0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,
        0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1
    };
*/
    //Key w/ all bits 1 makes DES generate subkeys w/ only bits 1
   /* unsigned int key[64] =
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };*/
    ifstream plaintext;
    ofstream ciphertext;
    string fileSrc, keyt,buffer;
    char c;
    int option;
    unsigned int bits[64];

    //string keyt, text, cipher, text2;

    cout<<"1 - Encrypt text\n2 - Decrypt text\n3 - Exit\nOption: ";
    cin>>option;
    while(option!=3)
    {
        cin.ignore();
        if(option==1)
        {

            cout<<"Source File Destination (with extension): ";
            getline(cin,fileSrc);
            plaintext.open(fileSrc.c_str(),ios::binary);
            if(!plaintext)
            {
                cout<<"\nFailure open the plaintext file. Please check if file exists and filename is correct";
                return 0;
            }
            ciphertext.open("encrypted.txt",ios::binary);
             if(!ciphertext)
            {
                cout<<"\nFailure open the cipher file. Please check if file exists and filename is correct";
                return 0;
            }
            cout<<"Key: "<<endl;
            getline(cin,keyt);
            keyGeneration(keyt);
            while(!plaintext.eof())
            {
                buffer.clear();
                while(buffer.length()<8)
                {

                     plaintext.get(c);
                     if(plaintext.eof()) break;
                     buffer += c;

                }
                //Padding
                /*The code fill the string with 0 bits, and add a new line in the file
                with the number of 0 bits added*/
                if(buffer.length()<8)
                {
                    int remain = 8 - buffer.length();
                    unsigned int *padding;
                    buffer.resize(8);
                    char2bit(buffer,bits);
                    padding = new unsigned int[64];
                    int2bin(padding,remain*8,64);
                    Encription(bits);
                    Encription(padding);
                    buffer = bit2char(bits,64);
                    ciphertext<<bit2char(bits,64)<<bit2char(padding,64);
                }
                else
                {
                    char2bit(buffer,bits);
                    Encription(bits);
                    buffer = bit2char(bits,64);
                    ciphertext<<bit2char(bits,64);
                }

            }
            plaintext.close();
            ciphertext.close();

        }
        if(option==2)
        {
            cout<<"Source File Destination (with extension): ";
            getline(cin,fileSrc);
            plaintext.open(fileSrc.c_str(),ios::binary);
            if(!plaintext)
            {
                cout<<"\nFailure open the Cipher file. Please check if file exists and filename is correct";
                return 0;
            }
            ciphertext.open("decrypted.txt",ios::binary);
             if(!ciphertext)
            {
                cout<<"\nFailure open the Plaintext file. Please check if file exists and filename is correct";
                return 0;
            }

            //Get lenght of file
            int fileLength;
            plaintext.seekg(0,ios::end); //Set the pointer to the end of file
            fileLength = plaintext.tellg(); //Get the current position of the pointer
            plaintext.seekg(0,ios::beg); ////Set the pointer to the beginning of file

            cout<<"Key: "<<endl;
            getline(cin,keyt);
            keyGeneration(keyt);
            while(!plaintext.eof())
            {
                buffer.clear();

                while(buffer.length()<8)
                {

                     plaintext.get(c);
                     if(plaintext.eof()) break;
                     buffer += c;


                }
                //The Pointer has reached at the last 'valid' line
                //The last line of the file is the padding information
                if(fileLength - plaintext.tellg() == 8)
                {
                    string line;
                    unsigned int padding[64];
                    int padLen;
                    line.clear();
                    //Read the padding line
                    while(line.length()<8)
                    {
                         plaintext.get(c);
                         if(plaintext.eof()) break;
                         line += c;
                    }

                    char2bit(line,padding); //Convert to bit
                    Decription(padding); //decrypt the padding block
                    padLen = bit2int(padding,64); //Get the padding length
                    char2bit(buffer,bits);
                    Decription(bits); //decrypt the message block
                    buffer = bit2char(bits,64); //Convert message from binary to string
                    buffer.resize(8-padLen/8); //Resize the string message, deleting the padding chars
                    ciphertext<<buffer;
                }
                else if(!plaintext.eof()) //Pointer at the end of the file
                {
                     char2bit(buffer,bits);
                     Decription(bits);
                     ciphertext<<bit2char(bits,64);
                }
            }
            plaintext.close();
            ciphertext.close();
        }
        else if(option == 3) return 0;
         cout<<"1 - Encrypt text\n2 - Decrypt text\n3 - Exit\nOption: ";
         cin>>option;
    }

}
