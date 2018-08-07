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

struct PT {
  double x, y;
  PT () {}
  PT(double x, double y) : x(x), y(y) {}
  PT operator + (const PT& other) { return PT(x + other.x, y + other.y); }
  PT operator - (const PT& other) { return PT(x - other.x, y - other.y); }
  PT operator / (double val) { assert(val != 0); return PT(x / val, y / val); }
};

inline double dot(PT a, PT b) {
  return a.x * b.x + a.y * b.y;
}

inline double dist(PT a, PT b) {
  return sqrt(dot(a-b, a-b));
}

void print(const PT& a) {
  cout << a.x << ", " << a.y << "\n";
}

int main() {
    ifstream cin("flags.in");
    
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
      cout << "Case " << t << ":\n";
      
      int N; cin >> N;
      vector<PT> v(N);
      for (int i = 0; i < N; i++) {
	int x, y; cin >> x >> y;
	v[i] = PT(x, y);
      }

      int Q; cin >> Q;
      for (int q = 0; q < Q; q++) {
	double sx, sy; cin >> sx >> sy;
	double ex, ey; cin >> ex >> ey;

	double ans = 1e18;
	PT pt;
	for (int i = 0; i < N; i++) {
	  int k = (i + 1) % N;
	  PT a = v[i], b = v[k];

	  for (int _ = 0; _ < 100; _++) {
	    PT l = a + (b - a) / 3;
	    PT r = b - (b - a) / 3;
	    double dl = dist(l, PT(sx, sy)) + dist(l, PT(ex, ey));
	    double dr = dist(r, PT(sx, sy)) + dist(r, PT(ex, ey));

	    if (dl < dr) {
	      b = r;
	      if (dl < ans) {
		ans = dl;
		pt = l;
	      }
	    } else {
	      a = l;
	      if (dr < ans) {
		ans = dr;
		pt = r;
	      }
	    }
	  }
	}

	cout << fixed << setprecision(7);
	cout << ans << " " << pt.x << " " << pt.y << "\n";
      }
    }
    
    return 0;
}
