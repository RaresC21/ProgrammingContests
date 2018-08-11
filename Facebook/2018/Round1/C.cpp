#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define pb push_back
#define mp make_pair
typedef long long LL;

const int MOD = 1e9 + 7;
const int INF = MOD - 1;
const long long LLINF = 1e18;

const int MAX = 200005;

int N, M, Z;
vector<int> UU(MAX), DD(MAX);
vector<int> L(22), R(22), U(22), D(22);
vector<int> h(MAX);

bool solve(double t) {
  double l = max(0.0, h[1] - t);
  double u = min(Z*1.0, h[1] + t);
  for (int i = 2; i <= N; i++) {
    double lowest = max(0.0, h[i] - t);
    double highest = min(Z*1.0, h[i] + t);
    double lowest_match = max(0.0, l - 1.0*DD[i - 1]);
    double highest_match = min(Z*1.0, u + 1.0*UU[i - 1]);

    u = min(highest, highest_match);
    l = max(lowest, lowest_match);

    if (u < l) return false;
  }
  return true;
}

int main() {
 
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N >> M;

    cin >> h[1] >> h[2];
    int W, X, Y; cin >> W >> X >> Y >> Z;
    for (int i = 3; i <= N; i++) {
      h[i] = (1LL * W * h[i - 2] + 1LL * X * h[i - 1] + Y) % Z;
    }

    for (int i = 0; i < M; i++) {
      cin >> L[i] >> R[i] >> U[i] >> D[i];
    }

    UU.clear(); UU.resize(N+1, INF);
    DD.clear(); DD.resize(N+1, INF);
    for (int i = 0; i < M; i++) {
      if (L[i] <= R[i]) {
        for (int k = L[i]; k < R[i]; k++) {
          UU[k] = min(UU[k], U[i]);
          DD[k] = min(DD[k], D[i]);
        }
      } else {
        for (int k = R[i]; k < L[i]; k++) {
          UU[k] = min(UU[k], D[i]);
          DD[k] = min(DD[k], U[i]);
        }
      }
    }

    double minim = 0, maxim = Z;
    for (int i = 0; i < 100; i++) {
      double mid = (minim + maxim) / 2;
      if (solve(mid)) {
	maxim = mid;
      } else {
	minim = mid;
      }
    }
    
    cout << "Case #" << t << ": ";
    cout << fixed << setprecision(6) << minim << "\n";
  }
  
  return 0;
}
