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
const int MAX = 1e4 + 10;

bool is[MAX];
VI prime;
int col[MAX];

int main() {
  //  io;

  int N; cin >> N;
  if (N == 1) {
    cout << "1\n1\n";
    return 0;
  }

  int num = 0;
  for (int i = 1; i <= N; i++) {
    num = max(num, col[i] + 1);
    for (int k = i + i; k <= N; k += i) {
      col[k] = max(col[k], col[i] + 1);
    }
  }

  cout << num << "\n";
  for (int i = 1; i <= N; i++)
    cout << 1 + col[i] << " ";
  cout << "\n";
  
  return 0;
}
