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
const int MAX = 1003;
string v[2];
bool single[2][MAX];

void solve_single() {
    int N; cin >> N;

    memset(single, false, sizeof(single));
    for (int i = 0; i < 2; i++) {
        cin >> v[i];
        for (int k = 0; k < N; k++) {
            if (v[i][k] == 'X') continue;

            int around = 0;
            if (k > 0 && v[i][k - 1] == 'X') around++;
            if (k < N - 1 && v[i][k + 1] == 'X') around++;
            if (around == 2) {
                single[i][k] = true;
            } else if (around == 1 && (k == 0 || k == N - 1)) {
                single[i][k] = true;
            } else if (around == 0 && N == 1) {
                single[i][k] = true;
            }
        }
        v[i] = v[i] + 'X';
    }
    N++;

    int ans = 0;
    for (int i = 0; i < 2; i++) {
        int other = (i + 1) % 2;
        bool available = true;
        for (int k = 0; k < N; k++) {
            if (v[i][k] == 'X') {
                if (k > 0 && v[i][k - 1] != 'X') {
                    ans++;
                    available = true;
                }
                continue;
            }
            if (single[i][k]) {
                if (single[other][k] || v[other][k] == 'X') {
                    ans++;
                    v[other][k] = 'X';
                }
                v[i][k] = 'X';
            } else {
                if (single[other][k]) {
                    if (available) {
                        available = false;
                    } else {
                        ans++;
                    }
                    v[other][k] = 'X';
                }
            }
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
