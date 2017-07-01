#include <bits/stdc++.h>
using namespace std;

#define MAX 1001
int w[MAX];

int main() {

    int N, C; cin >> N >> C;
    for (int i = 0; i < N; i++) {
	cin >> w[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
	int sum = 0;
	int cur = 0;
	for (int k = i; k < N; k++) {
	    if (sum + w[k] <= C) {
		sum += w[k];
		cur++;
	    }
	}
	ans = max(ans, cur);
    }
    cout << ans << "\n";
    
    return 0;
}
