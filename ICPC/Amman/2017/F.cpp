
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
map<int, queue<int> > next_;
int val[MAX];

int main() {
	ios_base::sync_with_stdio(false);

	int T; cin >> T;
	while (T--) {
		int N, K; cin >> N >> K;

		next_.clear();
		for (int i = 0; i < N; i++) {
			cin >> val[i];
			next_[val[i]].push(i);
		}
		FOR(i,0,N) {
			next_[val[i]].push(INF);
			next_[val[i]].push(INF);
		}

		priority_queue<PII> cur;
		set<int> have;
		int ans = 0;
		for (int i = 0; i < N; i++) {
			if (have.count(val[i])) {
				
			} else if (SZ(have) >= K) {
				auto a = cur.top();
				cur.pop();
				have.erase(a.second);
				ans++;
			} else {
				ans++;
			}
			have.insert(val[i]);
			next_[val[i]].pop();
			cur.push(MP(next_[val[i]].front(), val[i]));
		}
		cout << ans << "\n";
	}

	return 0;
}