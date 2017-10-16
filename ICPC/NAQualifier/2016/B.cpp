#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

vector<double> gauss(vector< vector<double> >& A) {
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
            int c = (A[k][i] / A[i][i]) % MOD;
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
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        if (i >= m) continue;
        x[i] = (A[i][m-1] / A[i][i]) % MOD;
        for (int k=i-1;k>=0; k--) {
            A[k][m-1] -= A[k][i] * x[i];
            if (A[k][m-1] < 0) A[k][m-1] %= MOD;
            if (A[k][m-1] < 0) A[k][m-1] += MOD;
        }
    }

    return x;
}

const int MAX = 40;
int conv[MAX][MAX];
map<pair<int, int>, int> map_;
int val[MAX][MAX];
int d[MAX][MAX][MAX];

int main() {

    int H; cin >> H;

    int cnt = 0;
    FOR(i,0,H) {
        FOR(k,0,i) {
            conv[cnt] = MP(i,k);
            map_[MP(i,k)] = cnt++;
            d[i][k][0] = MP(i - 1, k - 1);
            d[i][k][1] = MP(i - 1, k);
            d[i][k][2] = MP(i + 1, k - 1);
            d[i][k][3] = MP(i + 1, k + 1);
            cin >> val[i][k];
        }
    }

    vector<vector<double> > A(H*(H+1)/2, vector<double>(H*(H+1)/2, 0));
    FOR(i,0,H*(H+1)/2) {
        FOR(k,0,4) {
            double x; cin >> x;
            if (x != 0) {
                int cur = conv[i];
                pair<int, int> pos = map_[cur];
                pair<int, int> adj = d[pos.A][pos.B][k];
                int indx = map_[adj];
                A[i][indx] = x;
            }
        }
        A[i][i] = -1;
    }

    auto res = gauss(A);


    return 0;
}