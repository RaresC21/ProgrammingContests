/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2010/
   A.cpp
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

bool solve(vector<pair<double, double> >& v, int len) {
    sort(v.begin(), v.end());
    if (v[0].A > 0) return false;

    FOR(i,1,SZ(v)) {
	if (v[i].A > v[i - 1].B) return false;
    }

    if (v.back().B < len) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);

    const int L = 100, H = 75;
    
    int X, Y;
    double W;
    cin >> X >> Y >> W;
    while (!(X == 0 && Y == 0 && W == 0.0)) {

	vector<pair<double, double> > event;
	FOR(i,0,X) {
	    double x; cin >> x;
	    event.push_back(MP(x - W/2, x + W/2));
	}

	bool a = solve(event, H);

	event.clear();
	FOR(i,0,Y) {
	    double y;
	    cin >> y;
	    event.push_back(MP(y - W/2, y + W/2));
	}
	
	bool b = solve(event, L);

	if (a && b) {
	    cout << "YES\n";
	} else {
	    cout << "NO\n";
	}
	
	cin >> X >> Y >> W;
    }
    
    return 0;
}
