#include <bits/stdc++.h>
using namespace std;

int arr[101];

int main() {

    int N; cin >> N;
    for (int i = 0; i < N; i++)
	cin >> arr[i];
    
    int ans = 0;
    for (int i = 0; i < N; i++) {
	for (int k = 0; k <= i; k++) {
	    swap(arr[i], arr[k]);

	    int cur = 0;
	    for (int j = 0; j < N; j++) {
		if (arr[j] == 1)
		    cur++;
		else
		    cur = 0;
		ans = max(ans, cur);
	    }
	    
	    swap(arr[i], arr[k]);
	}
    }

    cout << ans << "\n";
    
    return 0;
}
