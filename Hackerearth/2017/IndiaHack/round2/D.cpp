#include <bits/stdc++.h>
using namespace std;
     
#define pb push_back
#define mp make_pair
     
vector<int> to_base(int x) {
    vector<int> ans;
    while (x) {
    	ans.pb(x % 2);
    	x /= 2;
    }
    return ans;
}
     
void solve() {
     
    int N, S, X; cin >> N >> S >> X;
    if (N == 1) {
    	if (S == X) {
    	    cout << "Yes\n";
    	} else {
    	    cout << "No\n";
    	}
    	return;
    }
    if (S < X) {
            
	cout << "No\n";
	return;
    }
    if (S == X) {
    	cout << "Yes\n";
    	return;
    }
     
    vector<int> x2 = to_base(X);
     
    S -= X;
        
    if (S % 2 != 0) {
    	cout << "No\n";
    	return;
    }
    S /= 2;
     
    if (S < 0) {
    	cout << "No\n";
    	return;
    }
        
    int amnt = 2;
    vector<int> s2 = to_base(S);
        
    for (int i = 0; i < s2.size(); i++) {
    	if (i < x2.size()) {
    	    if (s2[i] && x2[i]) amnt = 3;
    	} else
    	    break;
    }
     
    if (amnt > N) {
    	cout << "No\n";
    } else {
    	cout << "Yes\n";
    }
}
     
int main() {
     
    int T; cin >> T;
    while(T--) {
    	solve();
    }
        
    return 0;
}
