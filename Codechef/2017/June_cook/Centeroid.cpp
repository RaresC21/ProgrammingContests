
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

int main() {

    int T; cin >> T;
    while (T--) {
	int N, B; cin >> N >> B;
	if (N == 2 && B == 0) {
	    cout << "NO\n";
	    continue;
	}
	if (N == 2 && B == 1) {
	    cout << "YES\n";
	    cout << "1 2\n";
	    continue;
	}
	
	vector<pair<int, int> > v;
	for (int i = 1; i < B; i++) {
	    v.pb(mp(i, i + 1));
	}

	int remain = (N / 2) - B;

	if (remain < 0) {
	    cout << "NO\n";
	    continue;
	}

	if (remain < B) {
	    cout << "NO\n";
	    continue;
	}

	if (remain > 0) {
	    v.pb(mp(1, B + 2));
	    for (int i = 1; i < B; i++) {
		v.pb(mp(B + i + 1, B + i + 2));
	    }
	}

	int cur = v.size() + 2;
	for (int i = cur; i <= N; i++)
	    v.pb(mp(1 + B, i));

	cout << "YES\n";
	for (int i = 0; i < v.size(); i++) {
	    cout << v[i].first << " " << v[i].second << "\n";
	}
    }
    
    return 0;
}
