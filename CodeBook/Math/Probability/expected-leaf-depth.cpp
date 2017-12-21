/*
    Codeforces. Round 428. Div. 2. Problem C
    When the horse reaches a city (including the first one), it goes to one of
    the cities connected to the current city. But it is a strange horse, it only
    goes to cities in which they weren't before. In each such city, the horse
    goes with equal probabilities and it stops when there are no such cities.

    Let the length of each road be 1. The journey starts in the city 1. What is
    the expected length (expected value of length) of their journey?
*/

#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

void print_time(const clock_t& begin) {
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elapsed time: ";
    cerr << fixed << setprecision(4) << elapsed_secs << "\n";
}

const int INF = 1e9;
const int MAX = 100005;

double prob[MAX];
int depth[MAX];
bool leaf[MAX];
VI path[MAX];

void dfs(int node, int par) {
    depth[node] = depth[par] + 1;
    if (path[node].size() == 1) leaf[node] = true;
    for (int adj : path[node]) {
        if (adj == par) continue;
        prob[adj] = prob[node] * (1.0 / (path[node].size() - 1));

        dfs(adj, node);
    }
}

void solve_single() {
    int N; cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        path[a].pb(b);
        path[b].pb(a);
    }

    depth[1] = 0;
    prob[1] = 1;
    for (int adj : path[1]) {
        prob[adj] = 1.0 / path[1].size();
        dfs(adj, 1);
    }

    double ans = 0;
    for (int i = 1; i <= N; i++) {
        if (leaf[i]) {
            ans += prob[i] * depth[i];
        }
    }
    cout << fixed << setprecision(8) << ans << "\n";
}

int main() {
#ifdef TIMP
    clock_t start_time = clock();
#endif
    io;

    solve_single();

#ifdef TIMP
    print_time(start_time);
#endif
    return 0;
}
