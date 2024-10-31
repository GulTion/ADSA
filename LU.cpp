#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iterator>

void luDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; ++k) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        for (int j = i + 1; j < n; ++j) {
            L[j][i] = A[j][i];
            for (int k = 0; k < i; ++k) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
        L[i][i] = 1.0;
    }
}

std::vector<std::vector<double>> readMatrixFromUser() {
    int n;
    std::cout << "Enter the size of the matrix (n x n): ";
    std::cin >> n;

    if (n <= 0) {
        throw std::runtime_error("Matrix size must be positive.");
    }

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::cout << "Enter the elements of the matrix, row by row:\n";
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> A[i][j];
        }
    }

    return A;
}

int main() {
    std::vector<std::vector<double>> A;
    try {
        A = readMatrixFromUser();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    int n = A.size();
    std::vector<std::vector<double>> L, U;
    luDecomposition(A, L, U);

    std::cout << "Lower Triangular Matrix (L):\n";
    for (const auto& row : L) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Upper Triangular Matrix (U):\n";
    for (const auto& row : U) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

