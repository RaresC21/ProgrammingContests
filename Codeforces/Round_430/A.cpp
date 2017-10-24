/* 
   /home/rares/ProgrammingContests/Codeforces/Round_420/
   A.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {
    
    lli l, r, x, y, k;
    
    cin >> l >> r >> x >> y >> k;
    int start_ = (l + k - 1) / k;
    for (int i = k * start_; i <= r; i += k) {
        int want = i / k;
    	if (want >= x && want <= y) {
    	    cout << "YES\n";
    	    return 0;
    	}
    }

    cout << "NO\n";
    
    return 0;
}