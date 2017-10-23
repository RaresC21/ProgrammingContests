/* 
   /home/rares/ProgrammingContests/Codeforces/MemSQL/2017/Round2/
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

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    priority_queue<int> available;
    
    long long ans = 0;
    FOR(i,0,N) {
	int val; cin >> val;
	if (!available.empty()) {
	    int best = -available.top();
	    if (best < val) {
		ans += val - best;
		available.pop();
		// we can change our minds later on, and cancel out selling it
		// if we buy it back and sell something even better later. 
		available.push(-val);
	    }
	}
	available.push(-val);
    }

    cout << ans << "\n";
    
    return 0;
}
