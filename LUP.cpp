#include <bits/stdc++.h>
using namespace std;

void LUPDecomposition(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U, vector<int> &P, int n) {
    for (int i = 0; i < n; i++) {
        P[i] = i; 
    }

    for (int i = 0; i < n; i++) {
        double pivot = 0.0;
        int pivotIndex = i;

        for (int j = i; j < n; j++) {
            if (abs(A[j][i]) > abs(pivot)) {
                pivot = A[j][i];
                pivotIndex = j;
            }
        }

        if (pivot == 0) {
            throw runtime_error("Matrix is singular.");
        }

        if (pivotIndex != i) {
            swap(A[i], A[pivotIndex]);
            swap(P[i], P[pivotIndex]);
        }

        for (int j = i + 1; j < n; j++) {
            A[j][i] /= A[i][i];
            for (int k = i + 1; k < n; k++) {
                A[j][k] -= A[j][i] * A[i][k];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                L[i][j] = A[i][j];
                U[i][j] = 0;
            } else if (i == j) {
                L[i][j] = 1;
                U[i][j] = A[i][j]; 
            } else {
                L[i][j] = 0;
                U[i][j] = A[i][j]; 
            }
        }
    }
}

void forwardSubstitution(const vector<vector<double>> &L, const vector<int> &P, const vector<double> &B, vector<double> &Y, int n) {
    for (int i = 0; i < n; i++) {
        Y[i] = B[P[i]];
        for (int j = 0; j < i; j++) {
            Y[i] -= L[i][j] * Y[j];
        }
    }
}

void backwardSubstitution(const vector<vector<double>> &U, const vector<double> &Y, vector<double> &X, int n) {
    for (int i = n - 1; i >= 0; i--) {
        X[i] = Y[i];
        for (int j = i + 1; j < n; j++) {
            X[i] -= U[i][j] * X[j];
        }
        X[i] /= U[i][i];
    }
}

void readMatrixFromUser(vector<vector<double>> &A, vector<double> &B) {
    int n;
    cout << "Enter the size of the matrix (n x n): ";
    cin >> n;

    if (n <= 0) {
        throw runtime_error("Matrix size must be positive.");
    }

    A.resize(n, vector<double>(n));
    B.resize(n);

    cout << "Enter the elements of the matrix (row by row), and for each row, enter the last element as the corresponding entry of B:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
        cin >> B[i]; // Read the last element for vector B
    }
}

void printMatrix(const vector<vector<double>> &matrix, const string &name) {
    cout << name << " Matrix:\n";
    for (const auto &row : matrix) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<double>> A;
    vector<double> B;

    try {
        readMatrixFromUser(A, B);
    } catch (const runtime_error &e) {
        cout << e.what() << "\n";
        return 1;
    }

    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    vector<int> P(n);
    vector<double> Y(n);
    vector<double> X(n);

    try {
        LUPDecomposition(A, L, U, P, n);
        forwardSubstitution(L, P, B, Y, n);
        backwardSubstitution(U, Y, X, n);

        printMatrix(L, "Lower");
        printMatrix(U, "Upper");

        cout << "\nPermutation Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << (P[i] == j ? 1 : 0) << " ";
            }
            cout << "\n";
        }

        cout << "\nSolution:\n";
        for (const auto &val : X) {
            cout << val << " ";
        }
        cout << endl;

    } catch (const runtime_error &e) {
        cout << e.what() << endl;
        return 0;
    }

    return 0;
}

