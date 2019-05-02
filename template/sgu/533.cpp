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

  if (N < 21) {
    cout << "-1\n";
    return 0;
  }

  if (N == 21) {
    cout << "1\n";
    return 0;
  }

  if (N < 30) {
    cout << "-1\n";
    return 0;
  }

  
  
  int rem = N % 14;
  if (rem >= 2 && rem <= 12) {
    cout << N/14 << "\n";
    return 0;
  }

  cout << "-1\n";
  
  
  return 0;
}
