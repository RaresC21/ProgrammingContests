/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   A.cpp
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
    vector<string> v(N);

    set<char> alphabet;
    FOR(i,0,N) {
	cin >> v[i];
	for (auto c : v[i])
	    alphabet.insert(c);
    }
    
    VI num(10);
    FOR(i,0,10)
	num[i] = i;

    int cnt = 0;
    int ans = 0;
    do {
	int conv[255];
	int j = 0;
	for (auto c : alphabet) {
	    conv[c] = num[j];
	    j++;
	}

	bool skip = false;
	FOR(i,0,N) {
	    if (conv[v[i][0]] == 0) {
		skip = true;
		break;
	    }
	}
	if (skip) continue;
	    
	LL sum = 0;
	FOR(i,0,N-1) {
	    LL cur = 0;
	    for(char c : v[i]) {
		cur = (cur * 10) + conv[c];
	    }
	    sum += cur;
	}
	LL total = 0;
	for (char c : v[N - 1]) {
	    total = (total * 10) + conv[c];
	}
	
	if (sum == total) {
	    ans ++;
	}
    } while (next_permutation(num.begin(), num.end()));
    
    ROF(i, 1, 10 - SZ(alphabet) + 1)
	ans /= i;
    cout << ans << "\n";

    return 0;
}
