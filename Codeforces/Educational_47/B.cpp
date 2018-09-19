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

  string s; cin >> s;
  
  int two = s.size();
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '2') {
      two = i;
      break;
    }
  }

  string p = "";
  for (int i = 0; i < two; i++) {
    p = p + s[i];
  }
  sort(p.begin(), p.end());
  cout << p;
  
  for (int i = two; i < s.size(); i++) {
    if (s[i] == '1') cout << "1";
  }

  for (int i = two; i < s.size(); i++) {
    if (s[i] != '1') cout << s[i];
  }
  cout << "\n";
  
  return 0;
}
