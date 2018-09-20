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
const int MAX = 103;

char grid[MAX][MAX];
map<pair<PII, int>, bool> met;
bool found[300];
string target = "ICPCASIASG";
bool sol = false;
int N;

void solve(PII cur, int pos) {
  if (sol) return;
  if (pos == target.size()) {
    sol = true;
    return;
  }
  
  for (int i = -2; i <= 2; i++) {
    for (int k = -2; k <= 2; k++) {
      if (i*i + k*k != 5) continue;
      int x = cur.A + i;
      int y = cur.B + k;
      if (x >= 1 && x <= N && y >= 1 && y <= N) {
	auto cc = mp(x, y);
	if (!met[mp(cc, pos)]) {
	  met[mp(cc, pos)] = true;
	  if (grid[x][y] == target[pos])
	    solve(cc, pos + 1); 
	}
      }
    }
  }
  
}

int main() {
  io;
  
  cin >> N;
  string s; cin >> s;
  int cnt = 0;
  
  vector<PII> v;
  for (int i = 1; i <= N; i++) {
    for (int k = 1; k <= N; k++) {
      grid[i][k] = s[cnt++];
      if (grid[i][k] == 'I')
	v.pb(mp(i,k));
    }
  }
  
  for (auto p : v) {
    met.clear();
    solve(p, 1);
  }

  if (sol) cout << "YES\n";
  else cout << "NO\n";
  
  return 0;
}
