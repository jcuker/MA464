#include <cctype>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class CryptoFunctions
{
    public:
        static int LetterToNumber(char a, bool isCaseSensitive = false)
        {
            if( ! isalpha(a))
            {
                cout << a << " is not a letter.\n";
                return -1;
            }

            if(isCaseSensitive && islower(a))
            {
                return ((int) a) - 97;
            }
            else
            {
                return ((int) a) - 65;
            }
        }

        static char NumberToLetter(int a, bool lowercase = false)
        {
            if(lowercase)
            {
                return (char) a + 97;
            }
            else
            {
                return (char) a + 65;
            }
        }

        static vector<int> StringToVectorInt(string str)
        {
            vector<int> returnResult;

            for(char c : str)
            {
                returnResult.push_back(LetterToNumber(c));
            }

            return returnResult;
        }

        static string VectorIntToString(vector<int> vInt)
        {
            string returnResult;

            for(int i : vInt)
            {
                returnResult += NumberToLetter(i);
            }

            return returnResult;
        }
};