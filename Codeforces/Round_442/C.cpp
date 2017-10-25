/* 
   /home/rares/ProgrammingContests/Codeforces/Round_442/
   C.cpp
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

    VI ans;
    for (int i = 2; i <= N; i+=2) {
	ans.push_back(i);
    }

    for (int i = 1; i <= N; i+=2) {
	ans.push_back(i);
    }

    for (int i = 2; i <= N; i+=2) {
	ans.push_back(i);
    }

    cout << SZ(ans) << "\n";
    for (int a : ans) {
	cout << a << " ";
    }
    cout << "\n";
    
    return 0;
}
