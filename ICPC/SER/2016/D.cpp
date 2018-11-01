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
 
struct PT {
    LL x, y;
    PT() {}
    PT(LL x, LL y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    bool operator == (PT other) const {
     return (x == other.x) && (y == other.y); }
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
    PT operator * (LL c)         const { return PT(x*c, y*c); }
};
 
LL dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
LL dist2(PT p, PT q) { return dot(p - q, p - q); }
LL cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }
 
LL area_polygon(const vector<PT> &p) {
    LL area = 0;
    for (int i = 0; i < (int)p.size(); i++)
        area += cross(p[i], p[(i + 1) % (int)p.size()]);
    return abs(area); // double the area
}
 
//change < 0 comparisons to > 0 to produce hull PTs in CCW order
double cw(const PT & o, const PT & a, const PT & b) {
  return cross(a - o, b - o) < 0;
}
 
//convex hull from a range [lo, hi) of PTs
//monotone chain in O(n log n) to find hull PTs in CW order
//notes: the range of input PTs will be sorted lexicographically
template<class It> vector<PT> convex_hull(It lo, It hi) {
  int k = 0;
  if (hi - lo <= 1) return vector<PT>(lo, hi);
  vector<PT> res(2 * (int)(hi - lo));
  sort(lo, hi, [](PT a, PT b) {
                return mp(a.x, a.y) < mp(b.x, b.y);
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
 
int nxt(int i, int num_v) { return (i + 1) % num_v; }
int prev(int i, int num_v) { return (i - 1 + num_v) % num_v; }
 
bool dir(const PT& p, const PT& q, const PT& r, bool second) {
  if (!second) return cross(q-p,r-p) >= 0;
  return cross(q-p,r-p) <= 0;
}
 
bool is_tangent(const vector<PT>& polygon, int indx, const PT& p, bool second) {
  int sz = polygon.size();
  int a = nxt(indx, sz);
  int b = prev(indx, sz);
  if (dir(p, polygon[indx], polygon[a], second) &&
      dir(p, polygon[indx], polygon[b], second))
    return true;
  return false;
}
 
map<PLL, bool> in;
 
int main() {
  io;
 
  int N; cin >> N;
  int K; cin >> K;
 
  vector<PT> inner, outer;
  for (int i = 0; i < N; i++) {
    LL a, b; cin >> a >> b;
    if (i < K) {
      inner.pb(PT(a, b));
    }
    outer.pb(PT(a, b));
  }
 
  inner = convex_hull(inner.begin(), inner.end());
  outer = convex_hull(outer.begin(), outer.end());
  reverse(inner.begin(), inner.end()); // make ccw
  reverse(outer.begin(), outer.end());
 
  N = outer.size();
  K = inner.size();
 
  for (int i = 0; i < K; i++) {
    in[mp(inner[i].x, inner[i].y)] = i;
  }
 
  LL area = area_polygon(inner);
  LL diff = 0;
 
  int p = 0;
  int l = 0, r = 0;
  if (!in.count(mp(outer[p].x, outer[p].y))) {
    for (int i = 0; i < K; i++) {
      if (is_tangent(inner, i, outer[p], false)) {
        r = i;
      }
      if (is_tangent(inner, i, outer[p], true)) {
        l = i;
      }
    }
  } else {
    l = r = in[mp(outer[p].x, outer[p].y)];
  }
 
  int c = l;
  while (c != r) {
    int cc = (c + 1) % K;
    if (cc == r) break;
    int ccc = (cc + 1) % K;
 
    diff += abs(cross(inner[cc] - inner[l], inner[ccc] - inner[l]));
    c = cc;
  }
 
  LL ans = area;
  for (p = 0; p < N; p++) {
    while (!is_tangent(inner, r, outer[p], false)) {
      int rr = (r + 1) % K;
      diff += abs(cross(inner[r] - inner[l], inner[rr] - inner[l]));
      r = rr;
    }
 
    while (!is_tangent(inner, l, outer[p], true)) {
      int ll = (l + 1) % K;
      diff -= abs(cross(inner[l] - inner[r], inner[ll] - inner[r]));
      l = ll;
    }
 
    LL cur = abs(cross(inner[l] - outer[p], inner[r] - outer[p]));
    cur = cur + area - diff;
    ans = max(ans, cur);
  }
 
  cout << fixed << setprecision(1);
  if (ans % 2 == 0) {
    cout << ans / 2 << ".0\n";
  } else {
    ans = ans / 2;
    cout << ans << ".5\n";
  }
 
  return 0;
}
