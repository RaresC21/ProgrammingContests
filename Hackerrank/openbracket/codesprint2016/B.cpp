#include <bits/stdc++.h>
using namespace std;

int amnt[500];
int val[200005];

int main() {

    int N; cin >> N;
    int D; cin >> D;
    for (int i = 0; i < D; i++) {
	int x; cin >> x;
	val[i] = x;
	amnt[x] ++;
    }

    int ans = 0;
    for (int i = D; i < N; i++) {
	int x; cin >> x;
	val[i] = x;
	
	int cur = 0;
	int last = 0;
	int med = -1;
	for (int k = 0; k <= 200; k++) {
	    if (amnt[k] == 0) continue;
	    cur += amnt[k];

	    if (D % 2 == 0) {
		if (cur == D / 2) {
		    for (int j = k + 1; j <= 200; j++)
			if (amnt[j]) {
			    med = k + j;
			    break;
			}
		    break;
		} else if (cur > D / 2) {
		    med = 2 * k;
		    break;
		}
	    } else {
		if (cur >= D / 2) {
		    med = 2 * k;
		    break;
		}
	    }

	}

	if (x >= med) ans++;

	amnt[x]++;
	amnt[val[i - D]]--;
    }

    cout << ans << "\n";
    
    return 0;
}
