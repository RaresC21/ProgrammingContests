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

int N, M, P;
const int MAX = 1003;
const int INF = 1000000009;
bool bad[MAX];
vector<pii> path[MAX];
bool met[MAX];
int dist[MAX][MAX];

struct Node {
    int n, d;
    int par;
    Node (int n, int d, int p) : n(n), d(d), par(p) {}
    bool operator < (const Node& other) const {
        return d > other.d;
    }
};

int prim(int source) {
    priority_queue<Node> q;
    int cost = 0;
    int amnt = 0;
    q.push(Node(source, 0, source));
    while (!q.empty()) {
        Node cur = q.top();
        q.pop();

        if (met[cur.n]) continue;
        met[cur.n] = true;
        cost += dist[cur.n][cur.par];
        amnt++;

        for (auto adj : path[cur.n]) {
            if (bad[adj.A]) continue;
            q.push(Node(adj.A, adj.B, cur.n));
        }
    }
    if (amnt != N - P) return INF;
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> P;

    if (N == 1 && P == 1) {
        cout << "0\n";
        return 0;
    }

    FOR(i,0,P) {
        int x; cin >> x;
        bad[x] = true;
    }

    FOR(i,0,M) {
        int a, b, c; cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = c;
        path[a].push_back(MP(b, c));
        path[b].push_back(MP(a, c));
    }

    if (N == 2 && P == 2) {
        cout << dist[1][2] << "\n";
        return 0;
    }

    int cost = 0;
    FOR(i,1,N+1) {
        if (!bad[i]) {
            cost = prim(i);
            break;
        }
    }

    if (cost == INF) {
        cout << "impossible\n";
        return 0;
    }

    FOR(i,1,N+1) {
        if (bad[i]) {
            int best = INF;
            for (auto adj : path[i]) {
                if (!bad[adj.A]) best = min(best, adj.B);
            }
            if (best == INF) {
                cout << "impossible\n";
                return 0;
            }
            cost += best;
        }
    }

    cout << cost << "\n";

    return 0;
}