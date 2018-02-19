#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cmath>

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

static vector<vector<int>> StringToMatrixInt(string str, int dimen, bool limitedChars)
{
    if(str.length() % dimen != 0)
    {
        cerr << "Length of text is not divisible by dimension! (" << dimen << ")\n";
        exit(0);
    }

    int numRows = dimen;
    int numCols = str.length() / dimen;

    vector<vector<int>> returnMatrix(numRows, vector<int>(numCols));
    int currentPositionInString = 0;
    
    for(int currentRow = 0; currentRow < numRows; currentRow++)
    {
        for(int currentCol = 0; currentCol < numCols;  currentCol++)
        {
            char currentChar = str[currentPositionInString];
            int intRepresentationOfChar = LetterToNumber(currentChar, limitedChars);
            returnMatrix[currentRow][currentCol] = (intRepresentationOfChar);
            currentPositionInString++;
        }
    }
    return returnMatrix;
}

static string MatrixIntToString(vector<vector<int>> matrix, bool limitedChars)
{
    string returnString;
    
    for(int currentRow = 0; currentRow < matrix.size(); currentRow++)
    {
        for(int currentCol = 0; currentCol < matrix[currentRow].size();  currentCol++)
        {
            int currentCharAsInt = matrix[currentRow][currentCol];
            char currentChar = NumberToLetter(currentCharAsInt, limitedChars);
            returnString += currentChar;
        }
    }

    return returnString;
}

static int xGCD(int leftNum, int rightNum, int &x, int &y)
{
    if(rightNum == 0) {
       x = 1;
       y = 0;
       return leftNum;
    }

    int x1, y1, gcd = xGCD(rightNum, leftNum % rightNum, x1, y1);
    x = y1;
    y = x1 - (leftNum / rightNum) * y1;
    return gcd;
}

static int MultiplicativeInverseModulo(int num, int modNum)
{
    int x = 0, y = 0;
    int gcd = xGCD(num, modNum, x, y);
    if(gcd != 1)
    {
        return -1;
    }
    else
    {
        return x;
    }
}

static vector<vector<int>> MultiplyMatricesModulo(vector<vector<int>> leftMatrix, vector<vector<int>> rightMatrix, int modNum)
{
    vector<vector<int> > answerM = leftMatrix;
	for (int i = 0; i < rightMatrix.size(); i++)
	{
		for (int j = 0; j < leftMatrix[0].size(); j++)
		{
			int tempI = 0;

			for (int x = 0; x < rightMatrix[i].size(); x++)
			{
				tempI = tempI + (rightMatrix[i][x] * leftMatrix[x][j]);
			}

			answerM[i][j] = (tempI % modNum);
		}
	}
    return answerM;
}

static int DeterminantModulo (vector<vector<int>> matrix, int modNum)
{
    int add = 0, mulP = 1, sub = 0, mulN = 1, det;

	if (matrix.size() > 2)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0, n = i; j < matrix.size(); j++, n++)
			{
				mulP *= matrix[j][n % matrix[j].size()];
			}
			add += mulP;
			mulP = 1;
		}

		for (int i = (matrix.size() - 1); i >= 0; i--)
		{
			for (int j = (matrix.size() - 1), n = (matrix.size() - (i + 1)); j >= 0; j--, n++)
			{
				mulN *= matrix[j][n % matrix[j].size()];
			}
			sub += mulN;
			mulN = 1;
		}
	}
	else if (matrix.size() == 2) // if 2 by 2
	{
		add = matrix[0][0] * matrix[1][1];
		sub = matrix[0][1] * matrix[1][0];
	}
	else // if only 1 value. 
	{
		add = matrix[0][0];
		sub = 0;
	}

	det = add - sub;

	while (det < 0)
	{
		det += modNum; // to account for negative values. 
	}
    return (det % modNum);
}

static vector<vector<int>> InvertMatrixModulo(vector<vector<int>> matrix, int detInverse, int modNum)
{
	int temp;
	bool added = false;
	vector<vector<int>> returnMatrix;

	for (int i = 0; i < matrix.size(); i++)
	{
		vector<int> answerList;

		for (int j = 0; j < matrix[i].size(); j++)
		{
			vector<vector<int>> subMatrix;
			for (int x = 0; x < matrix.size(); x++)
			{
				vector<int> subList;
				for (int y = 0; y < matrix[x].size(); y++)
				{
					temp = matrix[x][y];
					if ((x != j) && (y != i)) // ignores subsequent columns and rows. 
					{
						subList.push_back(temp);
						added = true;
					}
				}
				if (added) // ignores subsequent columns and rows. 
				{
					subMatrix.push_back(subList);
					added = false;
				}
			}
			temp = pow(-1, (i + j)) * detInverse * DeterminantModulo(subMatrix, modNum);
			while (temp < 0)
			{
				temp += modNum; // to account for negative values. 
			}
			answerList.push_back(temp % modNum);
		}
		returnMatrix.push_back(answerList);
	}

	return returnMatrix;
}

static vector<vector<int>> TransposeMatrix(vector<vector<int>> matrix)
{
    vector<vector<int> > returnMatrix;
	for (int i = 0; i < matrix[0].size(); i++)
	{
		vector<int> temp;
		for (int j = 0; j < matrix.size(); j++)
		{
			temp.push_back(matrix[j][i]);
		}
		returnMatrix.push_back(temp);
	}
    return returnMatrix;
}