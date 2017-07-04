#include <bits/stdc++.h>
using namespace std;

int main() {

    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
	int x; cin >> x;
	if (x + i > N) {
	    cout << i << "\n";
	    break;
	}
    }
    
    return 0;
}
