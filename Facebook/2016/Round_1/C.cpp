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

double solve_single() {
    int N; cin >> N;
    int A, B; cin >> A >> B;
    int len = B - A;

    VI v(N);
    vector<double> expect(N);

    LL total = 0;
    double total_expect = 0;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        total += v[i];

        expect[i] = (v[i] * 1.0 / len) * v[i] / 2.0;
        total_expect += expect[i];
    }

    int l = (A / total) * total;
    int l_end = l + total;
    double left_ = 0;
    for (int cur = 0, amnt = l ; ; amnt += v[cur++]) {
        if (amnt >= l_end) break;
        if (amnt + v[cur] < A) continue;
        if (amnt < A && amnt + v[cur] >= A) {
            int ll = (amnt + v[cur]) - A;
            left_ += ((v[cur] + (v[cur] - ll)) / 2.0) * (ll *1.0 / len);
        } else {
            left_ += expect[cur];
        }
    }

    int r = (B / total) * total;
    double right_ = 0;
    for (int cur = 0, amnt = r ; ; amnt += v[cur++]) {
        if (amnt + v[cur] > B) {
            right_ += ((B - amnt) * 1.0 / len) * ((B - amnt) * 1.0 / 2);
            break;
        }
        right_ += expect[cur];
    }

    int amnt = (B / total) - ((A + total - 1) / total);
    double ans = amnt * total_expect + right_ + left_;
    return ans;
}

int main() {
#ifdef TIMP
    clock_t start_time = clock();
#endif
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        auto ans = solve_single();
        cout << fixed << setprecision(9) << ans << "\n";
    }

#ifdef TIMP
    print_time(start_time);
#endif
    return 0;
}
