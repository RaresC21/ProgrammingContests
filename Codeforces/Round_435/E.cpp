/* 
   /home/rares/ProgrammingContests/Codeforces/Round_435/
   E.cpp
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

VLL	 cand;

LL solve(LL goal) {
    int indx = 0;
    int minim = 0, maxim = SZ(cand) - 1;
    while (minim <= maxim) {
    	int mid = (minim + maxim) / 2;
    	if (cand[mid] <= goal) {
    		minim = mid + 1;
    		indx = max(indx, mid);
    	} else {
    		maxim = mid - 1;
    	}
    }

    LL ans = abs(cand[indx++] - goal);
   	if (indx < SZ(cand))
    	ans = min(ans, cand[indx] - goal);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    int N, M, Q; cin >> N >> M >> Q;
    LL a_sum = 0, s = 1;
    FOR(i,0,N) {
    	int x; cin >> x;
    	a_sum += s * x;
    	s = -s;
    }

    VLL b(M);
    FOR(i,0,M) {
    	cin >> b[i];
    }

    LL cur = 0;
    s = 1;
    FOR(i,0,N) {
		cur += s * b[i];
		s = -s;
	}

	s = (N % 2) == 1 ? 1 : -1;
    cand.push_back(cur);
    FOR(i,N,M) {
    	cur -= b[i-N];
		cur = -cur;
    	cur += b[i] * s;
		cand.push_back(cur);
    }

	sort(cand.begin(), cand.end());

    cout << solve(a_sum) << "\n";
    FOR(q,0,Q) {
    	int l, r, x; cin >> l >> r >> x;
    	int amnt = r - l + 1;
    	if (amnt % 2 == 1) {
    		if (r % 2 == 0) a_sum -= x;
    		else a_sum += x;
    	}

    	LL ans = solve(a_sum);
    	cout << ans << "\n";
    }

    return 0;
}
