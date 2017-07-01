#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
int grid[5][5];

int main() {

    const int N = 4;
    
    map<int, pair<int, int> > pos;
    for (int i = 0; i < N; i++)
	for (int k = 0; k < N; k++)
	    pos[i * N + k] = mp(i, k);

    int ans = 0;
    for (int i = 0; i < N; i++) {
	string s; cin >> s;
	for (int k = 0; k < N; k++) {
	    if (s[k] == '.') continue;
	    grid[i][k] = s[k] - 'A';
	    int dx = abs(i - pos[grid[i][k]].first);
	    int dy = abs(k - pos[grid[i][k]].second);
	    ans += dx + dy;
	}
    }
    cout << ans << "\n";
    
    return 0;
}
