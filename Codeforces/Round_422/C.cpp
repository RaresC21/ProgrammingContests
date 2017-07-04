#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

struct Event {
    int pos;
    int type;
    lli cost;
    int duration; 
    Event (int pos, int type, lli c, int d) : pos(pos), type(type), cost(c), duration(d) {}
    bool operator < (const Event& other) const {
	if (pos == other.pos) {
	    return type > other.type;
	}
	return pos < other.pos;
    }	
};

#define INF 100000000000000000
#define MAX 200005
lli best[MAX];

int main() {
    
    for (int i = 0; i < MAX; i++)
	best[i] = INF;
    
    int N, x; cin >> N >> x;
    
    vector<Event> v;
    for (int i = 0; i < N; i++) {
	int l, r, c; cin >> l >> r >> c;
	v.pb(Event(l, 1, c, r - l + 1));
	v.pb(Event(r, -1, c, r - l + 1));
    }
    
    sort(v.begin(), v.end());
    
    lli ans = INF;
    for (int i = 0; i < v.size(); i++) {
	if (v[i].type == 1) {
	    if (x - v[i].duration < 0) continue;
	    if (best[x - v[i].duration] != INF)
		ans = min(ans, best[x - v[i].duration] + v[i].cost);
	} else {
	    best[v[i].duration] = min(best[v[i].duration], v[i].cost);
	}
    }


    if (ans != INF)
	cout << ans << "\n";
    else
	cout << "-1\n";

    return 0;
}
