/* 
   /home/rares/ProgrammingContests/Bloomberg/2016/
   robo-golfer.cpp
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

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    int x; cin >> x;
    int g = x;
    FOR(i,1,N) {
	cin >> x;
	g = gcd(g, x);
    }

    int M; cin >> M;
    FOR(i,0,M) {
	cin >> x;
	if (x % g == 0) {
	    cout << "yes\n";
	} else {
	    cout << "no\n";
	}	    
    }
    
    return 0;
}
