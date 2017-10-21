/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2010/
   J.cpp
*/

#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

const int N = 3;

bool gauss(vector< vector<double> > A) {
    int n = A.size();
    int m = SZ(A[0]);

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        if (fabs(A[i][n] / A[i][i]) == 1 && fabs(A[i][n] - A[i][i]) < 1e-13) x[i] = 0.0001; 
        else x[i] = A[i][n]/A[i][i];
	if (x[i] <= 1e-8) x[i] = 0.01;
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }

    FOR(i,0,N) if (x[i] <= 0 || x[i] >= 1) return false;
    if (fabs(x[0] + x[1] + x[2] - 1.0) > 1e-8) return false;
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);

    while (true) { 
	vector<vector<double> > A(N, vector<double>(N+1, 0));
	FOR(i,0,N) {
	    FOR(k,0,N) {
		cin >> A[k][i];
		A[k][i] /= 10000.0;
	    }
	    if (A[0][0] == 0 && A[1][0] == 0 && A[2][0] == 0) return 0;
	}
	FOR(i,0,N) {
	    cin >> A[i][N];
	    A[i][N] /= 10000.0;
	}
	
	if (gauss(A)) {
	    cout << "YES\n";
	} else {
	    cout << "NO\n";
	}
    }
    
    return 0;
}
