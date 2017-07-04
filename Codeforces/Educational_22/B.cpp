#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back

void process(lli n, vector<lli>& v) {
    lli cur = n;
    v.pb(1);
    v.pb(n);
    while (cur < 1000000000000000000 / n) {
	cur *= n;
	v.pb(cur);
    }
}

int main() {

    lli X, Y, L, R; cin >> X >> Y >> L >> R;

    vector<lli> x, y;
    process(X, x);
    process(Y, y);

    vector<lli> unlucky;
    for (lli xx : x) {
	for (lli yy : y) {
	    lli sum = xx + yy;
	    if (sum >= L && sum <= R)
		unlucky.pb(sum);
	}
    }

    unlucky.pb(L - 1);
    unlucky.pb(R + 1);
    sort(unlucky.begin(), unlucky.end());

    lli last = unlucky[0];
    lli ans = 0;
    for (int i = 1; i < unlucky.size(); i++) {
	lli num = unlucky[i];
	ans = max(ans, num - last);
	last = num;
    }

    cout << ans - 1 << "\n";
    
    return 0;
}
