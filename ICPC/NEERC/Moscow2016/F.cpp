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

const int MAX = 200;
bool have[MAX];
string s;
map<char, int> order;
map<int, char> back_;

string gen(char l, char r) {

    string ans = "";
    if (order[r] == order[l]) {
        return ans + l;
    } else if (order[r] == order[l] + 1) {
        ans = ans + l;
        ans = ans + r;
        return ans;
    } else {
        if (l == '0') {
            l = '!';
        } else if (l == 'A') {
            l = ':';
        } else if (l == 'a') {
            l = '[';
        }

        ans = ans + (char)(l);
        ans = ans + '-';
        ans = ans + (char)(r);
    }
    return ans;
}

string solve() {
    int l = -1;
    vector<string> sol;
    FOR(i,0,MAX) {
        if (have[i]) {
            if (l == -1) l = i;
        } else if (l != -1) {
            sol.push_back(gen(back_[l], back_[i - 1]));
            l = -1;
        }
    }
    sort(sol.begin(), sol.end());
    string ans = "";
    for (auto cur : sol) {
        ans = ans + cur;
    }

    return ans;
}


int main() {
    ios :: sync_with_stdio(false);

    int cnt = 1;
    order[' '] = 0;
    back_[0] = ' ';
    for (char c = '0'; c <= '9'; c++) {
        order[c] = cnt;
        back_[cnt] = c;
        cnt++;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        order[c] = cnt;
        back_[cnt] = c;
        cnt++;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        order[c] = cnt;
        back_[cnt] = c;
        cnt++;
    }

    getline(cin, s);
    FOR(i,0,SZ(s)) {
        char c = s[i];
        have[order[c]] = true;
    }
    int amnt = 0;
    FOR(i,0,cnt) amnt += have[i];
    if (amnt == 63) {
        cout << "%[^!]\n";
        return 0;
    }
    string a = solve();

    FOR(i,0,cnt) {
        have[i] ^= 1;
    }
    string b = solve();

    if (SZ(b) == 0) {
        cout << "%[" << a << "]\n";
        return 0;
    }

    b = '^' + b;

    if (SZ(a) > SZ(b)) {
        swap(a, b);
    } else if (SZ(a) == SZ(b)) {
        a = min(a, b);
    }

    cout << "%[" << a << "]\n";

    return 0;
}