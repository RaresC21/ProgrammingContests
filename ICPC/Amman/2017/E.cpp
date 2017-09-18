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

map<char, int> amnt;

int main() {
	ios_base::sync_with_stdio(false);

	int T; cin >> T;
	while (T--) {
		long long a, b; cin >> a >> b;
		cout << (a - 1) + b << "\n";
	}

	return 0;
}