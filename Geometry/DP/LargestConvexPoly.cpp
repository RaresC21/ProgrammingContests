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

using namespace std;
const double EPS = 1e-8;
const double PI = acos(-1);

struct PT {
  double x, y;
  PT () {}
  PT (double x, double y) : x(x), y(y) {}
  PT operator + (const PT& other) const { return PT(x + other.x, y + other.y); }
  PT operator - (const PT& other) const { return PT(x - other.x, y - other.y); }
  PT operator * (double val) const { return PT(x * val, y * val); }
  PT operator / (double val) const { assert(val != 0); return PT(x / val, y / val); }
  bool operator < (const PT& other) const;
  
  double mag() const { return sqrt(x*x + y*y); }
  
  friend ostream& operator << (ostream& os, const PT& pt) {
    os << fixed << setprecision(9);
    os << pt.x << " " << pt.y << "\n";
    return os; }
};

inline double dot(const PT& p, const PT& q) {
  return p.x * q.x + p.y * q.y;
}

inline double cross(const PT& p, const PT& q) {
  return p.x * q.y - p.y * q.x;
}

// rotate point a around origin by theta degrees
inline PT rotate_ccw(const PT& a, double theta) {
  double c = cos(theta);
  double s = sin(theta);
  return PT(c * a.x - s * a.y,
	    s * a.x + c * a.y);
}

inline PT rotate_ccw(const PT& a, const PT& o, double theta) {
  PT temp = a - o;
  return rotate_ccw(temp, theta) + o;
}

inline double dist(const PT& p, const PT& q) {
  return sqrt(dot(p-q, p-q));
}

// is b ccw wrt c about a?
inline bool ccw(const PT& a, const PT& b, const PT& c) {
  return cross(b - a, c - a) < 0;
}

inline double angle(const PT& a, const PT& b) {
  double theta = acos(dot(a, b) / (a.mag() * b.mag()));
  if (!ccw(PT(0,0), a, b)) return -theta;
  return theta;
}

inline double angle(const PT& p, const PT& o, const PT& q) {
  return angle(p - o, q - o);
}

// sort points ccw about origin
bool PT::operator < (const PT& other) const {
  double a1 = angle(PT(1,0), *this);
  double a2 = angle(PT(1,0), other);
  if (a1 < 0) a1 += 2*PI;
  if (a2 < 0) a2 += 2*PI;
  return a1 < a2;
}

const int MAX = 101;
PT pt[MAX];
int dp[MAX][MAX];

int main() {
  io;

  int N; cin >> N;
  for (int i = 1; i <= N; i++) {
    double x, y; cin >> x >> y;
    pt[i] = PT(x, y);
  }

  sort(pt + 1, pt + N + 1);

  for (int i = 1; i < N; i++) {
    dp[i][0] = 2;
  }

  int ans = 3;
  for (int i = 2; i <= N; i++) {
    for (int k = 1; k < i; k++) {
      for (int j = 0; j < k; j++) {
	if (cross(pt[k] - pt[j], pt[i] - pt[j]) > -EPS) continue;
	dp[i][k] = max(dp[i][k], dp[k][j] + 1);
	ans = max(ans, dp[i][k]);

      }
    }
  }

  cout << ans << "\n";
  
  return 0;
}
