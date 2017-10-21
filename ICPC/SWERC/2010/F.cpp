/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2010/
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

const int MAX = 22;
VI path[MAX];
int par[1 << MAX];
int action[1 << MAX];
bool met[1 << MAX];
int N, M;

void print() {
    int p = 0;
    int goal = (1 << N) - 1;
    VI ans;
    while (p != goal) {
	ans.push_back(action[p]);
	p = par[p];
    }
    cout << SZ(ans) << ": ";
    reverse(ans.begin(), ans.end());
    for (int a : ans) cout << a << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    while (!(N == 0 && M == 0)) {
	FOR(i,0,N) path[i].clear();
	FOR(i,0,M) {
	    int a, b; cin >> a >> b;
	    path[a].push_back(b);
	    path[b].push_back(a);
	}
	
	int start = (1 << N) - 1;
	queue<int> q;
	q.push(start);
	memset(met, 0, sizeof(met));
	while (!q.empty()) {
	    int state = q.front();
	    q.pop();
	    
	    // try shooting at position i
	    FOR(i,0,MAX) {
		if (state & (1 << i)) {
		    int nxt = 0;
		    FOR(k,0,MAX) {
			if (!(state & (1 << k))) continue;
			if (i == k) continue;
			for (int adj : path[k]) nxt |= (1 << adj);
		    }
		    
		    if (!met[nxt]) {
			met[nxt] = true;
			par[nxt] = state;
			action[nxt] = i;
			
			q.push(nxt);
		    }
		}
	    }
	}
	
	if (met[0]) {
	    print();
	} else {
	    cout << "Impossible\n";
	}

	cin >> N >> M;
    }
    
    return 0;
}
