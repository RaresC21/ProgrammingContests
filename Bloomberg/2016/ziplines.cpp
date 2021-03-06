/* 
   /home/rares/ProgrammingContests/Bloomberg/2016/
   ziplines.cpp
*/

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

const int MAX = 101;
int a[MAX];
int best[MAX];
int N;

int dfs(int pos) {
    if (best[pos] != -1) return best[pos];
    int res = 0;
    if (pos - 1 >= 0 && a[pos] > a[pos - 1])
	res = max(res, dfs(pos - 1));
    if (pos - 2 >= 0 && a[pos] > a[pos - 2])
	res = max(res, dfs(pos - 2));
    if (pos + 1 < N && a[pos] > a[pos + 1])
	res = max(res, dfs(pos + 1));
    if (pos + 2 < N && a[pos] > a[pos + 2])
	res = max(res, dfs(pos + 2));
    return best[pos] = res + 1;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N;
    FOR(i,0,N) {
	cin >> a[i];
    }
    memset(best, -1, sizeof(best));
    
    int ans = 0;
    FOR(i,0,N) {
	ans = max(ans, dfs(i));
    }
    cout << ans - 1 << "\n";
    
    return 0;
}
