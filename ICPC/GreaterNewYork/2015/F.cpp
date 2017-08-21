/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   F.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 1000

int main() {
    
    int T; cin >> T;
    while (T--) {
	vector<int> rev_r[MAX], rev_g[MAX];
	
	int t; cin >> t;
	int N; cin >> N;
	for (int i = 0; i <  N; i++) {
	    int r; cin >> r;
	    rev_r[r].pb(i);
	}
	for (int i = 0; i < N; i++) {
	    int g; cin >> g;
	    rev_g[g].pb(i);
	}

	cout << t << " ";
	
	bool good = false;
	queue<pair<int, int> > q;
	vector<vector<bool> > found (N, vector<bool>(N, 0));

	for (int a = 0; a < N; a++) {
	    q.push(mp(a, a));
	}

	int amnt = 0;
	while (q.size()) {
	    int x = q.front().first;
	    int y = q.front().second;
	    q.pop();
	    
	    if (found[x][y]) continue;
	    found[x][y] = true;
	    amnt++;
	    
	    // move with green light
	    for (int i : rev_g[x])
		for (int k : rev_g[y])
		    q.push(mp(i, k));
	    
	    // move with red
	    for (int i : rev_r[x])
		for (int k : rev_r[y])
		    q.push(mp(i, k));
	}

	if (amnt == N * N) {
	    good = true;
	    cout << "YES\n";
	}
    
	if (!good)
	    cout << "NO\n";
    }
    
    return 0;
}
