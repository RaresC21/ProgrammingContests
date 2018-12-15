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

typedef complex<double> PT;

const int INF = 1e9;
const double eps = 1e-8;

#define X real()
#define Y imag()

inline double dot(const PT& p, const PT& q) { return real(conj(p) * q); }
inline double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }

//change < 0 comparisons to > 0 to produce hull PTs in CCW order
inline double cw(const PT & o, const PT & a, const PT & b) {
  return cross(a - o, b - o) < -eps;
}

//convex hull from a range [lo, hi) of PTs
//monotone chain in O(n log n) to find hull PTs in CW order
//notes: the range of input PTs will be sorted lexicographically
template<class It> vector<PT> convex_hull(It lo, It hi) {
  int k = 0;
  if (hi - lo <= 1) return vector<PT>(lo, hi);
  vector<PT> res(2 * (int)(hi - lo));
  sort(lo, hi, [](PT a, PT b) {
                return mp(a.X, a.Y) < mp(b.X, b.Y);
                }); //compare by x, then by y if x-values are equal
  for (It it = lo; it != hi; ++it) {
    while (k >= 2 && !cw(res[k - 2], res[k - 1], *it)) k--;
    res[k++] = *it;
  }
  int t = k + 1;
  for (It it = hi - 2; it != lo - 1; --it) {
    while (k >= t && !cw(res[k - 2], res[k - 1], *it)) k--;
    res[k++] = *it;
  }
  res.resize(k - 1);
  return res;
}

// project PT p onto line a, b
inline PT project(const PT& p, const PT& a, const PT& b) {
    return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

inline int prev_(int i, int n) {
  return (i + n - 1) % n;
}

inline int nxt_(int i, int n) {
  return (i + 1) % n;
}

vector<PT> pts;
int N;

inline bool tangent(int i, int k, int p) {
  PT a = pts[prev_(p, N)];
  PT b = pts[nxt_(p, N)];

  double cur = fabs(cross(pts[p] - pts[i], pts[k] - pts[i]));
  double aa = fabs(cross(a - pts[i], pts[k] - pts[i]));
  double bb = fabs(cross(b - pts[i], pts[k] - pts[i]));
  return cur > aa - eps && cur > bb - eps;
}

int main() {
  io;
  
  cin >> N;
  
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    pts.pb(PT(x, y));
  }

  pts = convex_hull(pts.begin(), pts.end());

  N = pts.size();

  if (N < 3) {
    cout << "0\n";
    return 0;
  }

  int p = 0;
  double ans = 0;
  int amnt = 0;
  for (int i = 0; i < N; i++) {
    for (int t = 0, k = i + 1; t < N; t++, k = (k + 1) % N) {
      
      // find the "tangent"
      while (p == i || p == k || !tangent(i, k, p)) {
	p = (p + 1) % N;
      }
      
      double area = abs(cross(pts[i] - pts[p], pts[k] - pts[p]));
      if (ans < area) ans = area;
    }
  }
  cout << fixed << setprecision(2);
  cout << ans/2.0 << "\n";


  return 0;
}
