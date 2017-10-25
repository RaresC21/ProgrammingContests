/* 
   /home/rares/ProgrammingContests/Codeforces/Round_442/
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

vector<string> names = {"Danil", "Olya", "Slava", "Ann", "Nikita"};
string s;

bool contain(const string& name, int l, int r) {
    int k = 0;
    FOR(i,l,r) {
	if (name[k] != s[i]) return false;
	k++;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);


    cin >> s;
    int cnt = 0;
    for (string n : names) {
	FOR(i,0,SZ(s) - SZ(n) + 1)
	    if (contain(n, i, i + SZ(n))) {
		cnt++;
	    }
    }

    if (cnt == 1) {
	cout << "YES\n"; 
    } else {
	cout << "NO\n";
    }
    
    return 0;
}
