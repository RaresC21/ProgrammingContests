#include "bits/stdc++.h"
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

const int MAX = 200005;
const int INF = 1000000009;

bool cmp(PII a, PII b) {
    if (a.second == b.second) {
	return a.first < b.first;
    }
    return a.second > b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    
    int N; cin >> N;
    int t = 0;
    while (N != 0) {
	t++;
	vector<PII> v;
	FOR(i,0,N) {
	    int a, b; cin >> a >> b;
	    v.push_back(MP(a, b));
	}
	
	sort(v.begin(), v.end(), cmp);
	
	int ans = 0;
	int cur = 0;
	FOR(i,0,N) {
	    ans = max(ans, cur + v[i].first + v[i].second);
	    cur += v[i].first;
	}
	
	cout << "Case " << t << ": " << ans << "\n";
	cin >> N;
    }
    
    return 0;
}
