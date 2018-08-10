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
    io;

    int N, K; cin >> N >> K;
    string s; cin >> s;
    sort(s.begin(), s.end());

    int amnt = 0;
    int ans = 0;
    int last = 0;
    for (int i = 0; i < N; i++) {
      if (amnt == K) break;
      if (last + 2 > s[i]) continue;
      amnt++;
      ans += s[i] - 'a' + 1;
      last = s[i];
    }

    if (amnt != K) {
      cout << "-1\n";
    } else {
      cout << ans << "\n";
    }
    
    return 0;
}
