/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   E.cpp
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

	lli p; cin >> p;
	char slash; cin >> slash;
	lli q; cin >> q;

	vector<char> dir;
	while (!(p == 1 && q == 1)) {
	    if (p < q) {
		dir.pb('L');
		q -= p;
	    } else {
		dir.pb('R');
		p -= q;
	    }
	}

	lli num = 1;
	for (int i = dir.size() - 1; i >= 0; i--) {
	    char c = dir[i];
	    if (c == 'L') num *= 2;
	    else num = (num * 2) + 1;
	}

	cout << t << " " << num << "\n";
    }
    
    
    return 0;
}
