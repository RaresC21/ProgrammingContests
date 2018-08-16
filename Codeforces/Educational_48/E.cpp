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

const double EPS = 1e-8;
const int INF = 1e9;

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

// line of form Ax + By = C
struct Line {
  double A, B, C;
  Line (double A, double B, double C) : A(A), B(B), C(C) {}
  Line (const PT& p, const PT& q) {
    A = q.y - p.y;
    B = p.x - q.x;
    C = A * p.x + B * p.y;
  }
};

bool lineline(const Line& l1, const Line& l2, PT& res) {
  double det = l1.A * l2.B - l1.B * l2.A;
  if (fabs(det) < EPS) return false;
  res = PT((l2.B * l1.C - l1.B * l2.C) / det,
	   (l1.A * l2.C - l2.A * l1.C) / det);
  return true;
}

int main() {
  io;

  int Y, A, B; cin >> Y >> A >> B;
  int N; cin >> N;

  vector<PII> fences;
  vector<int> pref;

  for (int i = 0; i < N; i++) {
    int l, r; cin >> l >> r;
    fences.push_back(mp(l,r));
  }

  pref.resize(N);
  pref[0] = fences[0].B - fences[0].A;
  for (int i = 1; i < N; i++)
    pref[i] = pref[i-1] + (fences[i].B - fences[i].A);

  Line base(PT(A, Y), PT(B, Y));
  
  int Q; cin >> Q;
  for (int q = 0; q < Q; q++) {
    int x, y; cin >> x >> y;
    PT pt(x, y);

    PT left_hit, right_hit;
    int left_indx=-1, right_indx=-1;
    
    int minim = 0, maxim = N - 1;
    while (minim <= maxim) {
      int mid = (minim + maxim) / 2;
      PT hit;
      lineline(base, Line(pt, PT(fences[mid].B, 0)), hit);
      if (hit.x >= A) {
	maxim = mid - 1;
	left_hit = hit;
	left_indx = mid;
      } else {
	minim = mid + 1;
      }
    }

    minim = 0, maxim = N - 1;
    while (minim <= maxim) {
      int mid = (minim + maxim) / 2;
      PT hit;
      lineline(base, Line(pt, PT(fences[mid].A, 0)), hit);
      if (hit.x <= B) {
	minim = mid + 1;
	right_hit = hit;
	right_indx = mid;
      } else {
	maxim = mid - 1;
      }
    }

    if (right_indx == -1 || left_indx == -1) {
      cout << "0\n";
      continue;
    }

    int between = 0;

    if (right_indx != -1 && left_indx != -1) {
      between = pref[right_indx - 1] - pref[left_indx];
      if (right_indx - 1 < left_indx) between = 0;
    }
    
    PT hit1, hit2;
    lineline(base, Line(pt, PT(fences[left_indx].A, 0)), hit1);
    lineline(base, Line(pt, PT(fences[right_indx].B, 0)), hit2);

    double l = 0, r = 0;

    if (hit1.x <= B) {
      l = min(B*1.0, left_hit.x) - max(A*1.0, hit1.x); 
    }

    if (hit2.x >= A) {
      r = min(B*1.0, hit2.x) - max(A*1.0, right_hit.x);
    }
    
    if (left_indx >= right_indx) l = 0;

    double ans = l + r + (between * (1.0*y-Y)/y);

    cout << fixed << setprecision(9);
    cout << ans << "\n";
  }
  
  return 0;
}
