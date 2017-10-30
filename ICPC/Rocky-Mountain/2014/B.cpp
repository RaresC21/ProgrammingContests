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

    int T; cin >> T;
    while (T--) {
        string name; cin >> name;
        string s; cin >> s;
        int year = 0;
        FOR(i,0,4) {
            year = year * 10 + (s[i] - '0');
        }

        cin >> s;
        int birth = 0;
        FOR(i,0,4)
            birth = birth * 10 + (s[i] - '0');

        int course; cin >> course;

        if (year >= 2010) {
            cout << name << " eligible\n";
        } else if (birth >= 1991) {
            cout << name << " eligible\n";
        } else if (course >= 41) {
            cout << name << " ineligible\n";
        } else {
            cout << name << " coach petitions\n";
        }

    }

    return 0;
}