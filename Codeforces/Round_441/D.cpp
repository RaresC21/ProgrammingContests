/* 
   /home/rares/ProgrammingContests/Codeforces/Round_441/
   D.cpp
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

const int MAX = 300005;
bool met[MAX];

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;

    cout << 1 << " ";
    int cnt = 0;
    int l = N;
    FOR(i,1,N+1) {	
    	int x; cin >> x;
    	met[x] = true;
    	while (l > 0 && met[l]) {
    	    l--;
    	    cnt++;
    	}
    	
    	cout << i - cnt + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}
