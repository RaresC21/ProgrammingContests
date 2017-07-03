#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back

int main() {

    lli x;
    while (cin >> x) {
	x *= 10000000LL;
	lli N; scanf("%lld", &N);

	if (N == 0) {
	    printf("danger\n");
	    continue;
	}
	if (N == 1) {
	    printf("danger\n");
	    lli whatever; scanf("%lld", &whatever);
	    continue;
	}

	vector<lli> v;
	for (int i = 0; i < N; i++) {
	    lli a; scanf("%lld", &a);
	    v.pb(a);
	}

	sort(v.begin(), v.end());

	int l = 0, r = v.size() - 1;
	bool sol = false;
	while (l < r) {
	    if (v[l] + v[r] == x) {
		printf ("yes %lld %lld\n", v[l], v[r]);
		sol = true;
		break;
	    }
	    if (v[l] + v[r] < x) {
		l++;
	    } else {
		r--;
	    }
	}

	if (!sol) {
	    printf("danger\n");
	}
	
    }
    
    return 0;
}
