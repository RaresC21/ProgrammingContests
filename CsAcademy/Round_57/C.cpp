#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back

const int MAX = 100005;
bool hole[MAX];

int main() {
    ios_base::sync_with_stdio(false);

    int N, K; cin >> N >> K;

    VI fox(K);
    for (int i = 0; i < K; i++) {
        cin >> fox[i];
        fox[i] --;
    }
    for (int i = 0; i < K; i++) {
        int x; cin >> x;
        hole[x - 1] = true;
    }

    sort(fox.begin(), fox.end());

    int ans = 0;
    for (int f : fox) {
        int prv = (f - 1 + N) % N;
        int nxt = (f + 1) % N;
        if (hole[prv]) {
            hole[prv] = false;
            ans++;
        } else if (hole[nxt]) {
            hole[nxt] = false;
            ans++;
        } else {
            ans += 2;
        }
    }

    cout << ans << "\n";

    return 0;
}