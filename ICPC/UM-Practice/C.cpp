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
     
const int INF = 1000000009;
const int MAX = 400005;
int N, M;
     
int two[MAX];
int maxim[MAX][30];
VI a;
     
void sparse_table() {
 	two[1] = 0;
	FOR(i,2,2*N) {
    	two[i] = two[i / 2] + 1;
    }
    FOR(i,0,2*N) {
        maxim[i][0] = a[i];
    }
    FOR(i,1,24) {
        for (int j = 0; j + (1 << i) < 2*N; j++) {
            maxim[j][i] = max(maxim[j][i - 1], maxim[j + (1 << (i - 1))][i - 1]);
        }
    }
}
     
int query(int a, int b) {
    int power_ = two[b - a + 1];
    return max(maxim[a][power_], maxim[b - (1 << power_) + 1][power_]);
}
     
int main() {
    ios_base::sync_with_stdio(false);
     
	cin >> N >> M;
    a.resize(2*N);
    FOR(i,0,N) {
    	cin >> a[i];
	}
    FOR(i,N,2*N)
    	a[i] = a[i - N];
     
	sparse_table();
     
    FOR(i,0,M) {
    	int start_, B; cin >> start_ >> B;
        int l = start_, r = 2 * N - 1;
        int ans = -1;
        while (l <= r) {
     	   int mid = (l + r) / 2;
        	int maxx = query(start_, mid);
        	if (maxx <= B) {
	       		ans = max(ans, mid);
            	l = mid + 1;
        	} else {
	        	r = mid - 1;
        	}
   		}	
     
		if (Ans >= start_ + N) {
	    	cout << "I will be back!\n";
	    } else if (ans == -1) {
	        cout << start_ << "\n";
		} else {
	    	cout << ((ans + 1) % N) << "\n";
	    }
	}
     
	return 0;
}