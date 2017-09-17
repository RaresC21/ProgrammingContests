/* 
   /home/rares/ProgrammingContests/ICPC/Waterloo/spring-2017/
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

const int GUESS = 10;
const int MOD = 1000000007;
map<LL, bool> met[GUESS];

// THIS IS ONLY GOING TO WORK IF THE CHARACTERS REALLY ARE PICKED UNIFORLY AT RANDOM.
// although in the samples it doesn't look like they are. 

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    string s; cin >> s;

    LL ans = 0;
    FOR(i,0,N) {
	LL hash1 = 0, hash2 = 0;
	FOR(k,0, min(N, GUESS)) {
	    hash1 = ((hash1 * 26) + s[(i + k) % N] - 'a');
	    hash2 = ((hash2 * 26) + s[(i - k + N) % N] - 'a');

	    met[k][hash1] = true;
	    met[k][hash2] = true;
	}
    }
    
    FOR(k,0,min(N, GUESS)) {
	ans += SZ(met[k]);
    }

    ans += 2LL * N * (max(0, N - GUESS));
    cout << ans << "\n";
    
    return 0;
}
