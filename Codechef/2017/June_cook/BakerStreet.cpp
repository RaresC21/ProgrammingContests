#include <bits/stdc++.h>
using namespace std;

struct PT {
    long long x, y;
    PT () {}
    PT (long long x, long long y) : x(x), y(y) {}
};

bool ccw(PT p1, PT p2, PT p3) {
    return (p2.y - p1.y) * 1LL * (p3.x - p2.x) -
	(p2.x - p1.x) * 1LL * (p3.y - p2.y) <= 0;
}

#define pb push_back
#define MAX 100005
int ans[MAX];
PT pt[MAX];
vector<int> section[MAX];

int main() {

    int T; cin >> T;
    while (T--) {
	int N; cin >> N;
	for (int i = 1; i <= N; i++) {
	    cin >> pt[i].x >> pt[i].y;
	}
	pt[N + 1].x = pt[N].x + 1;
	pt[N + 1].y = 10000001;
	section[0].push_back(N + 1);

	int cur = 0;
	for (int i = N; i >= 1; i--) {
	    ans[i] = -1;
	    if (pt[i + 1].y > pt[i].y) {
		section[++cur].clear();
		section[cur].pb(i);
		continue;
	    }

	    // we can disregard all of the sections smaller than current height
	    while (pt[i].y > pt[section[cur].back()].y) {
		cur--;
	    }
	    cur++;
	    
	    while (section[cur].size() > 1) {
		int sz = section[cur].size();
		if (ccw(pt[i], pt[section[cur][sz - 1]], pt[section[cur][sz - 2]]))
		    section[cur].pop_back();
		else
		    break;
	    }
	    ans[i] = section[cur].back();
	    section[cur].push_back(i);
	}

	for (int i = 1; i <= N; i++) {
	    cout << ans[i] << " ";
	    section[i].clear();
	} cout << "\n";
    }
    
    return 0;
}
