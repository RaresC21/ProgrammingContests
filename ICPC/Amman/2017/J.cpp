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
    string s; getline(cin, s);
    while (T--) {
        getline(cin, s);
        VI v;
        int cur = 0;
        FOR(i,0,SZ(s)) {
            if (s[i] == ' ') {
                v.push_back(cur);
                cur = 0;
            } else {
                cur++;
            }
        }

        int T = SZ(s);
        bool found = false;
        for (int k = 2; k <= T; k++) {
            if ((T - (k - 1)) % k == 0)  {
                int len = (T - (k - 1)) / k;

                int cur = 0;
                bool bad = false;
                FOR(i,0,SZ(v)) {
                    cur += v[i];
                    if (cur == len) {
                        cur = 0;
                    } else if (cur < len) {
                        cur++;
                    } else {
                        bad = true;
                        break;
                    }
                }
                if (!bad) {
                    cout << "YES\n";
                    found = true;
                    break;
                }
            }
        }
        if (found == false) {
            cout << "NO\n";
        }
    }

    return 0;
}