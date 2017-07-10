#include <bits/stdc++.h>
using namespace std;

#define MAX 120
int R, C;
char grid[MAX][MAX];
bool met[MAX][MAX];
bool done[MAX * MAX];

struct Window {
    char w[MAX][MAX];
    int r, c;
    Window() {
	memset(w, 0, sizeof(w));
	r = c = -1;
    }
    bool rotate() {
	int temp[MAX][MAX];
	for (int i = 0; i <= r; i++)
	    for (int k = 0; k <= c; k++)
		temp[k][r - i] = w[i][k];
	swap(r, c);
	for (int i = 0; i <= r; i++)
	    for (int k = 0; k <= c; k++)
		w[i][k] = temp[i][k];
    }
    void print() const {
	for (int i = 0; i <= r; i++) {
	    for (int k = 0; k <= c; k++)
		cout << w[i][k];
	    cout << "\n";
	} 
    }
    bool equal(const Window& other) {
	if (r != other.r || c != other.c) return false;
	for (int i = 0; i <= r; i++)
	    for (int k = 0; k <= c; k++)
		if (w[i][k] != other.w[i][k]) return false;
	return true;
    }

};

vector<Window> windows;
int cur_w, cur_h;
void dfs(int r, int c, int width, int height) {
    if (r < 0 || r >= R || c < 0 || c >= C) return;
    if (met[r][c]) return;
    if (grid[r][c] == '#') return;
    met[r][c] = true;


    cur_w = max(cur_w, width);
    cur_h = max(cur_h, height);
    dfs(r + 1, c, width, height + 1);
    dfs(r, c + 1, width + 1, height);
}

bool same(int a, int b) {
    for (int i = 0; i < 4; i++) {
	windows[a].rotate();
	for (int k = 0; k < 4; k++) {
	    windows[b].rotate();
	    if (windows[a].equal(windows[b]))
		return true;
	}
    }
    return false;
}

int main() {

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
	string s; cin >> s;
	for (int k = 0; k < C; k++) {
	    grid[i][k] = s[k];
	}
    }

    for (int i = 0; i < R; i++) {
	for (int k = 0; k < C; k++) {
	    if (grid[i][k] != '#' && !met[i][k]) {
		cur_h = 0, cur_w = 0;
		dfs(i, k, 0, 0);
		Window cur;
		for (int a = 0; a <= cur_h; a++)
		    for (int b = 0; b <= cur_w; b++)
			cur.w[a][b] = grid[i + a][k + b];
		cur.r = cur_h;
		cur.c = cur_w;

		windows.push_back(cur);
	    }
	}
    }

    int ans = windows.size();
    for (int i = 0; i < windows.size(); i++) {
	int cur = 0;
	for (int k = i + 1; k < windows.size(); k++) {
	    if (done[k]) continue;
	    if (same(i, k)) {
		done[k] = true;
		cur++;
	    }
	}
	ans -= cur;
    }

    cout << ans << "\n";
    
    return 0;
}
