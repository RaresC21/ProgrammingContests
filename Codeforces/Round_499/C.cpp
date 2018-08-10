#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;

int main() {
    io;

    int N; cin >> N;
    int M; cin >> M;
    VI a(N), b(N);

    for (int i = 0; i < N; i++) cin >> a[i];
    for (int k = 0; k < N; k++) cin >> b[k];

    VI v;
    v.pb(a[0]);
    for (int i = 1; i < N; i++) {
      v.pb(b[i]);
      v.pb(a[i]);
    }

    v.pb(b[0]);

    reverse(v.begin(), v.end());

    double mass = M;
    for (int i = 0; i < v.size(); i++) {
      if (v[i] == 1) {
	cout << "-1\n";
	return 0;
      }

      mass = mass + (mass / (v[i] - 1));
    }

    cout << fixed << setprecision(9);
    cout << mass - M << "\n";
    
    return 0;
}
