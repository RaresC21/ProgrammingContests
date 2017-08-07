/* 
   /home/rares/ProgrammingContests/Hackerrank/openbracket/2017/
   B.cpp
*/

#include <iostream>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int amnt[40];

int main() {
    
    string s; cin >> s;
    int K; cin >> K;
    for (int i = 0; i < s.size(); i++) {
	amnt[s[i] - 'a']++;
    }

    string ans = "";
    int pos = 0;
    int last = 0;
    int cnt = 0;
    while (pos < s.size() && cnt < 100) {
	for (int i = 25; i >= 0; i--) {
	    if (amnt[i] >= K) {
		for (; pos < s.size(); pos++) {
		    if (s[pos] - 'a' == i) {
			ans = ans + s[pos];
			last = pos;
		    }
		    amnt[s[pos] - 'a']--;
		}
		pos = last + 1;
		for (int k = s.size() - 1; k >= pos; k--)
		    amnt[s[k] - 'a']++;
	    }
	}
	cnt++;
    }

    cout << ans << "\n";
    
    return 0;
}
