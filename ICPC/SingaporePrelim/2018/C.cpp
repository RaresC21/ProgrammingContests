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
const int MOD = INF + 7;
const int MAX = 401;

int dp[MAX][MAX][MAX];
int N;
string S;

int add(int a, int b) {
  return (a + b) % MOD;
}

int exp(int a, int x) {
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

int solve(int pos, int l, int r) {
  if (l == r+1) return exp(26, N-pos); 
  if (l > r+1) return 0;
  if (pos == N) {
     return 0;
  }
  if (dp[pos][l][r] != -1) return dp[pos][l][r];
  
  int ans = 0;
  for (char c = 'A'; c <= 'Z'; c++) {
    if (l < r && S[l] == S[r] && S[l] == c) {
      ans = add(ans, solve(pos + 1, l + 1, r - 1));
    } else if (l < r && S[l] == c) {
      ans = add(ans, solve(pos + 1, l + 1, r));
    } else if (S[r] == c) {
      ans = add(ans, solve(pos + 1, l, r - 1));
    } else 
      ans = add(ans, solve(pos + 1, l, r));
  }
  return dp[pos][l][r] = ans;
}

int main() {
  io;

  cin >> N;
  cin >> S;

  if (N == 0 || N == 1) {
    cout << "1\n";
  } else {
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 0, N-1) << "\n";
  }


  
  return 0;
}
