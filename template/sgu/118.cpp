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

  int T; cin >> T;
  while (T--) {
    int N; cin >> N;

    LL x; cin >> x;
    if (x == 0) {
      cout << "0\n";
      for (int i = 1; i < N; i++) cin >> x;
      continue;
    }

    LL cur = x;
    LL prod = x;
    for (int i = 1; i < N; i++) {
      cin >> x;
      prod = (prod * x) % 9;
      cur = (cur + prod) % 9;
    }
    if (cur == 0) cur = 9;
    cout << cur << "\n";
  }
  
  return 0;
}
