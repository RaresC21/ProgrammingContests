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

void solve_single() {
    int N, P; cin >> N >> P;
    VI v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    VI suf(N + 1);
    for (int i = N - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + v[i];
    }

    LL ans = 0;
    for (int i = 0; i < N; i++) {
        int indx = -1;
        int minim = 0, maxim = i;
        while (minim <= maxim) {
            int mid = (minim + maxim) / 2;
            int amnt = suf[mid] - suf[i + 1];
            if (amnt <= P) {
                maxim = mid - 1;
            } else {
                indx = max(indx, mid);
                minim = mid + 1;
            }
        }
        if (indx == -1) continue;
        ans += indx + 1;
    }
    ans = ((N * 1LL * (N + 1)) / 2) - ans;
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
