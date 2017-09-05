#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define mp make_pair
#define pb push_back
#define MAX 1003
int grid[MAX][MAX];
int bl[MAX][MAX], br[MAX][MAX], tl[MAX][MAX], tr[MAX][MAX];

int main() {

    ios::sync_with_stdio(false);
    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= M; k++) {
            cin >> grid[i][k];
            tl[i][k] = max(grid[i][k], tl[i - 1][k]);
            tl[i][k] = max(tl[i][k], tl[i][k - 1]);
        }
    for (int i = 1; i <= N; i++)
        for (int k = M; k >= 1; k--) {
            tr[i][k] = max(grid[i][k], tr[i - 1][k]);
            tr[i][k] = max(tr[i][k], tr[i][k + 1]);
        }
    for (int i = N; i >= 1; i--)
        for (int k = 1; k <= M; k++) {
            bl[i][k] = max(grid[i][k], bl[i + 1][k]);
            bl[i][k] = max(bl[i][k], bl[i][k - 1]);
        }
    for (int i = N; i >= 1; i--) 
        for (int k = M; k >= 1; k--) {
            br[i][k] = max(grid[i][k], br[i + 1][k]);
            br[i][k] = max(br[i][k], br[i][k + 1]);
        }

    int sol = 1000000009;
    int r = -1, c = -1;
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= M; k++) {
            int ans = 0;
            ans = max(ans, tl[i - 1][k - 1]);
            ans = max(ans, tr[i - 1][k + 1]);
            ans = max(ans, bl[i + 1][k - 1]);
            ans = max(ans, br[i + 1][k + 1]);
            if (sol > ans) {
                sol = ans;
                r = i;
                c = k;
            }
        }
    }
    cout << r << " " << c << "\n";
}