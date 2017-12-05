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

const int INF = 1e9;
const int MOD = 1000000007;
const int MAX = 4003;

int main() {
    #ifdef _time_it
    clock_t begin = clock();
    #endif

    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        long long L, N, M, D; cin >> L >> N >> M >> D;
        M = min(M, L);

        vector<LL> v(N);
        priority_queue<PLL, vector<PLL>, greater<PLL> > q;
        for (int i = 0; i < N; i++) {
            cin >> v[i];
            q.push(mp(v[i], i));
        }

        VLL timp(L);
        for (int i = 0; i < L; i++) {
            auto washer = q.top();
            q.pop();

            timp[i] = washer.A;
            q.push(mp(washer.A + v[washer.B], washer.B));
        }

        sort(timp.begin(), timp.end());

        priority_queue<LL, vector<LL>, greater<LL> > dry;
        for (int i = 0; i < M; i++) dry.push(0);

        LL ans = 0;
        for (int i = 0; i < L; i++) {
            LL end_time = dry.top();
            dry.pop();

            LL cur = max(end_time, timp[i]) + D;
            ans = max(ans, cur);
            dry.push(cur);
        }
        cout << ans << "\n";
        cerr << t << "\n";
    }

    #ifdef _time_it
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elpased time: ";
    cerr << fixed << setprecision(4) << elapsed_secs << "\n";
    #endif

    return 0;
}
