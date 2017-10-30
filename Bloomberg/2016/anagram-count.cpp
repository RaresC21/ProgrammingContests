/* 
   /home/rares/ProgrammingContests/Bloomberg/2016/
   anagram-count.cpp
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

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    map<string, int> amnt;
    FOR(i,0,N) {
	string s; cin >> s;
	FOR(k,0,SZ(s)) if (s[k] <= 'Z') s[k] = s[k] - 'A' + 'a';

	sort(s.begin(), s.end());
	amnt[s] ++;
    }

    int ans = 0;
    for (auto a : amnt) {
	if (a.B > 1) ans += a.B;
    }

    cout << ans << "\n";
    
    return 0;
}
