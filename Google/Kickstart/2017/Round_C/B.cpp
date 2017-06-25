#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 100
char grid[MAX][MAX];

int main() {

    ifstream cin ("input.txt");
    ofstream cout ("ans.txt");

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        int N; cin >> N;
        for (int i = 0; i < N; i++) {
            string s; cin >> s;
            for (int k = 0; k < N; k++) {
                grid[i][k] = s[k];
            }
            // cout << s << "\n";
        }

        int single = 0;
        bool bad = false;
        for (int i = 0; i < N; i++) {
            int amnt = 0;
            for (int k = 0; k < N; k++) {
                if (grid[i][k] == 'X') amnt++;
            }
            if (amnt == 1) single++;
            else if (amnt != 2) {
                bad = true;
                break;
            }
        }
        if (single != 1) bad = true;

        if (bad) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        single = 0;
        for (int k = 0; k < N; k++) {
            int amnt = 0;
            for (int i = 0; i < N; i++) {
                if (grid[i][k] == 'X') amnt++;
            }
            if (amnt == 1) single++;
            else if (amnt != 2) {
                bad = true;
                break;
            }
        }

        if (single != 1) bad = true;

        if (bad) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        map<pair<int, int>, int> amnt;
        for (int i = 0; i < N; i++) {
            pair<int, int> pos = mp(-1, -1);
            for (int k = 0; k < N; k++) {
                if (grid[i][k] == 'X') {
                    if (pos.first == -1) pos.first = k;
                    else pos.second = k;
                }
            }
            if (pos.second == -1) continue;
            amnt[pos]++;
        }

        for (auto a : amnt) {
            if (a.second % 2 != 0)  {
                bad = true;
                break;
            }
        }
        if (bad) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }
        cout << "Case #" << t << ": POSSIBLE\n";
    }

    return 0;
}