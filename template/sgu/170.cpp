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

  string a, b; cin >> a >> b;
  if (a.size() != b.size()) {
    cout << "-1\n";
    return 0;
  }

  VI plus_a, plus_b;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == '+') plus_a.pb(i);
    if (b[i] == '+') plus_b.pb(i);
  }

  if (plus_a.size() != plus_b.size()) {
    cout << "-1\n";
    return 0;
  }

  int ans = 0;
  for (int i = 0; i < plus_a.size(); i++) {
    ans += abs(plus_a[i] - plus_b[i]);
  }
  cout << ans << "\n";
  
  return 0;
}
