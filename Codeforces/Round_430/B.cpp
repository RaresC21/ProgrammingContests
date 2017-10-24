/* 
   /home/rares/ProgrammingContests/Codeforces/Round_420/
   B.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

double dist(int x, int y) {
    return x*x + y*y;
}

int main() {
    
    int R, D; cin >> R >> D;
    int inner = R - D;

    int N; cin >> N;
    int ans = 0;
    for (int i = 0; i < N; i++) {
    	int r, x, y; cin >> x >> y >> r;
    	double d = sqrt(dist(x, y));
    	if (d >= inner + r && R >= d + r) {
    	    ans++;
    	}
    }

    cout << ans << "\n";
    
    return 0;
}