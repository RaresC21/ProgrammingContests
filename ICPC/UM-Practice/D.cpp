#include "bits/stdc++.h"
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

const int MAX = 200005;
const int INF = 1000000009;


const int ORD = 101 ; // Order of Square Matrix
const int MOD = 1000000007; // Modulo

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
    int mat[ORD][ORD];
    matrix(){
	for(int i = 0; i < ORD; i++)
	    for(int j = 0; j < ORD; j++)
		mat[i][j] = 0;
    }
    friend matrix operator * (matrix x, matrix y){
	matrix res;
	for(int i = 0; i < ORD; i++)
	    for(int j = 0; j < ORD; j++)
		for(int k = 0; k < ORD; k++)
		    res.mat[i][j] = add(res.mat[i][j], prod(x.mat[i][k], y.mat[k][j]));
	return res;
    }
};

matrix base;

matrix exponentiate(matrix cur, long long p){
    matrix result;
    for (int i = 0; i < ORD; i++) {
	result.mat[i][i] = 1;
    }
    if (p == 0) {
	return result;
    }
    if (p == 1) {
	return base;
    }
    while (p > 0) {
	if (p & 1) {
	    result = result * base;
	}
	base = base * base;
	p >>= 1;
    }
    return result;
}
     
// power(n) returns cur^{n}
matrix power(matrix cur, long long p) {
    base = cur;
    return exponentiate(cur, p);
}


int main() {
    ios_base::sync_with_stdio(false);
    
    int N, M; cin >> N >> M;
    int T; cin >> T;
    matrix adj;
    FOR(i,0,M) {
	int a, b; cin >> a >> b;
	adj.mat[a][b] = 1;
    }
    matrix ans = power(adj, T);
    
    FOR(i,1,N+1) {
	cout << ans.mat[1][i] << "\n";
    }
    
    return 0;
}
