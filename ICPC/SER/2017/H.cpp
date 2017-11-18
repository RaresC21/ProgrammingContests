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
int S, D;
bool met[MAX];
vector<pair<int, pii> > path[MAX];

bool inside(pii a, pii b) {
    return a.A >= b.A && a.B <= b.B;
}

bool possible(int node, pii seg) {
    if (node == D) return true;
    if (met[node]) return false;
    met[node] = true;
    bool can = false;
    for (auto adj : path[node]) {
        if (inside(seg, adj.B)) {
            can |= possible(adj.A, seg);
        }
    }
    return can;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> K;
    cin >> S >> D;
    VI all;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        int x, y; cin >> x >> y;
        all.push_back(x);
        all.push_back(y);
        path[a].push_back(MP(b, MP(x, y)));
    }

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end() );
    int ans = 0;
    for (int i = 0; i < all.size(); i++) {
        int k = i + 1;
        memset(met, 0, sizeof(met));
        if (possible(S, MP(all[i], all[i]))) {
            ans += 1;
        }

        memset(met, 0, sizeof(met));
        if (k != all.size() && possible(S, MP(all[i] + 1, all[k] - 1))) {
            ans += max(0, (all[k] - 1) - (all[i] + 1) + 1);
        }
    }

    cout << ans << "\n";

    return 0;
}
