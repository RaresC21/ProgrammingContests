#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    int T; cin >> T;
    while (T--) {
	string s; cin >> s;

	int len = 1;
	int up = 0, down = 0;
	for (int i = 1; i < s.size(); i++) {
	    if (s[i] == s[i - 1])
		len++;
	    else {
		if (s[i - 1] == 'U') up++;
		else down++;
		len = 1;
	    }
	}
	if (s[s.size() - 1] == 'U')
	    up++;
	else down++;
	
	cout << min(up, down) << "\n";
    }
    
    return 0;
}
