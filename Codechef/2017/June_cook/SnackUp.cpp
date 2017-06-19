#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    int T; cin >> T;
    while (T--) {
	int N; cin >> N;
	cout << N << "\n";
	for (int i = 1; i <= N; i++) { // round number
	    printf("%d\n", N);
	    for (int k = 1; k <= N; k++) {
		int cur = k + i - 1;
		if (cur > N) cur = cur % N;
		int nxt_ = cur + 1;
		if (nxt_ > N) nxt_ = 1;
		printf("%d %d %d\n", k, cur, nxt_);
	    }
	}
	
    }

    
    return 0;
}
