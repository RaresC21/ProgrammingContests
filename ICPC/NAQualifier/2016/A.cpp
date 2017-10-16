#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

int main() {
    ios_base::sync_with_stdio(false);

    map<char, string> mp;
    mp['a'] = "@";
    mp['b'] = "8";
    mp['c'] = "(";
    mp['d'] = "|)";
    mp['e'] = "3";
    mp['f'] = "#";
    mp['g'] = "6";
    mp['h'] = "[-]";
    mp['i'] = "|";
    mp['j'] = "_|";
    mp['k'] = "|<";
    mp['l'] = "1";
    mp['m'] = "[]\\/[]";
    mp['n'] = "[]\\[]";
    mp['o'] = "0";
    mp['p'] = "|D";
    mp['q'] = "(,)";
    mp['r'] = "|Z";
    mp['s'] = "$";
    mp['t'] = "']['";
    mp['u'] = "|_|";
    mp['v'] = "\\/";
    mp['w'] = "\\/\\/";
    mp['x'] = "}{";
    mp['y'] = "`/";
    mp['z'] = "2";
    mp[' '] = " ";

    string s; getline(cin, s);
    vector<char> v;
    FOR(i,0,SZ(s)) {
        v.push_back(s[i]);
    }

    FOR(i,0,SZ(s)) {
        if (v[i] >= 'A' && v[i] <= 'Z') v[i] += 32;
        if (v[i] >= 'a' && v[i] <= 'z') cout << mp[v[i]];
        else cout << v[i];
    }
    cout << "\n";

    return 0;
}