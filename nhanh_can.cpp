#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

// read the matrix from file
tuple<vector<vector<int>>, int, int, int> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    int n, m, b;

    if (file.is_open()) {
        string line;
        getline(file, line);
        istringstream iss(line);
        iss >> n >> m >> b;
        while (getline(file, line)) {
            vector<int> row;
            istringstream iss(line);
            int num;
            iss >> num;
            while (iss >> num) {
                row.push_back(num);
            }
            matrix.push_back(row);
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << endl;
    }

    return make_tuple(matrix, n, m, b);
}

// create matrix c 
vector<vector<int>> createMatrixC(const vector<vector<int>>& matrix, int maxNum) {
    vector<vector<int>> c(matrix.size(), vector<int>(maxNum, 0));

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            c[i][matrix[i][j] - 1] = 1;
        }
    }

    return c;
}

void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

bool checkRowsSum(const vector<vector<int>>& matrix, int b) {
    for (const auto& row : matrix) {
        int rowSum = 0;
        for (int element : row) {
            rowSum += element;
        }
        if (rowSum != b) {
            return false;
        }
    }
    return true;
}

int maxColumnSum(const vector<vector<int>>& matrix) {
    if(matrix.empty() || matrix[0].empty())
        return 0;
    
    int maxSum = 0;
    int numColumns = matrix[0].size();
    
    for (int j = 0; j < numColumns; ++j) {
        int columnSum = 0;
        for (const auto& row : matrix) {
            columnSum += row[j];
        }
        if (columnSum > maxSum) {
            maxSum = columnSum;
        }
    }
    return maxSum;
}

vector<vector<int>> elementWiseMatrixMultiplication(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows = matrix1.size();
    int columns = matrix1[0].size();
    
    vector<vector<int>> result(rows, vector<int>(columns));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }
    
    return result;
}

tuple<vector<vector<int>>, int> getSolutionMatrix(int n, int m, int b, const vector<vector<int>> c) {
    vector<vector<int>> bestMatrix;
    int minMaxColumnSum = INT_MAX; 

    function<void(int, int)> generate = [&](int row, int col) {
        vector<vector<int>> matrix(n, vector<int>(m, 0)); 
        if (row == n) { // All rows are filled
            if (checkRowsSum(matrix, b)) { 
                if (checkRowsSum(elementWiseMatrixMultiplication(matrix, c), b)) {
                    int currentMaxColumnSum = maxColumnSum(matrix);
                    if (currentMaxColumnSum < minMaxColumnSum) {
                        minMaxColumnSum = currentMaxColumnSum;
                        bestMatrix = matrix;
                    }
                }
            }
            return;
        }

        for (int val = 0; val <= 1; ++val) {
            matrix[row][col] = val;
            if (col + 1 < m)
                generate(row, col + 1);
            else
                generate(row + 1, 0);
        }
    };

    generate(0, 0);

    return make_tuple(bestMatrix, minMaxColumnSum);
}

int main() {

    string filename = "input.txt";
    tuple<vector<vector<int>>, int, int, int> readFile = readMatrixFromFile(filename);
    vector<vector<int>> matrix = get<0>(readFile);
    int n = get<1>(readFile);
    int m = get<2>(readFile);
    int b = get<3>(readFile);
    
    vector<vector<int>> c = createMatrixC(matrix, m);
    
    tuple<vector<vector<int>>, int> result = getSolutionMatrix(n, m, b, c);
    vector<vector<int>> resultMatrix = get<0>(result);
    displayMatrix(resultMatrix);
}
