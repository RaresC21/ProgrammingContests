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

VI prime;
int a[10005];

int main() {
  io;

  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  for (int i = 2; i <= K; i++) {
    bool p = true;
    for (int k = 2; k < i; k++) {
      if (i % k == 0) {
	p = false;
	break;
      }
    }
    if (p) prime.pb(i);
  }

  vector<PII> d;
  for (int p : prime) {
    int cnt = 0;
    while (K % p == 0) {
      K /= p;
      cnt++;
    }
    if (cnt > 0)
      d.pb(mp(p, cnt));
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    bool yes = true;
    for (auto cur : d) {
      int p = cur.A;
      int amnt = cur.B;

      int have = 0;
      while (a[i] % p == 0) {
	a[i] /= p;
	have++;
      }

      if (have * M < amnt) {
	yes = false;
	break;
      }
    }
    if (yes) {
      ans++;
    }
  }
  cout << ans << "\n";
  
  return 0;
}
