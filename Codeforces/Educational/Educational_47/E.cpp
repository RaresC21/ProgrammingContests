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
const int MAX = 1e6 + 10;
const int MOD = 998244353;

inline int exp(int a, int x) {
  int ans = 1;
  while (x) {
    if (x % 2 == 1) {
      ans = (1LL * ans * a) % MOD;
    }
    a = (1LL * a * a) % MOD;
    x /= 2;
  }
  return ans;
}

inline int inv(int a) {
  return exp(a, MOD - 2);
}

int a[MAX];

int main() {
  io;

  int N; cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
  }

  int two = inv(2);

  int ans = a[1];
  int pref = a[1];
  int last = pref;
  for (int i = 2; i <= N; i++) {
    pref = (pref - last + MOD) % MOD;
    pref = (pref + 1LL * a[i-1] * exp(two, i-1)) % MOD;

    last = (1LL * a[i] * exp(two, i-1)) % MOD;
    pref = (pref + last) % MOD;

    ans = (ans + pref) % MOD;
  }

  cout << (1LL * ans * exp(2, N-1)) % MOD << "\n";
  
  return 0;
}
