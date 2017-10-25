/* 
   /home/rares/ProgrammingContests/Codeforces/Round_442/
   B.cpp
*/

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

const int MAX = 5001;
int suf_b[MAX], pref_b[MAX], pref_a[MAX];

int main() {
    ios_base::sync_with_stdio(false);

    string s; cin >> s;
    s = " " + s;
    FOR(i,1,SZ(s)) {
	pref_a[i] = pref_a[i - 1];
	pref_b[i] = pref_b[i - 1];
	if (s[i] == 'a') pref_a[i] ++;
	if (s[i] == 'b') pref_b[i] ++;
    }

    int ans = 0;
    FOR(i,0,SZ(s)) {
	FOR(k,i,SZ(s)) {
	    int p1 = pref_b[i];
	    int p2 = pref_a[k] - pref_a[i];
	    int p3 = pref_b[SZ(s) - 1] - pref_b[k+1];

	    ans = max(ans, SZ(s) - p1 - p2 - p3 - 1);
	}
    }

    cout << ans << "\n";
    
    return 0;
}
