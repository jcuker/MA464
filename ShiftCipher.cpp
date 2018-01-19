#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "CryptoFunctions.h"

using namespace std;

void Encrypt();

void Decrypt();

vector<int> ShiftCipherEncrypt(vector<int> plaintextVector, int key);

vector<int> ShiftCipherDecrypt(vector<int> plaintextVector, int key);


int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        cerr << "Must enter -E for encrypt or -D for decrypt.\n";
        return 0;
    }

    string mode = argv[1];
    CryptoFunctions::RemoveWhitespace(mode);

    if( (mode.length() != 2) || (mode[1] != 'D' && mode[1] != 'E'))
    {
        cerr << "Must enter -E for encrypt or -D for decrypt.\n";
        return 0;
    }

    if(mode[1] == 'E')
    {
        Encrypt();
    }
    else if(mode[1] == 'D')
    {
        Decrypt();
    }
    else
    {
        cerr << "Error in parsing input.\n";
    }

    return 0;
}


void Encrypt()
{
    string plaintext;
    int key;

    cout << "Enter the plaintext.\n";
    getline(cin, plaintext);
    CryptoFunctions::RemoveWhitespace(plaintext);

    cout << "Enter the key.\n";
    cin >> key;

    vector<int> plaintextVector = CryptoFunctions::StringToVectorInt(plaintext);
    
    vector<int> ciphertextVector = ShiftCipherEncrypt(plaintextVector, key);

    cout << "ciphertext:\n" << CryptoFunctions::VectorIntToString(ciphertextVector);
}

vector<int> ShiftCipherEncrypt(vector<int> plaintextVector, int key)
{
    vector<int> ciphertextVector;

    for(int i : plaintextVector)
    {
        ciphertextVector.push_back( (i + key) % 26);
    }

    return ciphertextVector;
}

void Decrypt()
{
    string ciphertext;
    int key;

    cout << "Enter the ciphertext.\n";
    getline(cin, ciphertext);
    CryptoFunctions::RemoveWhitespace(ciphertext);

    cout << "Enter the key.\n";
    cin >> key;

    vector<int> ciphertextVector = CryptoFunctions::StringToVectorInt(ciphertext);
    
    vector<int> plaintextVector = ShiftCipherDecrypt(ciphertextVector, key);

    cout << "plaintext:\n" << CryptoFunctions::VectorIntToString(plaintextVector);
}

vector<int> ShiftCipherDecrypt(vector<int> ciphertextVector, int key)
{
    vector<int> plaintextVector;

    for(int i : ciphertextVector)
    {
        plaintextVector.push_back( ( (i + 26) - key) % 26);
    }

    return plaintextVector;
}