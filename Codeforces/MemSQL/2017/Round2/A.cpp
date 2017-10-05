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

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    string s; cin >> s;
    int ans = 0;
    FOR(i,1,N) {
        if (s[i] != s[i - 1]) {
            if (s[i - 1] == 'S') ans++;
            else ans--;
        }
    }

    if (ans > 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}