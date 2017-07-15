#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAX 1000006
int arr[MAX], event[MAX], single[MAX];

#undef int
int main() {
#define int long long
    
    int N; cin >> N;

    int change = 0;
    int cur = 0;
    for (int i = 1; i <= N; i++) {
	cin >> arr[i];
	cur += abs(arr[i] - i);
	
	if (i < arr[i]) { // the number is before its inteded place.
	    change --;
	    event[arr[i] + 1 - i] += 2;
	} else {
	    change ++;
	    event[N - i + 1 + arr[i]] += 2;
	}
	single[N - i + 1] += (arr[i] - 1) -  (N - arr[i]);
	event[N - i + 1] -= 1;
	event[N - i + 2] -= 1;
    }

    int ans = cur;
    int per = 0;
    for (int i = 1; i < N; i++) {
	change += event[i];
	cur += single[i]; 
	cur += change;

	if (ans > cur) {
	    ans = cur;
	    per = i;
	}
    }

    cout << ans << " " << per << "\n";
    
    return 0;
}
