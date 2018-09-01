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

  int N; cin >> N;
  int X; cin >> X;
  VI v(N);
  map<int, int> met1, met2;
  int ans = 3;
  
  for (int i = 0; i < N; i++) {
    cin >> v[i];
    met1[v[i]] ++;
    if (met1[v[i]] >= 2) {
      cout <<  "0\n";
      return 0;
    }
    if (met2[v[i]]) {
      ans = min(ans, 1);
    }

    if ((v[i] & X) != v[i]) {
      v[i] &= X;

      if (met1[v[i]]) {
	ans = 1;
	continue;
      }
      
      met2[v[i]] ++;
      if (met2[v[i]] >= 2) {
	ans = min(ans, 2);
      }
    }
  }

  if (ans == 3) ans = -1;

  cout << ans << "\n";
  
  return 0;
}
