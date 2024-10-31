#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1);

void fft(vector<Complex>& x) {
    int N = x.size();
    if (N <= 1) return;

    vector<Complex> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    fft(even);
    fft(odd);

    for (int k = 0; k < N / 2; k++) {
        Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

vector<Complex> multiplyPolynomials(const vector<double>& a, const vector<double>& b) {
    int n = a.size() + b.size() - 1;
    int m = 1;
    while (m < n) m *= 2; 

    vector<Complex> fa(m), fb(m);
    for (size_t i = 0; i < a.size(); i++) fa[i] = a[i];
    for (size_t i = 0; i < b.size(); i++) fb[i] = b[i];

    fft(fa);
    fft(fb);

    vector<Complex> result(m);
    for (int i = 0; i < m; i++) {
        result[i] = fa[i] * fb[i];
        result[i] = round(result[i].real());
    }

    return result;
}

int main() {
    int degree1, degree2;

    // Input for the first polynomial
    cout << "Enter the degree of the first polynomial: ";
    cin >> degree1;

    vector<double> poly1(degree1 + 1);
    cout << "Enter the coefficients of the first polynomial (from constant term to highest degree): ";
    for (int i = 0; i <= degree1; i++) {
        cin >> poly1[i]; // Read coefficients of the first polynomial
    }

    // Input for the second polynomial
    cout << "Enter the degree of the second polynomial: ";
    cin >> degree2;

    vector<double> poly2(degree2 + 1);
    cout << "Enter the coefficients of the second polynomial (from constant term to highest degree): ";
    for (int i = 0; i <= degree2; i++) {
        cin >> poly2[i]; // Read coefficients of the second polynomial
    }

    // Perform polynomial multiplication
    vector<Complex> result = multiplyPolynomials(poly1, poly2);

    // Output the resultant polynomial
    cout << "Resultant polynomial coefficients: " << endl;
    for (const auto& coeff : result) {
        cout << coeff << " ";
    }
    cout << endl;

    return 0;
}

