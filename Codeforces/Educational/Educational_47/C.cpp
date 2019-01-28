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

int N, M;

LL f(int i) {
  return 1LL * i * (i+1) / 2;
}

int main() {
  io;
  cin >> N >> M;
  
  LL a = f(N-1);
  LL b = -1;
  if (N % 2 == 1)
    b = 2 * f(N/2);
  else
    b = f(N/2) + f(N/2 - 1);

  LL ans = 0;
  for (int i = 0; i < M; i++) {
    int x, d; cin >> x >> d;

    ans += 1LL * x * N;
    if (d < 0) {
      ans += b * d;
    } else {
      
      ans += a * d;
    }
  }

  cout << fixed << setprecision(9);
  cout << ans * 1.0 / N  << "\n";
  
  return 0;
}
