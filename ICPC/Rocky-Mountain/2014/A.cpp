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

int main() {
    ios_base::sync_with_stdio(false);

    int N, T; cin >> N >> T;

    int amnt = 0;
    int ans = 0;
    FOR(i,0,N) {
        int x; cin >> x;
        if (amnt + x > T) break;
        ans ++;
        amnt += x;
    }

    cout << ans << "\n";

    return 0;
}