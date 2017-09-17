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
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

int main() {

    int N, X; cin >> N >> X;
    vector<vector<int> > primary(N, vector<int>(0, 0)),
                         secondary(N, vector<int>(0,0));
    if (X > N - 1) {
		cout << "-1\n";
		return 0;
	}

    int cur = 1;
	FOR(i,0,N) {
        FOR(k,0,X) {
            secondary[(i + k + 1) % N].push_back(cur);
            primary[i].push_back(cur);
            cur++;
        }
    }

    FOR(i,0,N) {
        for(auto x : primary[i]) cout << x << " ";
        for(auto x : secondary[i]) cout << x << " ";
        cout << "\n";
    }

	return 0;
}
