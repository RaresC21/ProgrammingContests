/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   E.cpp
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

const int MAX = 20;
map<VI, bool> met;

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};
char grid[MAX][MAX];
queue<pair<VI, int> > q;

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    int W, H; cin >> W >> H;
    int L; cin >> L;

    int target = -1;
    vector<int> pos(N);
    int cnt = 1;
    FOR(i,0,H) {
	string s; cin >> s;
	FOR(k,0,W) {
	    grid[i][k] = s[k];
	    if (grid[i][k] == 'X') {
		target = i * 10 + k;
		grid[i][k] = '.';
	    } else if (grid[i][k] != '.') {
		if (grid[i][k] == '1') {
		    pos[0] = i * 10 + k;
		    grid[i][k] = '.';
		}
		else if (grid[i][k] != 'W') {
		    pos[cnt++] = i * 10 + k;
		    grid[i][k] = '.';
		}
	    }
	}
    }

    sort(pos.begin() + 1, pos.end());
    q.push(MP(pos, 0));

    while (q.size()) {
	auto cur = q.front();
        VI p = cur.first;
	int dist = cur.second;
	q.pop();

	if (dist > L) continue;

	if (p[0] == target) {
	    cout << dist << "\n";
	    return 0;
	}

	FOR(i, 0, H) {
	    FOR(k, 0, W) {
		if (grid[i][k] != 'W') grid[i][k] = '.';
	    }
	}
	for(int val : p) {
	    int i = val / 10;
	    int k = val % 10;
	    grid[i][k] = 'P';
	}
	    
	FOR(j, 0, N) {
	    FOR(d, 0, 4) {
		int i = p[j] / 10, k = p[j] % 10;
		while (i + dr[d] >= 0 && i + dr[d] < H &&
		       k + dc[d] >= 0 && k + dc[d] < W &&
		       grid[i + dr[d]][k + dc[d]] == '.')
		    i += dr[d], k += dc[d];
		VI nxt = p;
		nxt[j] = i * 10 + k;
		sort(nxt.begin() + 1, nxt.end());
		if (!met[nxt]) {
		    met[nxt] = true;
		    q.push(MP(nxt, dist + 1));
		}
	    }
	}
    }
	
    cout << "NO SOLUTION\n";
	    
    return 0;
}
