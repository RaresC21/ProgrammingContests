/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   F.cpp
*/

#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

const int MAX = 50005;
int par[MAX];
int area[MAX];
int sz[MAX];
int region[MAX];

int find(int a) {
    if (a != par[a])
	par[a] = find(par[a]);
    return par[a];
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
}

struct Rect {
    int x, y, h, w;
    Rect(int x, int y, int h, int w) : x(x), h(h), y(y), w(w) {}
};

map<pii, set<int> > points;

inline void test(int indx, int x, int y) {
    if (points.find(MP(x, y)) != points.end()) {
	for (auto p : points[MP(x, y)])
	    merge(indx, p);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    vector<Rect> v;
    FOR(i,0,N) {
	par[i] = i;
	int x, y, w, h; cin >> x >> y >> w >> h;
	area[i] = w * h;

	points[MP(x, y)].insert(i);
	points[MP(x + w, y)].insert(i);
	points[MP(x + w, y + h)].insert(i);
	points[MP(x, y + h)].insert(i);

	v.push_back(Rect(x, y, h, w));
    }

    FOR(i,0,N) {
	FOR(x,v[i].x,v[i].x+v[i].w+1) {
	    test(i, x, v[i].y);
	    test(i, x, v[i].y + v[i].h);
	}
	FOR(y,v[i].y,v[i].y+v[i].h+1) {
	    test(i, v[i].x, y);
	    test(i, v[i].x + v[i].w, y);
	}
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
	int p = find(i);
	region[p] += area[i];
	ans = max(ans, region[p]);
    }

    cout << ans << "\n";
	
    return 0;
}
