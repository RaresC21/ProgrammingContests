#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 1000006
#define INF 1000000000000000009

struct Node {
    int cost, res, last, dist, n;
    Node(int cost, int res, int l, int dist, int num) : cost(cost), res(res), last(l), dist(dist), n(num) {}
};

int resource[MAX];
bool met[MAX];
int par[MAX];

int main() {

    set<pair<int, int> > costs;
    queue<Node> q;

    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        int cost, res; cin >> cost >> res;
        if (cost <= 1) {
            q.push(Node(cost, res, -1, 1, i));
        }
        resource[i] = res;
        costs.insert(mp(cost, i));
    }

    while (q.size()) {
        int cost = q.front().cost;
        int res = q.front().res;
        int last = q.front().last;
        int dist = q.front().dist;
        int n = q.front().n;
        q.pop();

        if (met[n]) continue;
        met[n] = true;
        par[n] = last;

        if (n == N) {
            cout << dist << "\n";
            vector<int> ans;
            while (n != -1) {
                ans.pb(n);
                n = par[n];
            }
            for (int i = dist - 1; i >= 0; i--)
                cout << ans[i] << " ";
            cout << "\n";
            return 0;
        }

        vector<pair<int, int> > bad;
        for (auto it = costs.begin(); it != costs.end(); ++it) {
            if (it->first > res) break;
            q.push(Node(it->first, resource[it->second], n, dist + 1, it->second));
            bad.pb(*it);
        }

        for (int i = 0; i < bad.size(); i++)
            costs.erase(bad[i]);
    }

    cout << "No such luck\n";

    return 0;
}
