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

vector<int> VigenereCipherEncrypt(vector<int> plaintextVector, vector<int> key);

vector<int> VigenereCipherDecrypt(vector<int> plaintextVector, vector<int> key);

// Global vars (bad practice but oh well)
bool isEncrypt = false;
bool limitedChars = false; // default mode is accept all ASCII
int modulusNum = 94;

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
    string key;

    cout << "Enter the plaintext.\n";
    getline(cin, plaintext);

    if(limitedChars)
    {
        RemoveWhitespace(plaintext);
        RemoveNonAlphaChars(plaintext);
    }

    cout << "Enter the key.\n";
    cin >> key;

    vector<int> plaintextVector = StringToVectorInt(plaintext, limitedChars);
    vector<int> keyVector = StringToVectorInt(key, limitedChars);

    vector<int> ciphertextVector = VigenereCipherEncrypt(plaintextVector, keyVector);

    cout << "ciphertext:\n";
    PrintBlock(VectorIntToString(ciphertextVector, limitedChars));
}

vector<int> VigenereCipherEncrypt(vector<int> plaintextVector, vector<int> key)
{
    vector<int> ciphertextVector;
    int keyLength = key.size();
    int currentIndex = 0;

    for(int i : plaintextVector)
    {
        ciphertextVector.push_back( (i + key[currentIndex]) % modulusNum);
        currentIndex++;
        currentIndex %= keyLength;
    }

    return ciphertextVector;
}

void Decrypt()
{
    string ciphertext;
    string key;

    cout << "Enter the ciphertext.\n";
    getline(cin, ciphertext);
    RemoveWhitespace(ciphertext);
    cout << "Enter the key.\n";
    cin >> key;

    vector<int> ciphertextVector = StringToVectorInt(ciphertext, limitedChars);
    vector<int> keyVector = StringToVectorInt(key, limitedChars);

    vector<int> plaintextVector = VigenereCipherDecrypt(ciphertextVector, keyVector);

    cout << "plaintext:\n" << VectorIntToString(plaintextVector, limitedChars);
}

vector<int> VigenereCipherDecrypt(vector<int> ciphertextVector, vector<int> keyVector)
{
    vector<int> plaintextVector;
    int keyLength  = keyVector.size();
    int currentIndex = 0;

    for(int i : ciphertextVector)
    {
        plaintextVector.push_back( ( (i + modulusNum) - keyVector[currentIndex]) % modulusNum);
        currentIndex++;
        currentIndex %= keyLength;
    }

    return plaintextVector;
}