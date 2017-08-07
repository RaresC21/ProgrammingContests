/* 
   /home/rares/ProgrammingContests/Hackerrank/openbracket/2017/
   D.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 2005
// int grid[MAX][MAXM], amnt[MAX][MAXM];

int main() {

    clock_t begin = clock();
    
    int N, M; cin >> N >> M;
    int NN = N, MM = M;
    int grid[N][M], amnt[N][M];
    //if (N > M) swap(NN, MM);
    
    for (int i = 0; i < N; i++) {
    for (int k = 0; k < M; k++) {
	    int a; scanf("%d", &a);
	    //	    if (N > M) grid[k][i] = a;
	    grid[i][k] = a;
	}
    }

    //    N = NN, M = MM;
    int prev_[N], dp[N];
    int temp[N];

    for (int i = 0; i < N; i++) {
	int k = 1;
	int start_ = 0;
	
	while (k <= M) {
	    while (k < M && grid[i][k] >= grid[i][k - 1])
		k++;
	    for (int j = start_; j < k; j++) {
		amnt[i][j] = j - start_ + 1;
	    }
	    start_ = k;
	    k++;
	}
	
    }

    lli ans = 0;
    for (int k = 0; k < M; k++) {
	ans += amnt[0][k];
    }
    
    for (int k = 0; k < M; k++) {
	temp[0] = dp[0] = amnt[0][k];
	prev_[0] = 0;
	for (int i = 1; i < N; i++) {
	    dp[i] = 0;
	    int cur = amnt[i][k];
	    int tmp = cur;
	    int b = k - cur + 1;
	    
	    if (b >= 0 && grid[i][b] < grid[i - 1][k]) {
		int minim = b, maxim = k;
		int best = MAX * MAX;
		while (minim <= maxim) {
		    int mid = (minim + maxim) / 2;
		    if (grid[i][mid] >= grid[i - 1][k]) {
			maxim = mid - 1;
			best = min(best, mid);
		    } else {
			minim = mid + 1;
		    }
		}
		if (best == MAX*MAX) cur = 0;
		else
		    cur = k - best + 1;
	    }

	    if (cur == 0) {
		dp[i] = amnt[i][k];
		ans += dp[i];
		prev_[i] = i;
		continue;
	    }

	    int indx = -1;
	    for (int j = i - 1; j >= prev_[i - 1]; j--) {
		if (amnt[j][k] <= cur) {
		    indx = j;
		    break;
		}
		if (temp[j] <= cur) {
		    indx = j;
		    dp[i] += cur - amnt[j][k];
		    break;
		}
	    }

	    if (indx == -1) {
		dp[i] = cur * (i - prev_[i - 1] + 1);
	    } else {
		dp[i] += cur * (i - indx);
		dp[i] += dp[indx];
	    }
	    
	    dp[i] += tmp - cur;
	    temp[i] = cur;
	    ans += dp[i];
	    prev_[i] = prev_[i - 1];
	}
    }
    
    cout << ans << "\n";

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << "\n";
    
    return 0;
}
