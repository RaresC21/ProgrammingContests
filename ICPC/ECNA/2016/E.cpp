/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   E.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int find_it(const string& s, const string& cur) {
    int amnt = 0;
    for (int i = 0; i < s.size(); i++) {
	if (i + cur.size() - 1 >= s.size()) break;
	int k = 0;
	for (; k < cur.size(); k++) {
	    if (cur[k] != s[i + k]) break;
	}
	if (k == cur.size()) {
	    amnt++;
	    i += k - 1;
	}
    }
    return amnt;
}

int main() {
    
    string s; cin >> s;
    int N = s.size();
    int ans = N;
    for (int i = 0; i < N; i++) {
	string cur = "";
	for (int k = i; k < N; k++) {
	    cur = cur + s[k];
	    int amnt = find_it(s, cur);
	    int len = k - i + 1;

	    int use = len + (N - amnt * (len - 1));
	    ans = min(ans, use);
	}
    }

    cout << ans << "\n";
    
    return 0;
}
