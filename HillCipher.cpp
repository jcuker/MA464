#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "CryptoFunctions.h"

using namespace std;

void PrintUsage();

void ParseArguments(int argc, char** argv);

vector<vector<int>> ParseMatrixInput(string input);

void Encrypt();

void Decrypt();

vector<vector<int>> HillCipherEncrypt(vector<vector<int>> plaintextMatrix, vector<vector<int>> keyMatrix);

vector<vector<int>> HillCipherDecrypt(vector<vector<int>> ciphertextMatrix, vector<vector<int>> keyMatrix);

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

    cout << "Enter the plaintext.\n";
    getline(cin, plaintext);

    if(limitedChars)
    {
        RemoveWhitespace(plaintext);
        RemoveNonAlphaChars(plaintext);
    }

    cout << "What is the dimension of the key matrix? (EX. 2, 3, 4, ...)\n";
    int dimen;
    cin >> dimen;

    cout << "Enter the key.\n";
    string key;
    cin >> key;

    vector<vector<int>> plaintextMatrix = StringToMatrixInt(plaintext, dimen, limitedChars);
    vector<vector<int>> keyMatrix = StringToMatrixInt(key, dimen, limitedChars);
    vector<vector<int>> ciphertextMatrix = HillCipherEncrypt(plaintextMatrix, keyMatrix);

    cout << "ciphertext:\n";
    PrintBlock(MatrixIntToString(ciphertextMatrix, limitedChars));
}

void Decrypt()
{
    string ciphertext;
    int key;

    cout << "Enter the ciphertext.\n";
    getline(cin, ciphertext);
    RemoveWhitespace(ciphertext);

}

vector<vector<int>> HillCipherEncrypt(vector<vector<int>> plaintextMatrix, vector<vector<int>> keyMatrix)
{
    vector<vector<int>> ciphertextMatrix = MultiplyMatricesModulo(plaintextMatrix, keyMatrix, modulusNum);
    return ciphertextMatrix;
}

vector<vector<int>> HillCipherDecrypt(vector<vector<int>> ciphertextMatrix, vector<vector<int>> keyMatrix)
{
    vector<vector<int>> inverseKeyMatrix = InvertMatrixModulo(keyMatrix, modulusNum);
    vector<vector<int>> plaintextMatrix = MultiplyMatrices(ciphertextMatrix, inverseKeyMatrix);
    return ciphertextMatrix;
}