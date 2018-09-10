/* 
   Problem: 
You would like to take a maximum non intersecting path on the polygon that visits each point at most once.

More specifically your path can be represented as some sequence of distinct points. Your path is the straight line segments between adjacent points in order. These segments are not allowed to touch or intersect each other except at the points in your sequence.

Given the polygon, print the maximum length non-intersecting path that visits each point at most once.
*/

#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define INF 1e100
#define PI acos(-1)

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
};

double dist(PT a, PT b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dy * dy + dx * dx);
}

#define MAX 2600
#define pb push_back

int N;
int first_pt;
bool starting;
vector<PT> poly;
double dp[MAX][MAX][2];

double solve(int l, int r, int which) {
  if (l == r && !starting) return 0;
  starting = false;

  if (dp[l][r][which] > -0.5) return dp[l][r][which];
  
  int prev = (l + N - 1) % N;
  int nxt = (r + 1) % N;
  int pt = which ? r : l;
  
  if (prev == r) return 0;
  if (l == nxt) return 0;

  double left = solve(prev, r, 0) + dist(poly[pt], poly[prev]);
  double right = solve(l, nxt, 1) + dist(poly[pt], poly[nxt]);

  return dp[l][r][which] = max(left, right);
}

int main() {
  
  cin >> N;
  for (int i = 0; i < N; i++) {
    double x, y; cin >> x >> y;
    poly.pb(PT(x, y));
  }

  for (int i = 0; i < N; i++) {
    for (int k = 0; k < N; k++) {
      dp[i][k][0] = dp[i][k][1] = -1;
    }
  }
  
  double ans = 0;
  for (int i = 0; i < N; i++) {
    starting = true;
    first_pt = i;
    ans = max(ans, solve(i, i, 0));   
  }
  
  cout << fixed << setprecision(10);
  cout << ans << "\n";
  
  return 0;
}
