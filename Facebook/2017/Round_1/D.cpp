#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

const int INF = 1e9;
const int MOD = 1000000007;
const int MAX = 4003;

int fact[MAX];
int inv_fact[MAX];
int inv[MAX];
vector<int> r;

inline int add(int a, int b) {
    int x = a + b;
    if (x > MOD) x -= MOD;
    return x;
}

inline int sub(int a, int b) {
    int x = a - b;
    if (x < 0) x += MOD;
    return x;
}

inline int mult(int a, int b) {
    LL x = a * 1LL * b;
    if (x > MOD) x %= MOD;
    return x;
}

int exp(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2 == 1) {
            ans = mult(ans, a);
        }
        x /= 2;
        a = mult(a, a);
    }
    return ans;
}

void combinatorics_init() {
    fact[0] = 1;
    inv_fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = mult(fact[i - 1], i);
        inv_fact[i] = exp(fact[i], MOD - 2);
        inv[i] = exp(i, MOD - 2);
    }
}

inline int binomialCo(int N, int r) {
    int res = 1;
    r=(r<(N-r))?r:(N-r);
    for(int i = 1; i <= r; i++, N--) {
        res = mult(res, N);
        res = mult(res, inv[i]);
    }
    return res;
}

// x1 + ... + x_n = m
int stars(int n, int m) {
    return binomialCo(n + m - 1, n - 1);
}

inline int less_than(int x) {
    int ans = 0;
    int minim = 0, maxim = r.size() - 1;
    while (minim <= maxim) {
        int mid = (minim + maxim) / 2;
        if (r[mid] < x) {
            minim = mid + 1;
            ans = max(ans, mid + 1);
        } else {
            maxim = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    combinatorics_init();

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int N, M; cin >> N >> M;
        r.resize(N);

        int all = 0;
        for (int i = 0; i < N; i++) {
            cin >> r[i];
            all += r[i] * 2;
        }

        if (N == 1) {
            cout << M << "\n";
            continue;
        }

        sort(r.begin(), r.end());


        int spaces = M - 1 - all;
        int none = 0;
        if (spaces >= 0)
            none = mult(fact[N], stars(N + 1, spaces));

        int one_side = 0;
        for (int i = 1; i < MAX; i++) {
            int cur_spaces = spaces + i;
            if (cur_spaces < 0) continue;
            if (cur_spaces > M - 1) break;

            // how many umbrellas could I place on the edge?
            int amnt = N - less_than(i);
            if (amnt == 0) continue;

            one_side = add(one_side,
                mult(fact[N - 1],
                    mult(amnt, stars(N, cur_spaces))));
        }
        one_side = add(one_side, one_side); // could be on left or right side.

        int both = 0;
        for (int a1 = 1; a1 < MAX; a1++) {
            for (int a2 = 1; a2 < MAX; a2++) {
                int cur_spaces = spaces + a1 + a2;
                if (cur_spaces < 0) continue;
                if (cur_spaces > M - 1) break;

                if (a1 + a2 > MAX) break;
                int l = N - less_than(a1);
                int r = N - less_than(a2);
                int amnt = sub(mult(l, r), min(l, r));

                if (amnt == 0) continue;

                both = add(both,
                    mult(fact[N - 2],
                        mult(amnt, stars(N - 1, cur_spaces))));
            }
        }

        int ans = add(none, add(one_side, both));

        cout << ans << "\n";
    }

    return 0;
}
