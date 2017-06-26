#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli exponent(lli a, lli x, lli mod) {
    lli ans = 1;
    while (x) {
	if (x % 2 == 1)
	    ans = (ans * a) % mod;
	x /= 2;
	a = (a * a) % mod;
    }
    return ans;
}

lli inverse(lli b, lli mod) {
    return exponent(b, mod - 2, mod);
}

lli root(lli n) {
    lli minim = 1, maxim = n;
    lli ans = n;
    while (minim <= maxim) {
	lli mid = (minim + maxim) / 2;
	if (mid * mid < n) {
	    minim = mid + 1;
	} else {
	    maxim = mid - 1;
	    ans = min(ans, mid);
	}
    }
    return ans;
}

int main() {

    int T; cin >> T;
    while (T--) {
	lli r, S, p;
	cin >> r >> S >> p;

	lli y = (S * (r - 1) + 1) % p;
	if (y == 0) {
	    cout << "-1\n";
	    continue;
	}
	
	lli m = root(p);
	lli r_inv = exponent(inverse(r, p), m, p);
	
	map<lli, lli> table;
	lli a = 1;
	for (int i = 0; i < m; i++) {
	    table[a] = i;
	    a = (a * r) % p;
	}

	for (int i = 0; i < m; i++) {
	    if (table.count(y)) {
		cout << i * m  + table[y] << "\n";
		break;
	    }
	    y = (y * r_inv) % p;
	}
    }
    
    return 0;
}
