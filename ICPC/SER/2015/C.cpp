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
const double eps = 1e-8;
const int INF = 1e9;
const int MAX = 5000 + 10;

// rotate PT a around PT o by th radians
PT rotate_ccw(const PT& a, const PT& o, double th) {
    return (a-o) * polar(1.0, th) + o;
}

// find center of a circle of radius R that is tangent to both circles centered
// at a and b with radii r1, r2, respectively.
// need: rotate_ccw
pair<PT, PT> circle_tangent(PT a, double r1, PT b, double r2, double R) {
  double v = R + r2;
  double u = R + r1;
  double d = abs(a - b);
  double theta = acos((u*u + d*d - v*v) / (2*u*d));

  PT p1 = rotate_ccw(b, a, theta) - a;
  PT p2 = rotate_ccw(b, a, -theta) - a;

  p1 = p1 * (u / abs(p1));
  p2 = p2 * (u / abs(p2));
  return mp(p1 + a, p2 + a);
}

class DSU {
public:
    int parent[MAX];
    int rank_[MAX];
    int set_size[MAX];

    int find_set (int a) {
        if (a != parent[a])
            parent[a] = find_set(parent[a]);
        return parent[a];
    }

    void make_set(int a) {
        parent[a] = a;
        set_size[a] = 1;
        rank_[a] = 0;
    }

    void merge_set (int a, int b) {
        int root_a = find_set (a);
        int root_b = find_set (b);

        if (root_a == root_b) return;

        if (rank_[root_a] > rank_[root_b]) {
            parent[root_b] = root_a;
            set_size[root_a] += set_size[root_b];
        } else {
            parent[root_a] = root_b;
            set_size[root_b] += set_size[root_a];
        }
        if (rank_[root_a] == rank_[root_b])
            rank_[root_b]++;
    }

    int get_set_size (int a) {
        int root = find_set(a);
        return set_size[root];
    }
};

VI to4[MAX];

int main() {
  io;

  int N; cin >> N;

  vector<PT> v(N);
  DSU dsu;
  for (int i = 0; i < N; i++) {
    double x, y; cin >> x >> y;
    v[i] = PT(x,y);
    dsu.make_set(i);
  }


  for (int i = 0; i < N; i++) {
    for (int k = i + 1; k < N; k++) {
      if (abs(v[i] - v[k]) < 2 + eps) {
        dsu.merge_set(i, k);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int k = i; k < N; k++) {
      if (abs(v[i] - v[k]) < 4 + eps) {
        to4[i].pb(k);
        to4[k].pb(i);
      }
    }
  }

  int ans = 2;
  for (int i = 0; i < N; i++) {
    ans = max(ans, dsu.get_set_size(i) + 1);
    for (auto p : to4[i]) {
      auto cc = circle_tangent(v[i], 1, v[p], 1, 1);
      for (auto cur : {cc.A, cc.B}) {
        set<int> all;
        for (int k : to4[i]) {
          if (abs(cur - v[k]) < 2 + eps) {

            all.insert(dsu.find_set(k));
          }
        }

        int amnt = 0;
        for (int a : all) {
          amnt += dsu.get_set_size(a);
        }
        ans = max(ans, amnt + 1);
      }
    }
  }

  cout << ans << '\n';

  return 0;
}
