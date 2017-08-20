/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   B.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

lli binomialCo(int N, int r) {
    lli res = 1;
    r=(r<(N-r))?r:(N-r);
    for(int i = 1; i <= r; i++, N--) {
        res *= N;
        res /= i;
    }
    return res;
}


int main() {
    
    int T; cin >> T;
    while (T--) {
	int t; cin >> t;
	int N; cin >> N;

	lli ans = 0;
	for (int k = 1; k <= N / 2; k++) {
	    int single = (N - 4 * k) / 2;
	    if (k < single || single < 0) continue;

	    int steps = k + single;
	    lli cur = binomialCo(steps, k);
	    ans += cur * cur;
	}

	cout << t << " " << ans << "\n";
    }
    
    return 0;
}
