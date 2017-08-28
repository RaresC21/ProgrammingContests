 #include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 100005
#define INF 100000000000000009
#define int lli

vector<int> source;

struct Node {
    int root, n;
    int dist;
    Node (int root, int n, int dist) : root(root), n(n), dist(dist) {}
    bool operator < (const Node& other) const {
        return dist > other.dist;
    }
};

vector<pair<int, int> > path[MAX];
int d[MAX], par[MAX];
bool met[MAX];

void dijkstra() {
    priority_queue<Node> q;
    for (int i = 1; i <= MAX; i++)
    	d[i] = INF;
    for (int s : source) {
        q.push(Node(s, s, 0));
    }

    while (q.size()) {
        int root = q.top().root;
        int n = q.top().n;
        int dist = q.top().dist;
        q.pop();

        if (met[n]) continue;
        met[n] = true;
        par[n] = root;
        d[n] = dist;

        for (auto adj : path[n]) {
        	if (met[adj.first]) continue;
            q.push(Node(root, adj.first, dist + adj.second));
        }
    }
}

#undef int
int main() {
#define int lli

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int t; cin >> t;
        if (t) source.pb(i);
    }

    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        path[a].pb(mp(b, c));
        path[b].pb(mp(a, c));
    }

    dijkstra();

    int best = INF;
    pair<int, int> ans = {-1, -1};
    for (int i = 1; i <= N; i++) {
        for (auto adj : path[i]) {
            if (par[i] != par[adj.first]) {
                if (best > d[i] + d[adj.first] + adj.second) {
                    best = d[i] + d[adj.first] + adj.second;
                    ans = mp(par[i], par[adj.first]);
                }
            }
        }
    }

    if (ans.first == -1) {
         cout << "No luck at all\n";
    } else {
        cout << best << "\n";
        cout << ans.first << " " << ans.second << "\n";
	}


    return 0;
}

