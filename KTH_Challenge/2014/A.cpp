#include <bits/stdc++.h>
using namespace std;

int main() {

    int H; cin >> H;
    int num_nodes = 1;
    for (int i = 0; i <= H; i++)
	num_nodes *= 2;

    int cur = 1;
    string op;
    if (cin >> op) {
	for (char c : op) {
	    if (c == 'L')
		cur *= 2;
	    else
		cur = cur * 2 + 1;
	}
    }

    cout << num_nodes - cur << "\n";
    
    return 0;
}
