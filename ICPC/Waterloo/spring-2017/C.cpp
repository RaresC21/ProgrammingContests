#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

#define MAX 100005
int x[MAX], y[MAX], val[MAX], best[MAX];
int right_[MAX], left_[MAX], down_[MAX], up_[MAX];
map<int, set<pii> > hor, ver;

LL ans = 0;
void eval(int i) {
    ans -= best[i];
    best[i] = max(right_[i], left_[i]) + max(up_[i], down_[i]);
    ans += best[i];
}

int main() {

    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    FOR(i,0,N) {
    	cin >> x[i] >> y[i];
    	cin >> val[i];

        if (hor.count(y[i])) {
            auto it = hor[y[i]].upper_bound(MP(x[i], -1));
            if (it != hor[y[i]].end()) {
                left_[it->second] = val[i];
                eval(it->second);
                right_[i] = val[it->second];
            }
            if (it != hor[y[i]].begin()) {
                --it;
                right_[it->second] = val[i];
                eval(it->second);
                left_[i] = val[it->second];
            }
        }

        // same, but for vertical hits
        if (ver.count(x[i])) {
            auto it = ver[x[i]].upper_bound(MP(y[i], -1));
            if (it != ver[x[i]].end()) {
                down_[it->second] = val[i];
                eval(it->second);
                up_[i]  = val[it->second];
            }
            if (it != ver[x[i]].begin()) {
                --it;
                up_[it->second] = val[i];
                eval(it->second);
                down_[i] = val[it->second];
            }
        }
        eval(i);
        ver[x[i]].insert(MP(y[i], i));
        hor[y[i]].insert(MP(x[i], i));

	    cout << ans << "\n";
    }

    return 0;
}
