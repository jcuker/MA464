#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include "CryptoFunctions.h"

using namespace std;

vector<int> ShiftCipher(vector<int> plaintextVector, int key)
{
    vector<int> ciphertextVector;

    for(int i : plaintextVector)
    {
        ciphertextVector.push_back( (i + key) % 26);
    }

    return ciphertextVector;
}

int main()
{
    string plaintext;
    int key;

    cout << "Enter the plaintext.\n";
    cin >> plaintext;

    cout << "Enter the key.\n";
    cin >> key;

    vector<int> plaintextVector = CryptoFunctions::StringToVectorInt(plaintext);
    vector<int> ciphertextVector = ShiftCipher(plaintextVector, key);

    cout << "ciphertext:\n" << CryptoFunctions::VectorIntToString(ciphertextVector);

    return 0;
}