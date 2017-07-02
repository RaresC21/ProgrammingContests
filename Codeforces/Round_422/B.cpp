#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    int N, M; cin >> N >> M;
    string s, t; cin >> s >> t;

    int ans = 10000000;
    vector<int> moves;
    for (int i = 0; i < t.size() - s.size() + 1; i++) {
	bool same = true;
	int amnt = 0;
	vector<int> cur_v;
	for (int k = 0; k < s.size(); k++) {
	    int cur = i + k;
	    if (t[cur] == s[k]) continue;
	    else if (s[k] == '?') continue;
	    else {
		cur_v.pb(k);
		amnt++;
	    }
	}
	if (amnt < ans) {
	    ans = amnt;
	    moves = cur_v;
	}
    }

    cout << ans << "\n";
    for (int v : moves) {
	cout << v + 1 << " ";
    }
    cout << "\n";

    return 0;
}
