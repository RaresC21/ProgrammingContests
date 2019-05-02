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

  int Q; cin >> Q;

  LL l = 1, r = 1LL * INF*INF;
  LL ans = -1;
  while (l <= r) {
    LL mid = (l + r) / 2;
    LL p = 5;
    LL amnt = 0;
    while (p <= mid) {
      amnt += mid / p;
      p *= 5;
    }
    if (amnt >= Q) {
      r = mid - 1;
      if (amnt == Q)
	ans = mid;
    } else {
      l = mid + 1;
    }
  }

  if (ans == -1) {
    cout << "No solution\n";
  } else {
    cout << ans << "\n";
  }
  
  return 0;
}
