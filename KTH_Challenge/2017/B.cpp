#include <bits/stdc++.h>
using namespace std;

long long f(long long x) {
    long long ans = 0;
    while (x != 1) {
	if (x % 2 == 0)
	    x /= 2;
	else
	    x += 1;
	ans += 1;
    }
    return ans;
}

const long long MOD = 1000000007;
long long calc(long long x) {
    if (x == 0) return 0;
    if (x == 1) return 0;
    if (x % 2 == 0) {
	long long nxt = x / 2;
	return (nxt + x - 2 + 2 * calc(nxt)) % MOD;
    }
    else 
	return f(x) + calc(x - 1);
}

int main() {

    long long a, b; cin >> a >> b;
    cout << (calc(b) - calc(a - 1) + MOD) % MOD << "\n";
    
    return 0;
}
