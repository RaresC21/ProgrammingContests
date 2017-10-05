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

int table[1000016];
int C[11];

int main() {
    ios_base::sync_with_stdio(false);

    int W; cin >> W;

    int n = 1000006;
    int k = 2;
    FOR(i,0,k) C[i] = i+1;

    table[0] = 1;
    for(int i=0; i<k; i++) {
        for(int j=C[i]; j<=n; j++) {
            table[j] += table[j-C[i]];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (table[i] == W) {
            cout << i << " " << 2 << "\n";
            cout << "1 2\n";
            return 0;
        }
    }

    return 0;
}