#include <bits/stdc++.h>
using namespace std;

int MOD;
int inv[100];

vector<int> gauss(vector< vector<int> >& A) {
    int n = A.size();
    int m = A[0].size();

    for (int i=0; i<min(n,m); i++) {
        int maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }
        for (int k=i; k<m;k++) {
            int tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        for (int k=i+1; k<n; k++) {
            int c = (A[k][i] * inv[A[i][i]]) % MOD;
            for (int j=i; j<m; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] -= c * A[i][j];
                    if (A[k][j] < 0) A[k][j] %= MOD;
                    if (A[k][j] < 0) A[k][j] += MOD;
                }
            }
        }
    }
    vector<int> x(n);
    for (int i=n-1; i>=0; i--) {
        if (i >= m) continue;
        x[i] = (A[i][m-1] * inv[A[i][i]]) % MOD;
        for (int k=i-1;k>=0; k--) {
            A[k][m-1] -= A[k][i] * x[i];
            if (A[k][m-1] < 0) A[k][m-1] %= MOD;
            if (A[k][m-1] < 0) A[k][m-1] += MOD;
        }
    }

    return x;
}

int m[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    int N, M, P; cin >> N >> M >> MOD;

    for (int i = 1; i < MOD; i++) {
        for (int k = 1; k < MOD; k++)
            if ((i * k) % MOD == 1)
                inv[i] = k;
    }

    vector<vector<int> > mat(N * M, vector<int>(N * M + 1, 0));

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            m[i][k] = cnt++;
        }
    }

    cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            int x; cin >> x;
            for (int a = 0; a < N; a++)
                mat[cnt][m[a][k]] = 1;
            for (int a = 0; a < M; a++)
                mat[cnt][m[i][a]] = 1;
            mat[cnt][N*M] = MOD - x;
            cnt++;
        }
    }

    vector<int> res = gauss(mat);
    for (int i = 0; i < N*M; i++) {
        bool all_zero = true;
        for (int k = 0; k < N*M; k++)
            if (mat[i][k] != 0) { all_zero = false; break; }
        if (all_zero && mat[i][N*M] != 0) {
            cout << "-1\n";
            return 0;
        }
    }

    int ans = 0;
    for (int i = 0; i < res.size(); i++)
        ans += res[i];

    cout << ans << "\n";
    for (int i = 0; i < res.size(); i++) {
        for (int k = 0; k < res[i]; k++) {
            cout << (i + 1) << " ";
        }
    }
    cout << "\n";

    return 0;
}