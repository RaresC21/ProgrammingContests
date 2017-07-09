#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
     
#define MAX 200005
bool moved_[MAX];
     
#undef int
int main() {
#define int long long
        
    int N; cin >> N;
    string s; cin >> s;
     
    int ans = 0;
    int sum = 0, swap = 0;
    int r = 0;
    for (int i = 0; i < 2 * N; i++) {
    	if (moved_[i]) {
    	    swap--;
    	    continue;
    	}
    	
    	r = max(r, i + 1);
    	if (s[i] == ')')
    	    sum--;
    	else
    	    sum++;
    	
    	if (sum < 0) {
    	    int amnt = 0;
    	    while (s[r] == ')') {
    		r++;
    	    }
    	    moved_[r] = true;
     
    	    ans += r - i - swap;
    	    sum = 0;
     
    	    swap++;
    	    r++;
    	} else {
    	}
    }
    cout << ans << "\n";
        
    return 0;
}
