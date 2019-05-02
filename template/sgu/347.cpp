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

bool cmp(const string& a, const string& b) {
  return a + b < b + a;
}

int main() {
  io;

  int N; cin >> N;
  vector<string> s(N);
  for (int i = 0; i < N; i++) {
    cin >> s[i];
  }

  sort(s.begin(), s.end(), cmp);

  for (auto a : s)
    cout << a;
  cout << "\n";
  
  return 0;
}
