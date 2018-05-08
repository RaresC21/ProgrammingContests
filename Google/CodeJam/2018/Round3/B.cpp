#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;

int main() {

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        int N; cin >> N;
        vector<bool> used(N, false);
        VI freq(N);

        for (int i = 0; i < N; i++) {
            int D; cin >> D;
            if (D == 0) {
                cout << "-1\n";
                cout.flush();
                continue;
            }

            VI liked;
            for (int k = 0; k < D; k++) {
                int a; cin >> a;
                liked.pb(a);
                freq[a]++;
            }

            int best = 2*N;
            int indx = -1;
            for (int k : liked) {
                if (used[k]) continue;
                if (freq[k] < best) {
                    best = freq[k];
                    indx = k;
                }
            }

            cout << indx << "\n";
            if (indx != -1) used[indx] = true;
            else cout.flush();
        }

    }

    return 0;
}
