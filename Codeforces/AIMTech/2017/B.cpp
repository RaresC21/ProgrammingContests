/* 
   /home/rares/ProgrammingContests/Codeforces/AIMTech/2017/
   B.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 51
int grid[MAX][MAX];
lli power[MAX];

int main() {

    power[0] = 1;
    for (int i = 1; i < MAX; i++)
	power[i] = power[i - 1] * 2;

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) {
	for (int k = 0; k < M; k++) {
	    cin >> grid[i][k];
	}
    }

    lli ans = 0;
    for (int i = 0; i < N; i++) {
	int white = 0, black = 0;
	for (int k = 0; k < M; k++) {
	    if (grid[i][k]) white++;
	    else black++;
	}

	ans += power[white] + power[black] - 2;
    }

    for (int k = 0; k < M; k++) {
	int white = 0, black = 0;
	for (int i = 0; i < N; i++) {
	    if (grid[i][k]) white++;
	    else black++;
	}
	ans += power[white] + power[black] - 2;
    }

    cout << ans - N * M << "\n";
    
    return 0;
}
