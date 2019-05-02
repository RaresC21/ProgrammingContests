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
const int MAX = 1e6 + 10;

bool met[MAX];

int main() {
  io;

  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    met[x] = true;
  }

  int ans = 1;
  for (int i = 1; i < MAX; i++) {
    int cur = 0;
    for (int k = i; k < MAX; k += i) {
      if (met[k]) {
	cur++;
      }
      if (cur == 2) {
	ans = max(ans, i);
	break;
      }
    }
  }
  cout << ans << "\n";
  
  return 0;
}
