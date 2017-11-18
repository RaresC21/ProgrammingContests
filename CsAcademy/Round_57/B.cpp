#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back

int main() {
#define int long long
    ios_base::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    string s; cin >> s;

    bool all_zero = true;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0') {
            all_zero = false;
            break;
        }
    }

    if (all_zero) {
        cout << N * K << "\n";
        return 0;
    }

    int pre = 0;
    int after = 0;
    int in = 0;

    int cur = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            cur++;
            in = max(in, cur);
        } else {
            cur = 0;
        }
    }

    int ans = in;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0') break;
        pre++;
    }

    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] != '0') break;
        after ++;
    }

    if (K == 1) {
        cout << ans << "\n";
        return 0;
    } else {
        cout << max(ans, after + pre) << "\n";
    }

    return 0;
}