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

const int MAX = 300;
int fac[MAX], client[MAX];
bool met[MAX];
VI path[MAX];

void dfs(int node) {
    if (met[node]) return;
    met[node] = true;
    for (int adj : path[node])
    dfs(adj);
}

int main() {
    ios_base::sync_with_stdio(false);

    int M, N, K; cin >> M >> N >> K;

    int cnt = 0;
    FOR(i,0,M) {
        fac[i] = cnt++;
    }
    FOR(i,0,N) {
        client[i] = cnt++;
    }

    FOR(i,0,M) {
        FOR(k,0,N) {
            int c; cin >> c;
            if (c == 0) {
                path[fac[i]].push_back(client[k]);
                path[client[k]].push_back(fac[i]);
            }
        }
    }

    int amnt = 0;
    FOR(i,0,N) {
        int k = client[i];
        if (met[k]) continue;
        if (path[k].size() == 0) {
            cout << "no\n";
            return 0;
        }
        amnt++;
        dfs(k);
    }

    if (amnt <= K) {
        cout << "yes\n";
    } else {
        cout << "no\n";
    }

    return 0;
}