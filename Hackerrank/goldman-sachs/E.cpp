#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MOD 1000000007
#define MAX 1003
long long best[MAX], cur[MAX];
double cur_log[MAX], log_val[MAX];

inline int prod(int x, int y){
    long long res = x * 1LL * y;
    if(res >= MOD) res %= MOD;
    return res;
}

inline int add(int x, int y){
    int res = x + y;
    if(res >= MOD) res -= MOD;
    return res;
}

struct matrix{
    int mat[21][21];
    double log_mat[21][21];
    int ORD;
    matrix(int ORD) : ORD(ORD) {
	for(int i = 0; i < ORD; i++)
	    for(int j = 0; j < ORD; j++)
		mat[i][j] = 0;
    }
    matrix operator * (matrix y){
	matrix res(ORD);
	for(int i = 0; i < ORD; i++)
	    for(int j = 0; j < ORD; j++)
		for(int k = 0; k < ORD; k++) {
                    if (log_mat[i][k] + y.log_mat[k][j] > res.log_mat[i][j]) {
                        res.log_mat[i][j] = log_mat[i][k] + y.log_mat[k][j];
                        res.mat[i][j] = prod(mat[i][k], y.mat[k][j]);
                    }
                }
	return res; 
    }
};

// power(n) returns base ^ {n}
matrix power(matrix base, matrix cur, long long p){
    if(p == 1) return base;
    matrix res = power(base, cur, p >> 1);
    res = res * res;
    if(p & 1) res = res * base;
    return res;
}

#undef int
int main() {
#define int long long
    
    int n;
    cin >> n;
    int x;
    int s;
    int f;
    int m;
    cin >> x >> s >> f >> m;
    vector< vector<int> > A(n,vector<int>(n));
    vector< vector<double> > log_A(n,vector<double>(n));
    for(int A_i = 0;A_i < n;A_i++){
	for(int A_j = 0;A_j < n;A_j++){
	    int val; cin >> val;
	    log_A[A_i][A_j] = log(val);
	    A[A_i][A_j] = val;
	}
    }
    
    int ORD = n;
    matrix base(ORD);
    matrix ans(ORD);
    
    for (int i = 0; i < n; i++) {
	for (int k = 0; k < n; k++) {
	    base.mat[k][i] = A[i][k];
            base.log_mat[k][i] = log(A[i][k]);
            
	    ans.mat[k][i] = base.mat[k][i];
            ans.log_mat[k][i] = log(A[i][k]);
	}
    }
    
    ans = power(base, base, m);
    int mine = ((ans.mat[f][s] * x) + MOD) % MOD;
    cout << mine << "\n";
    
    return 0;
}
