#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> pii;
typedef pair<LL, LL> PLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
#define A first
#define B second

const int INF = 1000000009;
const int MAX = 1003;
int N, E, X, Y, M;
VI path[MAX];
bool good[MAX];
int cost[MAX][MAX];
int dist[MAX][MAX][2];
vector<pair<int, int> > edge;

struct Node {
    int n;
    int d;
    int edges;
    bool use_black;
    Node(int n, int d, int e, bool u) : n(n), d(d), edges(e), use_black(u) {}
    inline bool operator < (const Node& other) const {
        return d > other.d;
    }
};

void dijkstra(int source) {
    priority_queue<pair<int, pair<int, pair<int, bool> > > > q;
    q.push(MP(source, MP(0, MP(0, true))));

    int cnt = 0;
    while (!q.empty()) {
        auto p = q.top();
        q.pop();

        if (p.edges == N) continue;
        if (dist[p.n][p.edges][p.use_black] != -1)
            continue;
        dist[p.n][p.edges][p.use_black] = p.d;

        for (int adj : path[p.n]) {
            if (good[adj]) {
                if (dist[adj][p.edges + 1][p.use_black] == -1)
                    q.push(Node(adj, p.d + cost[p.n][adj], p.edges + 1, p.use_black));
            } else
                if (dist[adj][p.edges + 1][0] == -1)
                    q.push(Node(adj, p.d + cost[p.n][adj], p.edges + 1, false));
        }
    }
}

int lower_bound_ = -1, upper_bound_ = INF;
bool impossible = false;
void calc(int e, int i) {
    int A = dist[Y][e][1];
    int B = dist[Y][i][0];

    if (e == i) {
        if (A >= B)
            impossible = true;
    } else if (e < i) {
        int cur = (A - B) / (i - e);
        if ((A - B) % (i - e) == 0) cur++;
        lower_bound_ = max(lower_bound_, cur);
    } else {
        int cur = (B - A) / (e - i);
        if ((B - A) % (e - i) == 0) cur--;
        upper_bound_ = min(upper_bound_, cur);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> E >> X >> Y;
    FOR(i,0,E) {
        int a, b, c; cin >> a >> b >> c;
        edge.push_back(MP(a, b));
        path[a].push_back(b);
        path[b].push_back(a);
        cost[a][b] = cost[b][a] = c;
    }

    cin >> M;
    FOR(i,0,M) {
        int x; cin >> x;
        good[x] = true;
    }

    memset(dist, -1, sizeof(dist));
    dijkstra(X);

    int BLACK = -1, WHITE = -1;
    FOR(i,1,N+1) {
        if (good[i] && BLACK == -1 && dist[Y][i][1] != -1)
            BLACK = i;
        if (WHITE == -1 && dist[Y][i][0] != -1)
            WHITE = i;
    }

    if (BLACK == WHITE && dist[Y][BLACK][1] < dist[Y][WHITE][0]) {
        cout << "Infinity\n";
        return 0;
    }

    int ans = -1;
    FOR(e,1,N) {
        if (dist[Y][e][1] == -1) continue;

        lower_bound_ = -1;
        upper_bound_ = INF;
        impossible = false;
        FOR(i,1,N) {
            if (dist[Y][i][0] == -1) continue;
            calc(e, i);
        }
        if (lower_bound_ > upper_bound_) impossible = true;
        if (impossible) continue;

        ans = max(ans, upper_bound_);
    }

    if (ans == INF) {
        cout << "Infinity\n";
    } else if (ans > -1) {
        cout << ans << "\n";
    } else {
        cout << "Impossible\n";
    }
    return 0;
}