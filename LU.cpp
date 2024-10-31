#include <iostream>
#include <vector>
#include <stdexcept>

void luDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
        for (int j = i; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < i; ++k) sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }
        for (int j = i + 1; j < n; ++j) {
            if (U[i][i] == 0) throw std::runtime_error("Zero pivot encountered. LU decomposition cannot proceed.");
            double sum = 0;
            for (int k = 0; k < i; ++k) sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

std::vector<std::vector<double>> readMatrixFromUser() {
    int n;
    std::cout << "Enter the size of the matrix (n x n): ";
    std::cin >> n;
    if (n <= 0) throw std::runtime_error("Matrix size must be positive.");

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::cout << "Enter the elements of the matrix, row by row:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> A[i][j];
        }
    }
    return A;
}

void printMatrix(const std::vector<std::vector<double>>& matrix, const std::string& name) {
    std::cout << name << " Matrix:\n";
    for (const auto& row : matrix) {
        for (double val : row) std::cout << val << " ";
        std::cout << "\n";
    }
}

int main() {
  	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    try {
        auto A = readMatrixFromUser();
        std::vector<std::vector<double>> L, U;
        luDecomposition(A, L, U);
        printMatrix(L, "Lower Triangular (L)");
        printMatrix(U, "Upper Triangular (U)");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

/*
README - Input and Output Example
=================================

Input Example:
--------------
Enter the size of the matrix (n x n): 3
Enter the elements of the matrix, row by row:
2 -1 -2
-4 6 3
-4 -2 8

Output Example:
---------------
Lower Triangular (L) Matrix:
1 0 0 
-2 1 0 
-2 -1 1 

Upper Triangular (U) Matrix:
2 -1 -2 
0 4 -1 
0 0 3 
*/

