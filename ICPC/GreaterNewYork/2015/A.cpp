/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   A.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {
    
    int T; cin >> T;
    while (T--) {
	int t; cin >> t;
	int N; cin >> N;
	lli s1 = N * (N + 1) / 2;
	lli s2 = N * N;
	lli s3 = 2 * s1;

	cout << t << " " << s1 << " " << s2 << " " << s3 << "\n";
    }
    
    return 0;
}
