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

    int T; cin >> T;
    while (T--) {
        int N, S; cin >> N >> S;

        vector<int> ans;
        int amnt = N - 2;
        int sum = 0;
        bool bad = false;
        FOR(i,0,N/2) {
            int choose = -1;
            FOR(k,0,10) {
                if (i == 0 && k == 0) continue;
                int minim = sum + 2 * k;
                int maxim = sum + 2 * k + 9 * amnt;
                if (S >= minim && S <= maxim) {
                    choose = k;
                }
            }
            if (choose == -1) {
                bad = true;
                break;
            }
            ans.push_back(choose);
            amnt -= 2;
            sum += choose * 2;
        }

        if (bad) {
            cout << "-1\n";
        } else {
            for (int a : ans)
                cout << a;
            if (N % 2 == 1)
                cout << S - sum;
            for (int i = ans.size() - 1; i >= 0; i--)
                cout << ans[i];
            cout << "\n";
        }
    }

    return 0;
}