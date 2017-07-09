#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

map<pair<int, int>, vector<pair<int, int> > > v;

int main() {
    
    int N; cin >> N;
    string s; cin >> s;
    for (int i = 0; i < N; i++) {
    	for (int k = i + 1; k < N; k++) {
    	    v[mp(s[i], s[k])].pb(mp(i, k));
    	}
    }
    
    long long ans = 0;
    for (auto x : v) {
    	vector<pair<int, int> > cur = x.second;
    	sort(cur.begin(), cur.end());
    	
    	for (int i = 0; i < cur.size(); i++) {
    	    int minim = i + 1, maxim = cur.size() - 1;
    	    int num = maxim + 1;
    	    while (minim <= maxim) {
    		int mid = (minim + maxim) / 2;
    		if (cur[mid].first > cur[i].second) {
    		    maxim = mid - 1;
    		    num = min (num, mid);
    		} else {
    		    minim = mid + 1;
    		}
    	    }
    	    if (num == cur.size()) continue;
     
    	    ans += cur.size() - num;
    	}
    }
     
    cout << ans << "\n";
        
    return 0;
}
