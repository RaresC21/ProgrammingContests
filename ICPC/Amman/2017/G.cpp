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

const int MAX = 2001;
int val[MAX];

LL gcd(LL a, LL b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

LL lcm(LL a, LL b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        FOR(i,0,N) {
            cin >> val[i];
        }

        int ans = 0;
        FOR(i,0,N) {
            LL sum = 0;
            LL l = val[i];
            FOR(k,i,N) {
                sum += val[k];
                l = lcm(l, val[k]);
                if (l > 200000000000) {
                    break;
                }
                if (sum % l == 0) {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}