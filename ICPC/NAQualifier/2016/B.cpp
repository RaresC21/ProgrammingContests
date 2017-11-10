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

void print(vector< vector<double> > A) {
    int n = A.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++) {
            cout << A[i][j] << "\t";
            if (j == n-1) {
                cout << "| ";
            }
        }
        cout << "\n";
    }
    cout << endl;
}

vector<double> gauss(vector< vector<double> >& A) {
    int n = A.size();
    int m = A[0].size();

    for (int i=0; i<min(n,m); i++) {
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }
        for (int k=i; k<m;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        for (int k=i+1; k<n; k++) {
            double c = (A[k][i] / A[i][i]);
            for (int j=i; j<m; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] -= c * A[i][j];
                }
            }
        }
    }
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        if (i >= m) continue;
        x[i] = (A[i][m-1] / A[i][i]);
        for (int k=i-1;k>=0; k--) {
            A[k][m-1] -= A[k][i] * x[i];
        }
    }

    return x;
}

const int MAX = 35;
pair<int, int> conv[MAX*MAX];
map<pair<int, int>, int> map_;
double val[MAX*MAX];
pair<int, int> d[MAX][MAX][MAX];

int main() {

    int H; cin >> H;

    int cnt = 0;
    FOR(i,0,H) {
        FOR(k,0,i+1) {
            conv[cnt] = MP(i,k);
            map_[MP(i,k)] = cnt;
            d[i][k][0] = MP(i - 1, k - 1);
            d[i][k][1] = MP(i - 1, k);
            d[i][k][2] = MP(i + 1, k);
            d[i][k][3] = MP(i + 1, k + 1);
            cin >> val[cnt];
            cnt++;
        }
    }

    vector<vector<double> > A(H*(H+1)/2, vector<double>(H*(H+1)/2 + 1, 0));
    FOR(i,0,H*(H+1)/2) {
        FOR(k,0,4) {
            double x; cin >> x;
            if (x != 0) {
                pair<int, int> pos = conv[i];
                pair<int, int> adj = d[pos.A][pos.B][k];
                int indx = map_[adj];
                A[i][indx] = x;
            }
        }
        double x; cin >> x;
        A[i][i] = -1;
        A[i][H*(H+1)/2] = -x * val[i];
    }

    auto res = gauss(A);
    cout << fixed << setprecision(9) << res[0] << "\n";

    return 0;
}