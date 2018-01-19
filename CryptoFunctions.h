#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class CryptoFunctions
{
    public:
        /*
            LetterToNumber takes a char and optionally a bool denoting whether or not to account for capital and lowercase. If not provided, or false is provided, everything will be taken toupper.
            LetterToNumber will return the integer representation of the char from [0-25]
            If the char provided was not valid input, IE not a-Z, -1 will be returned. 
        */
        static int LetterToNumber(char a, bool isCaseSensitive = false)
        {
            if( ! isalpha(a))
            {
                cout << a << " is not a letter.\n";
                return -1;
            }

            if(isCaseSensitive)
            {
                if(islower(a))
                {
                    return ((int) a) - 97;
                }
                else
                {
                    return ((int) a) - 65;
                }
            }
            else
            {
                if(islower(a))
                {
                    a = toupper(a);
                }
                return ((int) a) - 65;
            }
        }

        /*
            NumberToLetter takes a char and optionally a bool denoting whether the result should be taken to lowercase.
            NumberToLetter will return the char representation of the integer.
        */
        static char NumberToLetter(int a, bool isLowercase = false)
        {
            if(isLowercase)
            {
                return (char) a + 97;
            }
            else
            {
                return (char) a + 65;
            }
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
};