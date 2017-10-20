/* 
   /home/rares/ProgrammingContests/ICPC/NWERC/2014/
   B.cpp
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

#define x real()
#define y imag()
typedef complex<double> PT;

vector<PT> station;
double v_bike, v_walk;
PT start, finish;
PT p[4];
int N; 

inline double walk(const PT& a, const PT& b) {
    double d = abs(a - b);
    return d / v_walk;
}

inline double bike(const PT& a, const PT& b) {
    double d = abs(a - b);
    return d / v_bike;
}

inline double solve(const PT& s, const PT& e) {
    double ans = 1e9;
    FOR(k,0,4) {
	PT l = p[k];
	PT r = p[(k+1)%4];
	FOR(i,0,50) {
	    PT m1 = l + (r - l) / 3.0;
	    PT m2 = r - (r - l) / 3.0;
	    double val1 = bike(s, m1) + walk(m1, e);
	    double val2 = bike(s, m2) + walk(m2, e);
	    ans = min(ans, min(val1, val2));
	    if (val1 < val2) {
		r = m2;
	    } else {
		l = m1;
	    }
	}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    cin >> v_walk >> v_bike;
    double x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;

    p[0] = PT(x1, y1);
    p[1] = PT(x2, y1);
    p[2] = PT(x2, y2);
    p[3] = PT(x1, y2);

    double xx, yy;
    cin >> xx >> yy; start = PT(xx, yy);
    cin >> xx >> yy; finish = PT(xx, yy);

    cin >> N;
    station.resize(N);
    FOR(i,0,N) {
	cin >> xx >> yy;
	station[i] = PT(xx, yy);
    }

    double ans = walk(start, finish);
    FOR(i,0,N) {
	FOR(k,0,N) {
	    if (i == k) continue;
	    double cur = walk(start, station[i]) +
		bike(station[i], station[k]) +
		walk(station[k], finish);
	    ans = min(ans, cur);
	}
    }

    // walk to station. Drop bike at a border.
    FOR(i,0,N) {
	double cur = solve(station[i], finish);
	ans = min(ans, cur + walk(start, station[i]));

	// or walk to border, and drop at station
	// (same as previous, only start at finish point)
	cur = solve(station[i], start);
	ans = min(ans, cur + walk(finish, station[i]));
    }

    FOR(i,0,4) {
	PT l = p[i], r = p[(i+1)%4];
	FOR(k,0,50) {
	    PT m1 = l + (r - l) / 3.0;
	    PT m2 = r - (r - l) / 3.0;
	    double val1 = walk(start, m1) + solve(m1, finish);
	    double val2 = walk(start, m2) + solve(m2, finish);
	    ans = min(ans, min(val1, val2));
	    if (val1 < val2) {
		r = m2;
	    } else {
		l = m1;
	    }
	}
    }

    cout << fixed << setprecision(9) << ans << "\n";
    
    return 0;
}
