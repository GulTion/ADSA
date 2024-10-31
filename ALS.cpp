#include <bits/stdc++.h>
using namespace std;

int calcAssemblyTime(int n, const vector<vector<int>>& p, const vector<vector<int>>& t, vector<int> e, vector<int> x) {
    if (n <= 0) {
        cout << "Number of stations must be positive." << endl;
        return -1;
    }
    if (p.size() != 2 || t.size() != 2 || p[0].size() != n || p[1].size() != n || t[0].size() != n - 1 || t[1].size() != n - 1) {
        cout << "Invalid input dimensions." << endl;
        return -1;
    }
    
    vector<int> dp1(n), dp2(n), path1(n), path2(n);
    dp1[0] = e[0] + p[0][0];
    dp2[0] = e[1] + p[1][0];
    path1[0] = 1;
    path2[0] = 2;

    for (int i = 1; i < n; i++) {
        dp1[i] = min(dp1[i - 1] + p[0][i], dp2[i - 1] + t[1][i - 1] + p[0][i]);
        path1[i] = (dp1[i - 1] + p[0][i] <= dp2[i - 1] + t[1][i - 1] + p[0][i]) ? 1 : 2;

        dp2[i] = min(dp2[i - 1] + p[1][i], dp1[i - 1] + t[0][i - 1] + p[1][i]);
        path2[i] = (dp2[i - 1] + p[1][i] <= dp1[i - 1] + t[0][i - 1] + p[1][i]) ? 2 : 1;
    }

    int minTime = min(dp1[n - 1] + x[0], dp2[n - 1] + x[1]);
    int lastLine = (dp1[n - 1] + x[0] <= dp2[n - 1] + x[1]) ? 1 : 2;

    cout << "Optimal path:\nLine " << lastLine << ", Station " << n << endl;
    for (int j = n - 1; j >= 1; j--) {
        lastLine = (lastLine == 1) ? path1[j] : path2[j];
        cout << "Line " << lastLine << ", Station " << j << endl;
    }

    return minTime;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n;
    cout << "Enter number of stations: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of stations must be positive." << endl;
        return 0;
    }

    vector<vector<int>> p(2, vector<int>(n)), t(2, vector<int>(n - 1));
    cout << "Enter processing times for each line:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
            if (p[i][j] < 0) {
                cout << "Processing times must be non-negative." << endl;
                return 0;
            }
        }
    }

    cout << "Enter transfer times between lines:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n - 1; j++) {
            cin >> t[i][j];
            if (t[i][j] < 0) {
                cout << "Transfer times must be non-negative." << endl;
                return 0;
            }
        }
    }

    vector<int> e(2), x(2);
    cout << "Enter entry times: ";
    for (int &v : e) {
        cin >> v;
        if (v < 0) {
            cout << "Entry times must be non-negative." << endl;
            return 0;
        }
    }
    cout << "Enter exit times: ";
    for (int &v : x) {
        cin >> v;
        if (v < 0) {
            cout << "Exit times must be non-negative." << endl;
            return 0;
        }
    }

    cout << "Minimum time required: " << calcAssemblyTime(n, p, t, e, x) << endl;
    return 0;
}

//4
//4 5 3 2
//2 10 1 4
//7 4 5
//9 2 8
//10 12
//18 7

//35
