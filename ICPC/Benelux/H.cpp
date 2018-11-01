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

const double eps = 1e-8;
const int INF = 1e9;
const int MAX = 1e5 + 10;

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
    // PT operator / (LL c)     const { return PT(x / c, y / c); }
};

LL dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
LL dist2(PT p, PT q) { return dot(p - q, p - q); }
LL cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }

// double dot(const PT& p, const PT& q) { return real(conj(p) * q); }
// double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }


// determine if lines from a to b and c to d are parallel or collinear
// note: works with Long Long (no intermediate fractions
inline bool lines_parallel(PT a, PT b, PT c, PT d) {
    return cross(b - a, c - d) == 0;
}

// note: works with Long Long (no intermediate fractions)
inline bool lines_collinear(PT a, PT b, PT c, PT d) {
    return lines_parallel(a, b, c, d)
        && cross(a - b, a - c) == 0
        && cross(c - d, c - a) == 0;
}

// determine if line segment from a to b intersects with
// line segment from c to d
// note: works with Long Long (no intermediate fractions)
inline bool segments_intersect(PT a, PT b, PT c, PT d) {
    if (lines_collinear(a, b, c, d)) {
        if (a == c || a == d ||
            b == c || b == d) return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    LL c1 = cross(d - a, b - a);
    LL c2 = cross(c - a, b - a);
    if ((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return false;

    c1 = cross(a - c, d - c);
    c2 = cross(b - c, d - c);
    if ((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return false;
    return true;
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

int main() {
  io;

  int N; cin >> N;

  DSU dsu;

  vector<pair<PT, PT>> segments;
  for (int i = 0; i < N; i++) {
    LL x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    segments.pb(mp(PT(x1, y1), PT(x2, y2)));
    dsu.make_set(i);
  }

  int edges = 0, vertices = 0;
  for (int i = 0; i < N; i++) {
    bool has_edge = false;
    for (int k = 0; k < N; k++) {
      if (i == k) continue;
      if (segments_intersect(segments[i].A, segments[i].B, segments[k].A, segments[k].B)) {
        if (k > i) vertices ++;

        if (has_edge) {
          edges += 1;
        } else {
          has_edge = true;
        }

        dsu.merge_set(i, k);
      }
    }
  }

  int comp = 0;
  vector<bool> met(N);
  for (int i = 0; i < N; i++) {
    int cur = dsu.find_set(i);
    if (!met[cur] && dsu.get_set_size(cur) != 1) {
      met[cur] = true;
      comp ++;
    }
  }

  cout << edges - vertices + comp << "\n";

  return 0;
}
