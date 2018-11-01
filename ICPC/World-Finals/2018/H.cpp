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
    int indx;
    PT() {}
    PT(LL x, LL y, int i = -1) : x(x), y(y), indx(i) {}
    PT(const PT &p) : x(p.x), y(p.y), indx(p.indx) {}
    bool operator == (PT other) const {
     return (x == other.x) && (y == other.y); }
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
    PT operator * (LL c)         const { return PT(x*c, y*c); }
};

LL dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
LL dist2(PT p, PT q) { return dot(p - q, p - q); }
LL cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }


// determine if lines from a to b and c to d are parallel or collinear
inline bool lines_parallel(PT a, PT b, PT c, PT d) {
    return cross(b - a, c - d) == 0;
}

inline bool lines_collinear(PT a, PT b, PT c, PT d) {
    return lines_parallel(a, b, c, d)
        && cross(a - b, a - c) == 0
        && cross(c - d, c - a) == 0;
}

// determine if line segment from a to b intersects with
// line segment from c to d
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

bool cmp_l(PT a, PT b) {
  return a.y > b.y;
}

bool cmp_r(PT a, PT b) {
  return a.y < b.y;
}

bool cmp_d(PT a, PT b) {
  return a.x < b.x;
}

bool cmp_u(PT a, PT b) {
  return a.x > b.x;
}

vector<PT> v;
vector<pair<PT, PT>> all;

bool can_go(int a, int b) {
  PT p1 = v[b];
  auto possible = all[v[b].indx];
  PT p2 = possible.A;
  if (p2 == p1) {
    p2 = possible.B;
  }

  if (segments_intersect(p1, p2, v[a], v[b + 1])) return true;
  return false;
}

int met[2000006];
int W, H;
PT bck(PT p) {
  PT ans;
  if (p.y == H) {
    ans.x = p.x + 1;
  } else if (p.y == 0) {
    ans.x = p.x - 1;
  } else {
    ans.x = p.x;
  }

  if (p.x == W) {
    ans.y = p.y - 1;
  } else if (p.x == 0) {
    ans.y = p.y + 1;
  } else {
    ans.y = p.y;
  }
  return ans;
}

PT nxt(PT p) {
  PT ans;
  if (p.y == H) {
    ans.x = p.x - 1;
  } else if (p.y == 0) {
    ans.x = p.x + 1;
  } else {
    ans.x = p.x;
  }

  if (p.x == W) {
    ans.y = p.y + 1;
  } else if (p.x == 0) {
    ans.y = p.y - 1;
  } else {
    ans.y = p.y;
  }
  return ans;
}

bool intersect_all(PT a, PT b) {
  for (auto p : all) {
    if (!segments_intersect(a, b, p.A, p.B)) return false;
  }
  return true;
}

void print(PT p) {
  cout << (p.x / 2);
  if (p.x % 2 == 1) cout << ".5";
  cout << " ";
  cout << (p.y / 2);
  if (p.y % 2 == 1) cout << ".5";
  cout << " ";
}

int main() {
  io;

  int N; cin >> N;
  cin >> W >> H;
  W *= 2, H *= 2;

  all.resize(N);
  vector<PT> l, d, r, u;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    x1 *= 2, y1 *= 2;
    x2 *= 2, y2 *= 2;
    all[i] = mp(PT(x1, y1, i), PT(x2, y2, i));

    if (x1 == 0) {
      l.pb(PT(x1, y1, i));
    } else if (x1 == W) {
      r.pb(PT(x1, y1, i));
    } else if (y1 == H) {
      u.pb(PT(x1, y1, i));
    } else {
      d.pb(PT(x1, y1, i));
    }

    if (x2 == 0) {
      l.pb(PT(x2, y2, i));
    } else if (x2 == W) {
      r.pb(PT(x2, y2, i));
    } else if (y2 == H) {
      u.pb(PT(x2, y2, i));
    } else {
      d.pb(PT(x2, y2, i));
    }
  }

  sort(l.begin(), l.end(), cmp_l);
  sort(r.begin(), r.end(), cmp_r);
  sort(u.begin(), u.end(), cmp_u);
  sort(d.begin(), d.end(), cmp_d);

  for (auto a : l) v.pb(a);
  for (auto a : d) v.pb(a);
  for (auto a : r) v.pb(a);
  for (auto a : u) v.pb(a);

  int a = 0, b = 0;
  int amnt = 1;
  met[v[a].indx] = 1;
  for (int i = 0; i < v.size(); i++) {
    // increment b until we decrease amnt
    while (b + 1 < v.size() && can_go(a, b)) {
      b++;
      if (met[v[b].indx] == 0) {
        amnt++;
      }
      met[v[b].indx] ++;
    }

    if (amnt == N && !(v[a].x == 0 && v[b].x == 0)
                  && !(v[a].x == W && v[b].x == W)
                  && !(v[a].y == 0 && v[b].y == 0)
                  && !(v[a].y == H && v[b].y == H)) {
      PT p1, p2;
      p1 = nxt(v[a]), p2 = nxt(v[b]);
      if (intersect_all(p1, p2)) {
        cout << "1\n";
        print(p1);
        print(p2);
        cout << "\n";
        return 0;
      }
      p1 = bck(v[a]), p2 = nxt(v[b]);
      if (intersect_all(p1, p2)) {
        cout << "1\n";
        print(p1);
        print(p2);
        cout << "\n";
        return 0;
      }
      p1 = bck(v[a]), p2 = bck(v[b]);
      if (intersect_all(p1, p2)) {
        cout << "1\n";
        print(p1);
        print(p2);
        cout << "\n";
        return 0;
      }
      p1 = nxt(v[a]), p2 = bck(v[b]);
      if (intersect_all(p1, p2)) {
        cout << "1\n";
        print(p1);
        print(p2);
        cout << "\n";
        return 0;
      }
    }

    if (b == v.size()) break;

    if (met[v[a].indx] == 1)
      amnt--;
    met[v[a].indx] --;
    a++;
  }

  cout << "2\n";
  H /= 2, W /= 2;
  cout << "0.5 0 " << W - 1 << ".5 " << H << '\n';
  cout << W - 1 << ".5 " << "0 0.5 " << H << '\n';

  return 0;
}
