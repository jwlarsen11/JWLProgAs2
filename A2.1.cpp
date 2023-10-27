/*
	Jacob Larsen
	Part A2
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<vector<double>> matrixA = { {1, -1, -1, 1},
							   {2, -3, -5, 4},
							   {-2, -1, -2, -2},
							   {3, -3, -1, 2} };

vector<vector<double>> matrixAI = { {6, -1, 0, -1},
									{22, -4, 1, -4},
									{14, -3, 1, -2},
									{31, -6, 2, -5} };

vector<vector<double>> encrypt(string input);
vector<vector<double>> decrypt(string input);

int main()
{
	//for encryption
	ifstream myfile;
	myfile.open("input-A21.txt");
	stringstream stream;
	stream << myfile.rdbuf();
	string input = stream.str();
	vector<vector<double>> matrixI = encrypt(input);

	//for decryption
	ifstream myfile2;
	myfile2.open("input-A22.txt");
	stringstream stream2;
	stream2 << myfile2.rdbuf();
	string input2 = stream2.str();
	decrypt(input2);
}

//convert character to unicode value
int charToUnicode(char c) {
	return static_cast<int>(c); // Converting char to int
}

vector<vector<double>> encrypt(string input)
{
	cout << "ENCRYPTING.....\n";
	//turn all characters of input string into unicode and set them into a matrix of 4xN where N is the length of string/4(+1)
	int length = (input.length() / 4) + 1;
	vector<vector<double>> matrixB(4, vector<double>(length));
	int current = 0;
	for (int col = 0; col < length; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			if (current <= input.length())
				matrixB[row][col] = charToUnicode(input[current]);
			else
				matrixB[row][col] = 0;
			current += 1;
		}
	}

	//display matrixB
	cout << "matrixB:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < length; y++)
		{
			cout << matrixB[x][y] << " ";
		}
		cout << endl;
	}

	//encode the matrix by multiplying encrypted matrix B by cypher matrix A
	vector<vector<double>> outMatrix(4, vector<double>(length));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < length; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				outMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	//display output matrix
	cout << "\noutput matrix:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < length; y++)
		{
			cout << outMatrix[x][y] << " ";
		}
		cout << endl;
	}
	return outMatrix;
}


//decrypting----------------------------------------------------------------------------------------------------
vector<vector<double>> decrypt(string input)
{
	cout << "\nDECRYPTING...\n";
	stringstream ss(input);
	vector<int> stringHold;
	int num;
	while (ss >> num) {
		stringHold.push_back(num);
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}

	int length = (stringHold.size() / 4) + 1;
	vector<vector<double>> matrixB(4, vector<double>(length));
	int current = 0;
	for (int col = 0; col < length; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			if (current <= (length * 3) + 3)
				matrixB[row][col] = stringHold[current];
			current += 1;
		}
	}

	cout << "\nmatrixB2:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < length; y++)
		{
			cout << matrixB[x][y] << " ";
		}
		cout << endl;
	}


	cout << "\nmatrixAI:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			cout << matrixAI[x][y] << " ";
		}
		cout << endl;
	}

	//deccode the matrix by multiplying encrypted matrix c by cypher matrix A-1
	vector<vector<double>> outMatrix(4, vector<double>(length));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < length; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				outMatrix[i][j] += matrixAI[i][k] * matrixB[k][j];
			}
		}
	}

	//display output matrix
	cout << "\noutput matrix2:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < length; y++)
		{
			cout << (int)outMatrix[x][y] << " ";
		}
		cout << endl;
	}

	//display output matrix text
	cout << "\nOutput Matrix Text:\n";
	for (int x = 0; x < length; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			//had a very weird occurence where every number that was not in the top row was subtracted by one except for the ":"(58)
			int currentChar = outMatrix[y][x];
			cout << static_cast<char>(currentChar);
		}
	}
	cout << endl;
	return outMatrix;
}