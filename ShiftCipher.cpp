#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "CryptoFunctions.h"

using namespace std;

void PrintUsage();

void ParseArguments(int argc, char** argv);

void Encrypt();

void Decrypt();

vector<int> ShiftCipherEncrypt(vector<int> plaintextVector, int key);

vector<int> ShiftCipherDecrypt(vector<int> plaintextVector, int key);

// Global vars (bad practice but oh well)
bool isEncrypt = false;
bool limitedChars = false;
int modulusNum = 0;

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        PrintUsage();
    }

    ParseArguments(argc, argv);

    if(isEncrypt)
    {
        Encrypt();
    }
    else
    {
        Decrypt();
    }

    return 0;
}

void PrintUsage()
{
    cout << "Usage:\n";
    cout << "-E for encrypt\n-D for decrypt\n";
    cout << "-F for full ASCII support (default)\n-C for characters only\n";
    exit(0);
}

void ParseArguments(int argc, char** argv)
{
    for(int currentIndex = 1; currentIndex < argc; currentIndex++)
    {
        string mode = argv[currentIndex];
        RemoveWhitespace(mode);
        if( (mode.length() != 2) || (mode[1] != 'D' && mode[1] != 'E' && mode[1] != 'F' && mode[1] != 'C'))
        {
            PrintUsage();       
        }

        if(mode[1] == 'E')
        {
            isEncrypt = true;   
        }
        else if(mode[1] == 'D')
        {
            isEncrypt = false;
        }
        else if(mode[1] == 'F')
        {
            limitedChars = false;
            modulusNum = 94;
        }
        else if(mode[1] == 'C')
        {
            limitedChars = true;
            modulusNum = 26;
        }
        else
        {
            cerr << "Error in parsing input.\n";
        }
    }
    
}

void Encrypt()
{
    string plaintext;
    int key;

    cout << "Enter the plaintext.\n";
    getline(cin, plaintext);

    if(limitedChars)
    {
        RemoveWhitespace(plaintext);
        RemoveNonAlphaChars(plaintext);
    }

    cout << "Enter the key.\n";
    cin >> key;
    key %= modulusNum;

    vector<int> plaintextVector = StringToVectorInt(plaintext, limitedChars);
    
    vector<int> ciphertextVector = ShiftCipherEncrypt(plaintextVector, key);

    cout << "ciphertext:\n";
    PrintBlock(VectorIntToString(ciphertextVector, limitedChars));
}

vector<int> ShiftCipherEncrypt(vector<int> plaintextVector, int key)
{
    vector<int> ciphertextVector;

    for(int i : plaintextVector)
    {
        ciphertextVector.push_back( (i + key) % modulusNum);
    }

    return ciphertextVector;
}

void Decrypt()
{
    string ciphertext;
    int key;

    cout << "Enter the ciphertext.\n";
    getline(cin, ciphertext);
    RemoveWhitespace(ciphertext);
    cout << "Enter the key.\n";
    cin >> key;
    key %= modulusNum;

    vector<int> ciphertextVector = StringToVectorInt(ciphertext, limitedChars);
    
    vector<int> plaintextVector = ShiftCipherDecrypt(ciphertextVector, key);

    cout << "plaintext:\n" << VectorIntToString(plaintextVector, limitedChars);
}

vector<int> ShiftCipherDecrypt(vector<int> ciphertextVector, int key)
{
    vector<int> plaintextVector;
    for(int i : ciphertextVector)
    {
        plaintextVector.push_back( ( (i + modulusNum) - key) % modulusNum);
    }

    return plaintextVector;
}