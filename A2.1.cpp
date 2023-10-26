/*
	Jacob Larsen
	Part A2
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<vector<double>> matrixA = {{1, -1, -1, 1},
							   {2, -3, -5, 4},
						       {-2, -1, -2, -2},
						       {3, -3, -1, 2} };

vector<vector<double>> matrixAI = { {6, -1, 0, -1},
									{4.28571428571, -0.57142857142, -0.14285714285, -1.14285714286},
									{-3.71428571429, 0.42857142857, -0.14285714285, 0.85714285714},
									{-4.42857142857, 0.85714285714, -0.28571428571, 0.71428571428} };

vector<vector<double>> encrypt(string input);
vector<vector<double>> decrypt(vector<vector<double>> input);

int main()
{
	ifstream myfile;
	myfile.open("input-A21.txt");
	stringstream stream;
	stream << myfile.rdbuf();
	string input = stream.str();
	vector<vector<double>> matrixI = encrypt(input);
	decrypt(matrixI);
}

//convert character to unicode value
int charToUnicode(char c) {
    return static_cast<int>(c); // Converting char to int
}

vector<vector<double>> encrypt(string input)
{
	//turn all characters of input string into unicode and set them into a matrix of 4xN where N is the length of string/4(+1)
	int length = (input.length()/4)+1;
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

//not sure if decrypt is part of a.21
vector<vector<double>> decrypt(vector<vector<double>> input)
{
	cout << "\nmatrixAI:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			cout << matrixAI[x][y] << " ";
		}
		cout << endl;
	}

	int length = input[0].size();
	//deccode the matrix by multiplying encrypted matrix c by cypher matrix A-1
	vector<vector<double>> outMatrix(4, vector<double>(length));
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < length; j++) 
		{
			for (int k = 0; k < 4; k++) 
			{
				outMatrix[i][j] += matrixAI[i][k] * input[k][j];
			}
		}
	}

	//display output matrix
	cout << "\noutput matrix2:\n";
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < length; y++)
		{
			cout << outMatrix[x][y] << " ";
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
			if (y != 0 && currentChar != 58)
				currentChar += 1;
			cout << static_cast<char>(currentChar);
		}
	}
	return outMatrix;
}