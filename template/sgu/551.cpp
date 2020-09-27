#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_top
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;

int main() {
  io;


  int N, t[3];
  cin >> N >> t[1] >> t[2];

  int amnt = 0;
  LL timp = 0;
  std::priority_queue<PLL, std::vector<PLL>, std::greater<PLL> > q;
  q.push(mp(t[1], 1));
  q.push(mp(t[2], 2));

  bool here = false;
  while (true) {
    auto cur = q.top();
    q.pop();

    amnt++;
    timp = cur.A;

    if (q.top().A == timp && amnt + 1 >= N) {
      amnt++;
      q.pop();
      here = true;
      break;
    }

    if (amnt == N) break;

    q.push(mp(timp + t[cur.B], cur.B));
  }

  if (!here) {
    amnt++;
    timp = q.top().A;
  }
  cout << amnt << " " << timp << "\n";

  return 0;
}
