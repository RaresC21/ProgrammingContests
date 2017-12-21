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

void print_time(const clock_t& begin) {
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elapsed time: ";
    cerr << fixed << setprecision(4) << elapsed_secs << "\n";
}

const int INF = 1e9;

int dist2(PII p, PII q) {
    int dx = p.A - q.A;
    int dy = p.B - q.B;
    return dx*dx + dy*dy;
}

void solve_single() {
    int N; cin >> N;
    vector<PII> v;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        v.pb(mp(a, b));
    }

    int ans = 0;
    for (int i = 0; i < N; i++) { // center point
        map<int, int> dist;
        for (int k = 0; k < N; k++) {
            if (i == k) continue;
            int d = dist2(v[i], v[k]);
            dist[d] ++;
        }
        for (auto d : dist) {
            ans += d.B * (d.B - 1) / 2;
        }
    }
    cout << ans << "\n";
}

int main() {
    #ifdef TIMP
    clock_t start_time = clock();
    #endif
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve_single();
    }

    #ifdef TIMP
    print_time(start_time);
    #endif
    return 0;
}
