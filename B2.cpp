/*
	Jacob Larsen
	Part B2
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void toREF(vector<vector<int>>& matrix);
void toRREF(vector<vector<int>>& matrix);
void printMatrix(vector<vector<int>>& matrix);


int main()
{
	int flow1, flow2, flow3, flow4;
	cout << "Enter flow1: " << endl;
	cin >> flow1;
	cout << "Enter flow2: " << endl;
	cin >> flow2;
	cout << "Enter flow3: " << endl;
	cin >> flow3;
	cout << "Enter flow4: " << endl;
	cin >> flow4;
	
	vector<vector<int>> traffic = { {0,0,-1,1, flow1},
									{0,1,1,0, flow2},
									{-1,1,0,0, flow3},
									{1,0,0,1, flow4} };
	
	cout << "input matrix\n";
    printMatrix(traffic);

    cout << "REF:\n";
    toREF(traffic);
    printMatrix(traffic);

    cout << "RREF:\n";
    toRREF(traffic);
    printMatrix(traffic);
}

void printMatrix(vector<vector<int>>& matrix)
{
    for (const auto& row : matrix) 
    {
        for (const auto& elem : row)
            cout << elem << " ";
        cout << endl;
    }
    cout << endl;
}

void toREF(vector<vector<int>>& matrix) 
{
    int lead = 0;
    const size_t rowCount = matrix.size();
    const size_t columnCount = matrix[0].size();

    for (size_t r = 0; r < rowCount; r++) 
    {
        if (lead >= columnCount) 
            return;
        int i = r;
        while (matrix[i][lead] == 0) 
        {
            i++;
            if (i == rowCount) 
            {
                i = r;
                lead++;
                if (lead == columnCount) 
                    return;
            }
        }
        swap(matrix[i], matrix[r]);

        if (matrix[r][lead] != 0) 
        {
            int val = matrix[r][lead];
            for (size_t j = 0; j < columnCount; j++) 
                matrix[r][j] /= val;
        }

        for (size_t i = 0; i < rowCount; i++) 
        {
            if (i != r) 
            {
                int val = matrix[i][lead];
                for (size_t j = 0; j < columnCount; j++)
                    matrix[i][j] -= val * matrix[r][j];
            }
        }
        lead++;
    }
}

void toRREF(vector<vector<int>>& matrix) 
{
    toREF(matrix);
    for (size_t i = 0; i < matrix.size(); i++) 
    {
        int lead = 0;
        for (size_t j = 0; j < matrix[0].size(); j++) 
        {
            if (matrix[i][j] != 0) 
            {
                lead = j;
                break;
            }
        }
        if (matrix[i][lead] != 0) 
        {
            int val = matrix[i][lead];
            for (size_t j = 0; j < matrix[0].size(); j++) 
                matrix[i][j] /= val;
        }
    }
}