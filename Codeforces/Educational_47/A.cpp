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
const int MAX = 1003;

int cost[MAX], bill[MAX];

int main() {
  io;

  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> cost[i];
  }
  
  for (int i = 0; i < M; i++) {
    cin >> bill[i];
  }

  int indx = 0;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (indx >= M) break;
    if (cost[i] <= bill[indx]) {
      indx++;
      ans++;
    }
  }

  cout << ans << "\n";
  
  return 0;
}
