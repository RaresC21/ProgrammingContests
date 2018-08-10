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
const int MAX = 105;

int main() {
    io;

    int N, M; cin >> N >> M;
    VI amnt(MAX);
    for (int i = 0; i < M; i++) {
      int x; cin >> x;
      amnt[x]++;
    }

    int ans = 0;
    for (int len = 1; len < MAX*MAX; len++) {
      auto cur = amnt;
      int people = 0;
      for (int i = 1; i < MAX; i++) {
	while (cur[i] >= len) {
	  cur[i] -= len;
	  people++;
	}
      }
      if (people >= N) ans = len;
    }

    cout << ans << "\n";
    
    return 0;
}
