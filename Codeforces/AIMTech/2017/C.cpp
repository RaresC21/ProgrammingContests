/* 
   /home/rares/ProgrammingContests/Codeforces/AIMTech/2017/
   C.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 100005
int a[MAX];
bool met[MAX];
vector<vector<int> > g;

void group(int v, vector<int>& cur) {
    if (met[v]) return;
    met[v] = true;
    cur.pb(v);

    group(a[v], cur);
}

int main() {

    vector<pair<int, int> > order;
    
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
	cin >> a[i];
	order.pb(mp(a[i], i));
    }
    sort(order.begin(), order.end());
    for (int i = 0; i < order.size(); i++) {
	a[order[i].second] = i + 1;
    }

    for (int i = 1; i <= N; i++) {
	if (met[i]) continue;
	vector<int> cur;
	group(i, cur);
	g.pb(cur);
    }

    cout << g.size() << "\n";
    for (int i = 0; i < g.size(); i++) {
	cout << g[i].size();
	for (int k : g[i])
	    cout <<  " " << k;
	cout << "\n";
    }
    
    return 0;
}
