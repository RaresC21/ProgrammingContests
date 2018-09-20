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
const int BUCKET = 500;

int amnt[200000 + 10];
int add[BUCKET][BUCKET];

int main() {
  io;

  int N, Q; cin >> N >> Q;
  for (int q = 0; q < Q; q++) {
    int t; cin >> t;
    if (t == 1) {
      int A, B, C; cin >> A >> B >> C;
      if (B < BUCKET) {
	add[B][A] += C;
      } else {
	for (int i = A; i <= N; i += B)
	  amnt[i] += C;
      }
    } else {
      int D; cin >> D;
      int ans = amnt[D];
      for (int b = 1; b < BUCKET; b++) {
	ans += add[b][D % b];
      }
      cout << ans << "\n";
    }
  }
  
  return 0;
}
