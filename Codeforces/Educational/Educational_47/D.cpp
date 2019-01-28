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

  int N, M; cin >> N >> M;

  if (M < N - 1) {
    cout << "Impossible\n";
    return 0;
  }
  
  int ans = 0;
  bool found = false;
  vector<PII> edge;
  for (int i = 1; i <= N && !found; i++) {
    for (int k = i + 1; k <= N; k++) {
      if (ans == M) {
	found = true;
	break;
      }

      if (__gcd(i,k) == 1) {
	edge.pb(mp(i,k));
	ans++;
      }
    }
  }

  if (ans != M) {
    cout << "Impossible\n";
  } else {
    cout << "Possible\n";
    for (auto e : edge) {
      cout << e.A << " " << e.B << "\n";
    }
  }

  return 0;
}
