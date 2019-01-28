#include <bits/stdc++.h>
using namespace std;

#define MAX 1001
bool met[MAX][MAX], met2[MAX][MAX];
int amnt[MAX][MAX];
char grid[MAX][MAX];
int count_;

int R, C, Q;

void dfs (int r, int c) {

    if (r < 0 || c < 0 || r >= R || c >= C) return;
    if (met[r][c]) return;

    if (grid[r][c] == '*') {
        count_++;
        return;
    }

    met[r][c] = true;

    dfs(r+1, c);
    dfs(r-1, c);
    dfs(r, c+1);
    dfs(r, c-1);
}

void dfs2 (int r, int c) {

    if (r < 0 || c < 0 || r >= R || c >= C) return;
    if (met2[r][c]) return;

    if (grid[r][c] == '*') {
        return;
    }

    met2[r][c] = true;
    amnt[r][c] = count_;

    dfs2(r+1, c);
    dfs2(r-1, c);
    dfs2(r, c+1);
    dfs2(r, c-1);
}

int main() {

    cin >> R >> C >> Q;
    for (int i = 0; i < R; i++) {
        string s; cin >> s;
        for (int k = 0; k < C; k++) {
            grid[i][k] = s[k];
        }
    }

    for (int i = 0; i < R; i++) {
        for (int k = 0; k < C; k++) {
            if (grid[i][k] == '*' || met[i][k]) continue;
            count_ = 0;
            dfs(i, k);
            dfs2(i, k);
        }
    }

    for (int i = 0; i < Q; i++) {
        int r, c; cin >> r >> c;
        r--; c--;
        cout << amnt[r][c] << "\n";
    }

    return 0;
}
