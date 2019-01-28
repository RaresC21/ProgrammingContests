/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   B.cpp
*/

/*
  Just try all possible 6 digit numbers. complexity is 10^N but N = 6, so it's OK.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int ans = 10;
string original;

void solve(int pos, string s, int changes) {
    if (pos == 6) {
	int a = 0, b = 0;
	for (int i = 0; i < 3; i++)
	    a += s[i] - '0';
	for (int i = 3; i < 6; i++)
	    b += s[i] - '0';

	if (a == b)
	    ans = min(ans, changes);
	return;
    }

    for (char i = '0'; i <= '9'; i++) {
	if (original[pos] != i)
	    solve(pos + 1, s + i, changes + 1);
	else
	    solve(pos + 1, s + i, changes);
    }
}

int main() {
    
    cin >> original;
    solve(0, "", 0);

    cout << ans << "\n";
    
    return 0;
}
