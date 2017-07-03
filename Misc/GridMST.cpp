#include <bits/stdc++.h>
using namespace std;

struct PT {
    int x, y;
    int i;
    PT () {}
    PT (int x, int y, int i) : x(x), y(y), i(i) {}
};

#define pb push_back
#define SZ 1001
#define MAX 100005
int N;
PT pts[MAX];
vector<int> path[MAX];
int met[SZ][SZ];
map<pair<int, int>, bool> edge;
bool intree[MAX];

struct Node {
    int n;
    int dist;
    Node (int n, int dist) : n(n), dist(dist) {}
    bool operator < (const Node &other) const {
        return dist > other.dist;
    }
};

int dist(int a, int b) {
    int dx = abs(pts[a].x - pts[b].x);
    int dy = abs(pts[a].y - pts[b].y);
    return dx + dy;
}

int prim(int source) {

    memset(intree, 0, sizeof(intree));
    int tree_size = 0;
    int tree_cost = 0;

    priority_queue<Node> q;
    q.push(Node(source, 0));

    while (q.size()) {
        Node p = q.top();
        q.pop();

        if (intree[p.n]) continue;
        intree[p.n] = true;

        tree_size ++;
        tree_cost += p.dist;

        for (int i = 0; i < path[p.n].size(); i++) {
            int cur_node = path[p.n][i];
            if (intree[cur_node]) continue;
            q.push(Node(cur_node, dist(p.n, cur_node)));
        }
    }
    return tree_cost;
}

int main() {

    memset(met, -1, sizeof(met));

    cin >> N;
    queue<PT> q;
    for (int i = 0; i < N; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].i = i;
        q.push(pts[i]);
    }

    while (!q.empty()) {
        PT cur = q.front();
        q.pop();

        if (met[cur.x][cur.y] != -1) {
            if (cur.i != met[cur.x][cur.y] && !edge.count(make_pair(cur.i, met[cur.x][cur.y]))) {
                edge[make_pair(cur.i, met[cur.x][cur.y])] = edge[make_pair(met[cur.x][cur.y], cur.i)] = true;
                path[cur.i].pb(met[cur.x][cur.y]);
                path[met[cur.x][cur.y]].pb(cur.i);
            }
            continue;
        }
        met[cur.x][cur.y] = cur.i;

        if (cur.y + 1 < SZ) q.push(PT(cur.x, cur.y + 1, cur.i));
        if (cur.y - 1 >= 0) q.push(PT(cur.x, cur.y - 1, cur.i));
        if (cur.x - 1 >= 0) q.push(PT(cur.x - 1, cur.y, cur.i));
        if (cur.x + 1 < SZ) q.push(PT(cur.x + 1, cur.y, cur.i));
    }

    cout << prim(0) << "\n";

    return 0;
}