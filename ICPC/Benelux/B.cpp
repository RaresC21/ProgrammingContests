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

const double PI = acos(-1);
typedef complex<double> PT;
const double eps = 1e-8;
const int INF = 1e9;
const int MAX = 5e5 + 10;


struct circle {
  PT c;
  double r;
  circle() {}
  circle(PT c, double r) : c(c), r(r) {}
  bool contain(PT p) {
    return abs(p - c) < r + eps;
  }
  bool contain(const circle& other) {
    double d = abs(c - other.c);
    return d + other.r < r + eps;
  }
};
vector<circle> v;


double dot(const PT& p, const PT& q) { return real(conj(p) * q); }
double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }


// rotate PT a around PT o by th radians
PT rotate_ccw(const PT& a, const PT& o, double th) {
    return (a-o) * polar(1.0, th) + o;
}

//  intersection(s) of line a-b with circle @ c with radius r > 0
vector <PT> line_circle(PT a, PT b, PT c, double r) {
    vector<PT> ret;
    b = b - a;
    a = a - c;
    double A = norm(b);
    double B = dot(a, b);
    double C = norm(a) - r*r;
    double D = B*B - A*C;
    if (D < -eps) return ret;
    ret.push_back(c + a + b*(-B + sqrt(D)) / A);
    if (D > eps)
        ret.push_back(c + a + b*(-B - sqrt(D)) / A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> circle_circle(const circle& a, const circle& b){
  PT c1 = a.c, c2 = b.c;
  double r1 = a.r, r2 = b.r;
  vector<PT> ret;
  double d = abs(c1-c2);
  if (d > r1 + r2 || d + min(r1, r2) < max(r1, r2)) return ret;
  double x = (d*d - r2*r2 + r1*r1) / (2 * d);
  double y = sqrt(r1*r1 - x*x);
  PT v = (c2 - c1) / d;
  ret.push_back(c1 + v*x + rotate_ccw(v, PT(0,0), PI/2)*y);
  if (y > 0)
      ret.push_back(c1 + v*x - rotate_ccw(v, PT(0,0), PI/2)*y);
  return ret;
}

double dist[MAX];
int vertex[30][30];
vector<PT> inter[MAX];
vector<pair<int, double>> edge[MAX];

struct Node {
  int n;
  double d;
  Node (int n, double d): n(n), d(d) {}
  bool operator < (const Node& other) const {
    return d > other.d;
  }
};

void dijkstra() {
  for (int i = 0; i < MAX; i++) {
    dist[i] = -1;
  }

  priority_queue<Node> q;
  q.push(Node(0, 0));

  while (q.size()) {
    auto cur = q.top();
    q.pop();

    if (dist[cur.n] > -0.5) continue;
    dist[cur.n] = cur.d;

    for (auto adj : edge[cur.n]) {
      int a = adj.A;
      double d = adj.B + cur.d;
      q.push(Node(a, d));
    }
  }
}

//  whether p is on segment a-b
bool is_on_segment(const PT& p, const PT& a, const PT& b) {
  return abs(abs(a - p) + abs(b - p) - abs(a - b)) < eps;
}

bool cmp(const pair<double, int>& a, const pair<double, int>& b) {
  if (abs(a.A - b.A) < eps) return a.B > b.B;
  return a.A < b.A;
}

bool direct(PT start, PT finish) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i].contain(start) && v[i].contain(finish)) return true;
  }

  vector<pair<double, int>> event;
  for (int i = 0; i < v.size(); i++) {
    auto cur = line_circle(start, finish, v[i].c, v[i].r);
    if (cur.size() <= 1) {
      continue;
    }

    for (int tt = 0; tt <= 1; tt++) {
      if (!is_on_segment(cur[tt ], start, finish)) {
        if (is_on_segment(start, cur[tt], finish)) {
          cur[tt] = start;
        } else {
          cur[tt] = finish;
        }
      }
    }

    if (abs(cur[0] - start) > abs(cur[1] - start)) swap(cur[0], cur[1]);
    event.pb(mp(abs(start - cur[0]), 1));
    event.pb(mp(abs(start - cur[1]), -1));
  }
  if (event.empty()) return false;

  sort(event.begin(), event.end(), cmp);

  int cnt = 0;
  for (int i = 0; i < event.size(); i++) {
    if (event[i].B == 1) {
      cnt++;
    } else {
      cnt--;
      if (i != event.size() - 1 && cnt == 0) return false;
    }
  }
  return true;
}

int main() {
  io;

  cout << fixed << setprecision(9);

  int ax, ay, bx, by; cin >> ax >> ay >> bx >> by;
  PT start(ax, ay);
  PT finish(bx, by);

  int N; cin >> N;
  v.resize(N);
  for (int i = 0; i < N; i++) {
    int x, y, r; cin >> x >> y >> r;
    v[i] = circle(PT(x, y), r);
  }

  vector<circle> temp;
  for (int i = 0; i < N; i++) {
    bool within = false;
    for (int k = 0; k < N; k++) {
      if (i == k) continue;
      if (v[k].contain(v[i])) {
        within = true;
        break;
      }
    }
    if (!within) {
      temp.pb(v[i]);
    }
  }

  v = temp;
  temp.clear();
  N = v.size();

  if (N == 1) {
    cout << abs(start - finish) << "\n";
    return 0;
  }

  int cnt = 1;
  vector<PT> intersection;
  intersection.pb(start);
  for (int i = 0; i < N; i++) {
    for (int k = i + 1; k < N; k++) {
      if (i == k) continue;

      auto cur = circle_circle(v[i], v[k]);
      for (auto c : cur) {
        intersection.pb(c);
      }
    }
  }
  intersection.pb(finish);

  for (int i = 0; i < intersection.size(); i++) {
    for (int k = i + 1; k < intersection.size(); k++) {
      if (direct(intersection[i], intersection[k])) {
        double d = abs(intersection[i] - intersection[k]);
        edge[i].pb(mp(k, d));
        edge[k].pb(mp(i, d));
      }
    }
  }

  dijkstra();

  double ans = dist[intersection.size() - 1];
  if (ans < 0) {
    cout << "impossible\n";
  } else {
    cout << ans << "\n";
  }

  return 0;
}
