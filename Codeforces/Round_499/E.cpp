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

inline int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
    io;

    int N, K; cin >> N >> K;
    int g; cin >> g;
    for (int i = 1; i < N; i++) {
      int x; cin >> x;
      g = gcd(g, x);
    }

    vector<bool> possible(K);
    int cur = g, ans = 0;

    cur = cur % K;
    while (!possible[cur]) {
      possible[cur] = true;
      ans++;
      cur = (cur + g) % K;
    }

    cout << ans << "\n";
    for (int i = 0; i < K; i++) {
      if (possible[i]) cout << i << " ";
    }
    cout << "\n";
    
    return 0;
}
