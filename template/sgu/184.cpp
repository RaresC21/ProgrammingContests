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

  int P, M, C; cin >> P >> M >> C;
  int K, R, V; cin >> K >> R >> V;

  int a = P / K;
  int b = M / R;
  int c = C / V;

  cout << min(min(a, b), c) << "\n";
  
  return 0;
}
