#include "bits/stdc++.h"
using namespace std;
typedef long long int lli;

const int MOD = 1000000007; // Modulo

inline lli prod(lli x, lli y){
    long long res = x * y;
    if(res >= MOD) res %= MOD;
    return res;
}

inline lli add(lli x, lli y){
    int res = x + y;
    if(res >= MOD) res -= MOD;
    return res;
}

struct Matrix{
    int ORD;
    lli mat[20][20];
    Matrix(int ORD) : ORD(ORD) {
        for(int i = 0; i < ORD; i++)
            for(int j = 0; j < ORD; j++)
                mat[i][j] = 0;
    }

    lli get(int i, int k) {
        return mat[i][k];
    }

    void set(int i, int k, int val){
        mat[i][k] = val;
    }

    Matrix unit() {
        for (int i = 0; i < ORD; i++)
            mat[i][i] = 1;
    }

    void mult (Matrix y){
        Matrix res(ORD);
        for(int i = 0; i < ORD; i++)
            for(int j = 0; j < ORD; j++)
                for(int k = 0; k < ORD; k++)
                    res.mat[i][j] = add(res.mat[i][j], prod(mat[i][k], y.mat[k][j]));
        for (int i = 0; i < ORD; i++)
            for (int k = 0; k < ORD; k++)
                mat[i][k] = res.mat[i][k];
    }
};

void exponent_(Matrix& ans, Matrix a, lli x) {
    while (x > 0) {
        if (x % 2 == 1) {
            ans.mult(a);
        }
        x /= 2;
        a.mult(a);
    }
}

lli ways[20];

int main() {

    ways[0] = 1;

    int N; cin >> N;
    lli K; cin >> K;
    for (int i = 0; i < N; i++) {
        lli a, b; cin >> a >> b;
        int c; cin >> c;

        Matrix u(c + 1);
        u.unit();

        Matrix transition(c + 1);
        for (int i = 0; i <= c; i++) {
            if (i != 0) transition.set(i, i - 1, 1);
            transition.set(i, i, 1);
            if (i != c) transition.set(i, i + 1, 1);
        }

        lli amnt = min(K, b) - a;
        exponent_(u, transition, amnt);

        vector<lli> cur_ways(20);
        for (int i = 0; i <= c; i++) {
            for (int k = 0; k <= c; k++) {
                cur_ways[i] = (cur_ways[i] + (u.get(i, k) * ways[k]) % MOD) % MOD;
            }
        }
        for (int i = 0; i <= 19; i++) {
            ways[i] = cur_ways[i];
        }
    }

    cout << (ways[0] + MOD) % MOD << "\n";

    return 0;
}