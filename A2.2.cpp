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

void decrypt(string input);

int main()
{
	ifstream myfile;
	myfile.open("input-A22.txt");
	stringstream stream;
	stream << myfile.rdbuf();
	string input = stream.str();
	decrypt(input);
}

//convert character to unicode value
int charToUnicode(char c) {
    return static_cast<int>(c); // Converting char to int
}

void decrypt(string input)
{
	stringstream ss(input);
	vector<int> stringHold;
	int num;
	while (ss >> num) {
		stringHold.push_back(num);
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}

	int length = (stringHold.size()/4)+1;
	vector<vector<double>> matrixB(4, vector<double>(length));
	int current = 0;
	for (int col = 0; col < length; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			if(current <= (length*3)+3)
				matrixB[row][col] = stringHold[current];
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


	//display output matrix text
	cout << "\nOutput Matrix Text:\n";
	for (int x = 0; x < length; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			//had a very weird occurence where every number that was not in the top row was subtracted by one except for the ":"(58)
			int currentChar = matrixB[y][x];
			//if (y != 0 && currentChar != 58)
				//currentChar += 1;
			cout << static_cast<char>(currentChar);
		}
	}
	cout << endl;
}

