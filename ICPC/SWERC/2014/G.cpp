/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   G.cpp
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

bool rotate(vector<pii>& p1) {
    int N = 0;
    FOR(i,0,SZ(p1))
	N = max(N, p1[i].A);

    FOR(i,0,SZ(p1))
	p1[i] = MP(N - p1[i].B, p1[i].A);
    return true;
}

bool same(const vector<pii>& p1, const vector<pii>& p2) {
    FOR (i,0,SZ(p1)) {
	bool good = true;
	FOR (k,0,SZ(p2)) {
	    if (p1[(k + i) % SZ(p1)] != p2[k]) {
		good = false;
		break;
	    }
	}
	if (good) {
	    return true;
	}
    }
    return false;
}

vector<pii> map_coord(const vector<pii>& v) {
    set<int> x, y;
    for (auto cur : v)
	x.insert(cur.A), y.insert(cur.B);

    int cnt = 0;
    map<int, int>  new_x, new_y;
    for (auto cur : x) new_x[cur] = cnt++;

    cnt = 0;
    for (auto cur : y) new_y[cur] = cnt++;

    vector<pii> sol;
    for (auto cur : v)
	sol.push_back(MP(new_x[cur.A], new_y[cur.B]));

    return sol;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    vector<pii> p1(N), p2(N);
    FOR(i,0,N) cin >> p1[i].A >> p1[i].B;

    int M; cin >> M;
    FOR(i,0,N) cin >> p2[i].A >> p2[i].B;

    if (N != M) {
	cout << "no\n";
	return 0;
    }

    auto pp1 = map_coord(p1);
    auto pp2 = map_coord(p2);

    if (same(pp1, pp2)) {
	cout << "yes\n";
    } else if (rotate(pp1) && same(pp1, pp2)) {
	cout << "yes\n";
    } else if (rotate(pp1) && same(pp1, pp2)) {
	cout << "yes\n";
    } else if (rotate(pp1) && same(pp1, pp2)) {
	cout << "yes\n";
    } else {
	cout << "no\n";
    }

    
    
    return 0;
}
