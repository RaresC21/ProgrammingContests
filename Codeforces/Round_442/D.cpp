/* 
   /home/rares/ProgrammingContests/Codeforces/Round_442/
   D.cpp
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

const int MAX = 1003;
int N, M, K;
char grid[MAX][MAX];
set<int> av_row[MAX], av_col[MAX];
bool met[MAX][MAX];

int main() {
    //ios_base::sync_with_stdio(false);
    clock_t begin = clock();

    /*
    N = 1000, M = 1000, K = 1;
    FOR(i,0,M-1) cout << '.';
    cout << "#\n";
    FOR(i,0,N-1) {
	FOR(k,0,M) cout << '.';
	cout << "\n";
    }
    return 0;
    */
    scanf("%d%d%d", &N, &M, &K);
    FOR(i,0,N) {
	scanf("%s", grid[i]);
	FOR(k,0,M) {
	    //grid[i][k] = s[k];
	    av_row[i].insert(k);
	    av_col[k].insert(i);
	}
    }

    pii start, finish;
    cin >> start.A >> start.B >> finish.A >> finish.B;
    start.A--, start.B--;
    finish.A--, finish.B--;

    queue<pair<pii, int> > q;
    q.push(MP(start, 0));
    while (!q.empty()) {
	auto cur = q.front();
	pii pos = cur.A;
	int dist  = cur.B;
	q.pop();

	//if (met[pos.A][pos.B]) continue;
	//met[pos.A][pos.B] = true;
	if (pos == finish) {
	    cout << dist << "\n";
	    return 0;
	}


	if (SZ(av_row[pos.A])) {
	    while (true) {
		auto it = av_row[pos.A].lower_bound(pos.B);
		if (it == av_row[pos.A].end()) break;
		if (grid[pos.A][*it] == '#') break;
		if (*it - pos.B > K) break;

		q.push(MP(MP(pos.A, *it), dist+1));
		av_row[pos.A].erase(*it);
		av_col[*it].erase(pos.A);
	    }
	    
	    while (true) {
		auto it = av_row[pos.A].lower_bound(pos.B);
		if (it == av_row[pos.A].begin()) break;
		--it;		
		if (grid[pos.A][*it] == '#') break;
		if (abs(*it - pos.B) > K) break;
		
		q.push(MP(MP(pos.A, *it), dist+1));
		av_row[pos.A].erase(*it);
		av_col[*it].erase(pos.A);
	    }	    
	}

	if (SZ(av_col[pos.B])) {
	    while (true) {
		auto it = av_col[pos.B].lower_bound(pos.A);
		if (it == av_col[pos.B].end()) break;
		if (grid[*it][pos.B] == '#') break;
		if (*it - pos.A > K) break;

		q.push(MP(MP(*it, pos.B), dist+1));
		av_col[pos.B].erase(*it);
		av_row[*it].erase(pos.B);
	    }

	    while (true) {
		auto it = av_col[pos.B].lower_bound(pos.A);
		if (it == av_col[pos.B].begin()) break;
		--it;
		if (grid[*it][pos.B] == '#') break;
		if (abs(*it - pos.A) > K) break;

		q.push(MP(MP(*it, pos.B), dist+1));
		av_col[pos.B].erase(*it);
		av_row[*it].erase(pos.B);
	    }
	}
    }

    cout << "-1\n";

    return 0;
}
