/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   B.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

vector<pair<string, string> > win;

void add_win(string a, string b) {
    if (a > b) swap(a, b);
    win.pb(mp(a, b));
}

int main() {
    
    int N; cin >> N;
    string wo, bo, wd, bd; cin >> wo >> bo >> wd >> bd;

    queue<string> q;
    for (int i = 4; i < N; i++) {
	string s; cin >> s;
	q.push(s);
    }

    string results; cin >> results;
    for (int i = 0; i < results.size(); i++) {
	if (results[i] == 'W') {
	    swap(wo, wd);
	    add_win(wo, wd);
	    
	    string gone = bd;
	    swap(bo, bd);

	    bo = q.front();
	    q.pop();
	    q.push(gone);
	    
	} else {
	    swap(bo, bd);
	    add_win(bo, bd);
	    
	    string gone = wd;
	    swap(wo, wd);

	    wo = q.front();
	    q.pop();
	    q.push(gone);
	}
    }

    int most = 0;
    vector<pair<string, string> > ans;
    for (int i = 0; i < win.size(); i++) {
	int k = i + 1;
	int amnt = 1;
	while (k < win.size() && win[i] == win[k]) {
	    k++;
	    amnt++;
	}
	i = k - 1;
	if (most < amnt) {
	    most = amnt;
	    ans.clear();
	    ans.pb(win[i]);
	} else if (most == amnt) {
	    ans.pb(win[i]);
	}
    }

    for (int i = 0; i < ans.size(); i++) {
	cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}
