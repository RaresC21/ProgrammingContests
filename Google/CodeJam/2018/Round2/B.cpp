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

struct Sign {
    int M, N;
    Sign() {}
    Sign(int D, int A, int B) {
        M = D + A;
        N = D - B;
    }
};

vector<Sign> v;

int ans = 0;
int amnt = 0;
map<pair<int, int>, bool> met;

void get_answer(int i, int k, int M, int N) {
    int mid = (i + k) / 2;

    int cur = 0;
    int l = k, r = i;
    for (int j = mid; j <= k; j++) {
        if (v[j].N != N && v[j].M != M) break;
        r = j;
        cur++;
    }

    for (int j = mid - 1; j >= i; j--) {
        if (v[j].N != N && v[j].M != M) break;
        l = j;
        cur++;
    }

    if (met[mp(l,r)]) return;
    if (cur > ans) {
        met[mp(l,r)] = true;
        ans = cur;
        amnt = 1;
    } else if (cur == ans) {
        met[mp(l,r)] = true;
        amnt++;
    }
}

void solve(int i, int k) {
    if (i > k) return;
    int mid = (i + k) / 2;

    int M = v[mid].M;
    int N = v[mid].N;

    int N1 = N, N2 = N, M1 = M, M2 = M;

    for (int j = mid; j <= k; j++) {
        // Fix M for mid
        if (v[j].M != M) { // need to use other side
            N1 = v[j].N;
            break;
        }
    }

    // other direction
    for (int j = mid; j >= i; j--) {
        // Fix M for mid
        if (v[j].M != M) { // need to use other side
            N2 = v[j].N;
            break;
        }
    }

    for (int j = mid; j <= k; j++) {
        // Fix N for mid
        if (v[j].N != N) { // need to use other side
            M1 = v[j].M;
            break;
        }
    }

    for (int j = mid; j >= i; j--) {
        // Fix N for mid
        if (v[j].N != N) { // need to use other side
            M2 = v[j].M;
            break;
        }
    }

    get_answer(i, k, M, N1);
    get_answer(i, k, M, N2);
    get_answer(i, k, M1, N);
    get_answer(i, k, M2, N);

    solve(i, mid - 1);
    solve(mid + 1, k);
}

int main() {
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        int N; cin >> N;
        v.resize(N);
        for (int i = 0; i < N; i++) {
            int D, A, B; cin >> D >> A >> B;
            v[i] = Sign(D, A, B);
        }

        ans = 0;
        amnt = 0;
        met.clear();
        solve(0, N-1);

        cout << "Case #" << t << ": ";
        cout << ans << " " << amnt << "\n";
    }

    return 0;
}
