#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back

int t[40];

int main() {

    string s; cin >> s;
    for (int i = 0; i < 26; i++) {
        cin >> t[i];
    }

    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += t[s[i] - 'a'];
    }

    cout << ans << "\n";
    
    return 0;
}