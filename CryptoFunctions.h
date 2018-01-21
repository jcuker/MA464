#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

/*
    LetterToNumber takes a character and will return the integer representation of it.
    LetterToNumber will return an integer from [0-93] accounting for ASCII codes from 32-126
*/
static int LetterToNumber(char a, bool isCaseSensitive = false)
{
    if((int)a < 32 || ((int)a) > 126)
    {
        string msg =  a + ": is not a supported character. Only use ASCII characters from 32 - 126.";
        throw std::invalid_argument(msg);
    }
    return ((int)a) - 32;
}

/*
    NumberToLetter takes a char and optionally a bool denoting whether the result should be taken to lowercase.
    NumberToLetter will return the char representation of the integer.
*/
static char NumberToLetter(int a, bool isLowercase = false)
{
    return (char) (a + 32);
}

/*
    StringToVectorInt takes in a string.
    StringToVectorInt returns an integer vector filled with the integer representations of the provided characters. Any invalid characters, IE not alphabetic, will be omitted.
*/
static vector<int> StringToVectorInt(string str)
{
    vector<int> returnResult;

    for(char c : str)
    {
        returnResult.push_back(LetterToNumber(c));
    }

    return returnResult;
}

/*
    VectorIntToString takes in an integer vector.
    VectorIntToString returns the string of characters that the integers represent.
*/
static string VectorIntToString(vector<int> vInt)
{
    string returnResult;

    for(int i : vInt)
    {
        returnResult += NumberToLetter(i);
    }

    return returnResult;
}

static void RemoveWhitespace(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}
