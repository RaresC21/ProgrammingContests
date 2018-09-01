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
const int MAX = 100;
int a1[MAX];

int main() {
  io;

  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a1[i];
  }
  int diff = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    diff += a1[i] - x;
  }

  if (diff < 0) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
  }
  
  return 0;
}
