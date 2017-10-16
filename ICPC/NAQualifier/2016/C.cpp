#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

#define INF 1000000
#define pb push_back
#define MAX 101
VI path[MAX];
int gain[MAX];
int weight[MAX][MAX], dist[MAX][MAX];
int total[MAX][MAX], carry[MAX][MAX];

int main() {

    int N; cin >> N;
    FOR(i,1,N+1) {
        cin >> gain[i];
    }
    FOR(i,1,N+1) {
        FOR(k,1,N+1) {
            dist[i][k] = INF;
            carry[i][k] = INF;
        }
    }

    int M; cin >> M;
    FOR(i,0,M) {
        int a, b, c; cin >> a >> b >> c;
        path[a].pb(b);
        path[b].pb(a);
        dist[a][b] = dist[b][a] = c;
        carry[a][b] = carry[b][a] = gain[b] + gain[a];
    }

    FOR(k,1,N+1) {
        FOR(i,1,N+1) {
            FOR(j,1,N+1) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    carry[i][j] = carry[i][k] + carry[k][j];
                }
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    carry[i][j] = max(carry[i][j], carry[i][k] + carry[k][j]);
                }
            }
        }
    }

    if (dist[1][N] < INF) {
        cout << dist[1][N] << " " << (carry[1][N] + gain[1] + gain[N]) / 2;
        cout << "\n";
    }
    else cout << "impossible\n";

    return 0;
}