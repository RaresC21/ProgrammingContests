#include "bits/stdc++.h"
using namespace std;

const int MOD = 1000000007; // Modulo

int N; 

vector<int> mult(vector<int> P, vector<vector<int> > m) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            v[i] = (v[i] + (1LL * P[k] * m[i][k]) % MOD) % MOD;
        }
    }
    return v;
}

int main() {


    ios::sync_with_stdio(false);
    cin >> N;
    
    vector<vector<int> > A(N, vector<int>(N, 0));
    vector<vector<int> > B(N, vector<int>(N, 0));
    vector<vector<int> > C(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            cin >> A[i][k];

    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            cin >> B[i][k];

    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++) {
            cin >> C[i][k];
        }


    vector<int> P(N);
    for (int i = 0; i < N; i++)
        P[i] = rand();


    vector<int> temp = mult(P, B);
    vector<int> L = mult(temp, A);
    vector<int> R = mult(P, C);

    for (int i = 0; i < N; i++) {
        if (L[i] != R[i]) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
} 