#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
     
int main() {
    
    
    int N, M; cin >> N >> M;
    
    int people = 0;
    int empty = M;
    int standing = 0;
    
    int ans = 0;
    for (int i = 0; i < N - 1; i++) {
    	int a, b; cin >> a >> b;
    	people += a;
    	people -= b;
	
    	if (people > M) {
    	    empty = 0;
    	    standing = people - M;
    	} else {
    	    empty = M - people;
    	    standing = 0;
    	}
	
    	if (empty == 0)
    	    ans++;
    }
    
    cout << ans << "\n";
    
    return 0;
}
