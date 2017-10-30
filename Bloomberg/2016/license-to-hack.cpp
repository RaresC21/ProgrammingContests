/* 
   /home/rares/ProgrammingContests/Bloomberg/2016/
   license-to-hack.cpp
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
    
    string s; getline(cin, s);
    int N; cin >> N;

    int i = 0;
    bool flip = true;
    while (i < SZ(s)) {
	string cur = "";
	for (int k = 0; i < SZ(s) && k < N; k++, i++) {
	    cur = cur + s[i];
	}
	if (flip) reverse(cur.begin(), cur.end());
	flip = !flip;
	cout << cur;
    }
    cout << "\n";
    
    return 0;
}
