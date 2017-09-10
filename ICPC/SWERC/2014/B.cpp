#include <bits/stdc++.h>
using namespace std;

const int MAX = 100005;
vector<pair<int, int> > path[MAX];

struct Node {
    int n;
    int d;
    Node (int n, int d) : n(n), d(d) {}
    bool operator < (const Node& other) const {
        return d > other.d;
    }
};

void dijktra(int source, vector<int>& dist) {
    vector<bool> met(dist.size());
    priority_queue<Node> q;
    q.push(Node(source, 0));
    while (q.size()) {
        Node cur = q.top();
        q.pop();

        if (met[cur.n]) continue;
        dist[cur.n] = cur.d;
        met[cur.n] = true;

        for (auto adj : path[cur.n]) {
            q.push(Node(adj.first, adj.second + cur.d));
        }
    }
}

int main() {

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        path[a].push_back(make_pair(b, c));
        path[b].push_back(make_pair(a, c));
    }

    vector<int> to(N), from(N);
    dijktra(0, to);
    dijktra(N - 1, from);

    to[0] = 0;
    from[N - 1] = 0;

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (auto adj : path[i]) {
            if (to[i] + from[adj.first] + adj.second == to[N - 1]) {
                ans += adj.second;
            }
        }
    }


    cout << ans * 2 << "\n";

    return 0;
}
