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
  vector<PLL> v;
  for (int i = 0; i < N; i++) {
    LL a, b; cin >> a >> b;
    v.pb(mp(a, b));
  }

  sort(v.begin(), v.end());

  int r = -1;
  int ans = 0;
  

  for (int i = 0; i < v.size(); i++) {
    if (v[i].B > r) {
      r = v[i].B; 
    } else {
      ans++;
    }
  }

  cout << ans << "\n";
  
  return 0;
}
