#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 60
string s[2];
int c[2];
int dp[MAX][MAX][MAX];

int main() {

    ifstream cin ("input.txt");
    ofstream cout ("ans.txt");

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        memset(dp, 0, sizeof(dp));

        int N, Q; cin >> N >> Q;

        if (N == 1) {
            string s;
            for (int i = 0; i < N; i++) {
                cin >> s;
            }

            string mine; cin >> mine;

            int correct; cin >> correct;

            int same = 0;
            for (int i = 0; i < mine.size(); i++) {
                if (mine[i] == s[i])
                    same++;
            }

            cout << "Case #" << t << ": ";

            if (correct < same) {
                cout << Q - (same - correct) << "\n";
            } else {
                cout << Q - (correct - same) << "\n";
            }
            continue;
        }

        for (int i = 0; i < N; i++) {
            cin >> s[i];
        }
        string mine; cin >> mine;
        for (int i = 0; i < N; i++)
            cin >> c[i];

        // say that first is true
        if (s[0][0] == 'T') {
            if (s[1][0] == 'T')
                dp[0][1][1] = mine[0] == 'T';
            else
                dp[0][1][0] = mine[0] == 'T';
        } else {
            if (s[1][0] == 'T')
                dp[0][0][1] = mine[0] == 'T';
            else
                dp[0][0][0] = mine[0] == 'T';
        }

        // say that first is false
        if (s[0][0] == 'F') {
            if (s[1][0] == 'F')
                dp[0][1][1] = max(dp[0][1][1], (int)(mine[0] == 'F'));
            else
                dp[0][1][0] = max(dp[0][1][0], (int)(mine[0] == 'F'));
        } else {
            if (s[1][0] == 'F')
                dp[0][0][1] = max(dp[0][0][1], (int)(mine[0] == 'F'));
            else
                dp[0][0][0] = max(dp[0][0][0], (int)(mine[0] == 'F'));
        }

        for (int i = 1; i < Q; i++) {
            for (int k = 0; k <= c[0]; k++) {
                for (int j = 0; j <= c[1]; j++) {
                    // say that current is false.
                    if (s[0][i] == 'F' && k > 0) {
                        if (s[1][i] == 'F' && j > 0)
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k - 1][j - 1] + (mine[i] == 'F'));
                        else if (s[1][i] == 'T')
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k - 1][j] + (mine[i] == 'F'));
                    } else if (s[0][i] == 'T') {
                        if (s[1][i] == 'F' && j > 0)
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k][j - 1] + (mine[i] == 'F'));
                        else if (s[1][i] == 'T')
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k][j] + (mine[i] == 'F'));
                    }

                    // say that current one is True
                    if (s[0][i] == 'T' && k > 0) {
                        if (s[1][i] == 'T' && j > 0)
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k - 1][j - 1] + (mine[i] == 'T'));
                        else if (s[1][i] == 'F')
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k - 1][j] + (mine[i] == 'T'));
                    } else if (s[0][i] == 'F') {
                        if (s[1][i] == 'T' && j > 0)
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k][j - 1] + (mine[i] == 'T'));
                        else if (s[1][i] == 'F')
                            dp[i][k][j] = max(dp[i][k][j], dp[i - 1][k][j] + (mine[i] == 'T'));
                    }
                }
            }
        }


        cout << "Case #" << t << ": ";
        cout << dp[Q - 1][c[0]][c[1]] << "\n";
    }

    return 0;
}