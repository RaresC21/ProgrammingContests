#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;

int N, L;
string ans;
bool found;
map<string, bool> dict;
set<char> options[20];

void solve(int pos, string s) {
    if (found) return;
    if (pos == L) {
        if (!dict.count(s)) {
            ans = s;
            found = true;
        }
        return;
    }

    for (char c : options[pos]) {
        solve(pos + 1, s + c);
    }
}

int main() {
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        cin >> N >> L;

        found = false;
        for (int i = 0; i < L; i++) options[i].clear();
        dict.clear();

        for (int i = 0; i < N; i++) {
            string s; cin >> s;
            dict[s] = true;

            for (int k = 0; k < L; k++) {
                options[k].insert(s[k]);
            }
        }

        ans = "-";
        solve(0, "");

        cout << "Case #" << t << ": ";
        cout << ans << "\n";
    }

    return 0;
}
