/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   G.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define INF 1000000000000000009
#define MAX 51
int N;
int goal[MAX];
lli moves[MAX];

void init() {
    lli p = 1;
    for (int i = 0; i < MAX; i++) {
	moves[i] = p - 1;
	p *= 2;
    }
}

bool read_row(int k) {
    int M; cin >> M;
    int last = 100;
    for (int i = 0; i < M; i++) {
	int r; cin >> r;
	if (r > last) return false;
	goal[r] = k;
	N = max(N, r);
    }
    return true;
}

lli solve(int disk, int to_move, int pile, int target) {
    if (disk == 0 || to_move == 0) return 0;
    if (goal[to_move] == pile) return solve(disk, to_move - 1, pile, target);

    if ((to_move - disk) % 2 == 0) {
	// must be in 'target' position
	int cur_target = target;
	if (goal[to_move] != cur_target) return -INF;
	
	int cur_pile = (pile + 1) % 3;
	if (cur_pile == cur_target) cur_pile = (cur_pile + 1) % 3;

	return (moves[to_move - 1] + 1) + solve(to_move - 1, to_move - 1, cur_pile, cur_target);
    } else {
	// must be in remaining position. i.e. not in current pile or in target
	int cur_target = (target + 1) % 3;
	if (cur_target == pile) cur_target = (cur_target + 1) % 3;
	if (goal[to_move] != cur_target) return -INF;

	int cur_pile = target;
	return (moves[to_move - 1] + 1) + solve(to_move - 1, to_move - 1, cur_pile, cur_target);
    }
}

int main() {
    
    init();

    for (int i = 0; i < 3; i++)
	if (!read_row(i)) {
	    cout << "No\n";
	    return 0;
	}

    lli cur = solve(N, N, 0, 2);
    if (cur < 0) {
	cout << "No\n";
    } else {
	cout << moves[N] - cur << "\n";
    }
	
    return 0;
}
