/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   D.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 4600
int N, M;
map<int, bool> is_target;
map<string, int> conv;
int cost[MAX][MAX];
int depth[MAX];
int met[MAX];
int parent[MAX];
vector<int> path[MAX];

void bfs() {
    int start_ = conv["English"];
    queue<pair<int, int> > q;
    q.push(mp(start_, 0));
    while (q.size()) {
	pair<int, int> cur = q.front();
	q.pop();

	if (met[cur.first]) continue;
	met[cur.first] = true;
	depth[cur.first] = cur.second;
	
	for (int adj : path[cur.first]) {
	    q.push(mp(adj, cur.second + 1));
	}
    }
}

int dist[MAX];

int solve() {
    int ans = 0;
    int amnt = 0;
    int start_ = conv["English"];
    dist[start_] = 0;
    
    
    for (int d = 1; d < MAX; d++) {
	for (int i = 1; i < MAX; i++) {
	    if (depth[i] != d) continue;
	    
	    for (int adj : path[i]) {
		if (depth[adj] == d - 1) {
		    if (dist[i] == 0) {
			dist[i] = dist[adj] + cost[adj][i];
		    } else if (dist[i] > dist[adj] + cost[adj][i]) {
			dist[i] = dist[adj] + cost[adj][i];
		    }
		}
	    }
	    if (is_target[i] && depth[i] == d) {
		amnt++;
		ans += dist[i];
		dist[i] = 0;
	    }
	}
    }
    if (amnt != N) return -1;
    return ans;
}

int main() {
    
    cin >> N >> M;
    int cnt = 1;
    for (int i = 0; i < N; i++) {
	string s; cin >> s;
	conv[s] = cnt++;
	is_target[conv[s]] = true;
    }
    
    for (int i = 0; i < M; i++) {
	string a, b; cin >> a >> b;
	int c; cin >> c;
	
	if (conv.count(a) == 0) conv[a] = cnt++;
	if (conv.count(b) == 0) conv[b] = cnt++;
	int aa = conv[a];
	int bb = conv[b];

	path[aa].pb(bb);
	path[bb].pb(aa);
	cost[aa][bb] = cost[bb][aa] = c;
    }

    bfs();
    
    int ans = solve();
    if (ans == -1) {
	cout << "Impossible\n";
    } else {
	cout << ans << "\n";
    }
    
    return 0;
}
