#include <bits/stdc++.h>
using namespace std;

int main() {

    int N; cin >> N;
    int ans = 1000000;
    for (int i = 1; i <= N; i++) {
	int two = 1;
	int days = 0;
	while (two < i) {
	    two *= 2;
	    days++;
	}
	int to_make = N - (two - N);
	days += (to_make + i - 1) / i;
	ans = min(days, ans);
    }

    cout << ans << "\n";
    
    return 0;
}
