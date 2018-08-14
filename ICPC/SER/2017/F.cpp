#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;
const double PI = acos(-1);

#define pb push_back

struct PT {
  double x, y;
  PT () {}
  PT (double x, double y) : x(x), y(y) {}
  PT operator + (const PT& other) const { return PT(x + other.x, y + other.y); }
  PT operator - (const PT& other) const { return PT(x - other.x, y - other.y); }
  PT operator * (double val) const { return PT(x * val, y * val); }
  PT operator / (double val) const { assert(val != 0); return PT(x / val, y / val); }

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

struct Circle {
  PT cntr;
  double R;
  Circle(const PT& c, double r) : cntr(c), R(r) {}
};

pair<PT, PT> circle_circle(const Circle& c1, const Circle& c2) {
  double d = dist(c1.cntr, c2.cntr);
  if (d - EPS > c1.R + c2.R) return make_pair(PT(1e9,1e9), PT(1e9,1e9));
  if (d + min(c1.R, c2.R) + EPS < max(c1.R, c2.R)) return make_pair(PT(1e9,1e9), PT(1e9,1e9));
  
  double theta = acos((c1.R*c1.R + d*d - c2.R*c2.R) / (2*c1.R*d));
  
  PT b = c2.cntr - c1.cntr;
  PT pt1 = rotate_ccw(b, theta) * (c1.R / d);
  PT pt2 = rotate_ccw(pt1, 2*PI - 2*theta);
  return make_pair(c1.cntr + pt1, c1.cntr + pt2);
}

vector<Circle> v;

bool in(const PT& p) {
  for (int i = 0; i < v.size(); i++) {
    if (dist(p, v[i].cntr) - EPS > v[i].R) { return false; }
  }
  return true;
}

int main() {
  
  int N; cin >> N;

  for (int i = 0; i < N; i++) {
    double x, y, R; cin >> x >> y >> R;
    v.pb(Circle(PT(x,y), R));
  }

  if (N != 1) {
    vector<Circle> temp;
    for (int i = 0; i < N; i++) {
      bool good = true;
      for (int k = 0; k < N; k++) {
	if (i == k) continue;
	double d = dist(v[i].cntr, v[k].cntr);
	if (d + v[k].R + EPS < v[i].R) good = false;
      }
      if (good) temp.pb(v[i]);
    }
    v = temp;
    N = v.size();
  }
  
  if (N == 1) {
    cout << fixed << setprecision(3);
    cout << v[0].R + dist(PT(0,0), v[0].cntr) << "\n";
    return 0;
  }

  vector<PT> intersect;
  for (int i = 0; i < N; i++) {
    for (int k = i + 1; k < N; k++) {
      auto p = circle_circle(v[i], v[k]);
      auto p1 = p.first;
      auto p2 = p.second;
      if (in(p1)) { intersect.pb(p1); }
      if (in(p2)) { intersect.pb(p2); }
    }
    double d = dist(v[i].cntr, PT(0,0));
    PT far = PT(0,0);
    if (d > EPS) far = v[i].cntr * ((v[i].R + d) / d);
    if (in(far)) intersect.pb(far);
  }
    
  double ans = 0;
  for (auto p : intersect) {
    ans = max(ans, dist(p, PT(0,0)));
  }

  cout << fixed << setprecision(3);
  cout << ans << "\n";
  
  return 0;
}
