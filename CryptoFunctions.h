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
static int LetterToNumber(char a, bool limitToCharsOnly =  false)
{
    if(limitToCharsOnly)
    {
        if( ! isalpha(a))
        {
            cerr << a << ": is not a character." << endl;
            exit(0);
        }
        a = toupper(a);
        return ( (int) a) - 65;
    }
    if((int)a < 32 || ((int)a) > 126)
    {
        cerr << a << ": is not a supported character. Only use ASCII characters from 32 - 126." << endl;
        exit(0);
    }
    return ((int)a) - 32;
}

/*
    NumberToLetter takes a char and optionally a bool denoting whether the result should be taken to lowercase.
    NumberToLetter will return the char representation of the integer.
*/
static char NumberToLetter(int a, bool limitToCharsOnly = false)
{
    if(limitToCharsOnly)
    {
        return (char) (a + 65);
    }

    return (char) (a + 32);
}

/*
    StringToVectorInt takes in a string.
    StringToVectorInt returns an integer vector filled with the integer representations of the provided characters. Any invalid characters, IE not alphabetic, will be omitted.
*/
static vector<int> StringToVectorInt(string str, bool limitToCharsOnly = false)
{
    vector<int> returnResult;

    for(char c : str)
    {
        returnResult.push_back(LetterToNumber(c, limitToCharsOnly));
    }

    return returnResult;
}

/*
    VectorIntToString takes in an integer vector.
    VectorIntToString returns the string of characters that the integers represent.
*/
static string VectorIntToString(vector<int> vInt, bool limitToCharsOnly)
{
    string returnResult;

    for(int i : vInt)
    {
        returnResult += NumberToLetter(i, limitToCharsOnly);
    }

    return returnResult;
}

static void RemoveWhitespace(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

static void RemoveNonAlphaChars(string& str)
{
    for(char c : str)
    {
        if (! isalpha(c))
        {
            str.erase(std::remove(str.begin(), str.end(), c), str.end());
        }
    }
}

static void PrintBlock(string str, int blockLength = 5)
{
    int tempBlockLength = blockLength;
    for(char c : str)
    {
        cout << c;
        tempBlockLength--;
        if(tempBlockLength == 0)
        {
            cout << " ";
            tempBlockLength = blockLength;
        }
    }
}
