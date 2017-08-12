/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   H.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 102
int R, C; 
char grid[MAX][MAX], section[MAX][MAX];
bool met[MAX][MAX], bad[MAX][MAX];
vector<char> touch[300];

void fill(int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) return;
    if (grid[r][c] == 'X') return;
    if (grid[r][c] == 'A' || grid[r][c] == 'B') return;
    if (bad[r][c]) return;
    bad[r][c] = true;

    fill(r - 1, c);
    fill(r + 1, c);
    fill(r, c + 1);
    fill(r, c - 1);
}

void dfs(int i, int k, char color) {
    if (grid[i][k] != '.') return;
    if (bad[i][k]) return;
    if (met[i][k]) return;
    met[i][k] = true;

    section[i][k] = color;

    dfs(i + 1, k, color);
    dfs(i - 1, k, color);
    dfs(i, k - 1, color);
    dfs(i, k + 1, color);
}

void surround(int r, int c, char color) {
    for (int i = -1; i <= 1; i++) {
	for (int k = -1; k <= 1; k++) {
	    if (r + i < 0 || c + k < 0 || r + i >= R || c + k >= C) continue;
	    if (!bad[r + i][c + k] && met[r + i][c + k]) {
		touch[section[r + i][c + k]].pb(color);
	    }
	}
    }
}

bool cmp(const pair<vector<char>, char>& a, const pair<vector<char>, char>& b) {
    return a.first.size() < b.first.size();
}

int area(char sec = '.') {
    int ans = 0;
    for (int i = 0; i < R; i++) {
	for (int k = 0; k < C; k++) {
	    if (bad[i][k]) continue;
	    if (section[i][k] == sec) {
		section[i][k] = 'X';
		ans++;
	    }
	    if (sec == '.' && section[i][k] != 'X' && section[i][k] != 'A' && section[i][k] != 'B') ans++;
	}
    }
    return ans;
}

int main() {

    pair<int, int> A, B;
    
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
	string s; cin >> s;
	for (int k = 0; k < C; k++) {
	    grid[i][k] = s[k];
	    section[i][k] = grid[i][k];
	    if (grid[i][k] == 'A') {
		A = mp(i, k);
	    } else if (grid[i][k] == 'B') {
		B = mp(i, k);
	    }
	}
    }

    for (int k = 0; k < C; k++)
	fill(0, k), fill(R - 1, k);
    for (int i = 0; i < R; i++)
	fill(i, 0), fill(i, C - 1);
    
    char cur = 'P';
    for (int i = 1; i < R - 1; i++) {
	for (int k = 1; k < C - 1; k++) {
	    if (grid[i][k] != '.') continue;
	    if (met[i][k] || bad[i][k]) continue;
	    dfs(i, k, cur++);
	}
    }

    surround(A.first, A.second, 'A');
    surround(B.first, B.second, 'B');

    vector<pair<vector<char>, char> > amnt;
    for (char c = 'P'; c <= 'R'; c++) {
	set<char> s(touch[c].begin(), touch[c].end() );
	touch[c].assign(s.begin(), s.end());
	amnt.pb(mp(touch[c], c));
    }

    sort(amnt.begin(), amnt.end(), cmp);

    int middle = 0, area_a = 0, area_b = 0;
    if (amnt[0].first.size() == 0 && amnt[1].first.size() == 1 && amnt[2].first.size() == 2) {
	middle = area(amnt[1].second);

	if (amnt[1].first[0] == 'A') {
	    area_a = area(amnt[0].second);
	    area_b = area();
	} else {
	    area_b = area(amnt[0].second);
	    area_a = area();
	}
    } else if (amnt[0].first.size() == 0 &&
	       amnt[1].first.size() == 1 &&
	       amnt[2].first.size() == 1) {
	
	middle = area(amnt[0].second);

	if (amnt[1].first[0] == 'A') {
	    area_a = area(amnt[1].second);
	    area_b = area();
	} else {
	    area_b = area(amnt[1].second);
	    area_b = area();
	}
    } else {
	middle = area(amnt[2].second);

	if (amnt[0].first[0] == 'A') {
	    area_a = area(amnt[1].second);
	    area_b = area(amnt[0].second);
	} else {
	    area_b = area(amnt[1].second);
	    area_a = area(amnt[0].second);
	}
    }

    cout << area_a << " " << area_b << " " << middle << "\n";
    
    return 0;
}
