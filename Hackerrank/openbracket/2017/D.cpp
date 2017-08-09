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

int N, M; 
int temp[MAX * MAX];
int prev_[MAX * MAX], dp[MAX * MAX];
int smallest_prev[MAX * MAX];
vector<vector<int> > grid;
vector<vector<int> > amnt;

inline void build_tight(int i, int k) {
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
    temp[i] = cur;
}

inline void build_stack(int k) {
	stack<pair<int, int> > st;
	for (int j = N - 1; j >= 0; j--) {
		while (!st.empty() && st.top().first >= temp[j]) {
			smallest_prev[st.top().second] = j;
			st.pop();
		}
		st.push(mp(temp[j], j));
	}
	while (!st.empty()) {
		smallest_prev[st.top().second] = -1; // have none that are smaller
		st.pop();
	}
}

int main() {

    cin >> N >> M;
    grid.resize(N, vector<int>(M, 0));
    amnt.resize(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++) {
    	for (int k = 0; k < M; k++) {
	    	scanf("%d", &grid[i][k]);
		}
    }

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
		
		for (int i = 1; i < N; i++)
			build_tight(i, k);
		build_stack(k);

		for (int i = 1; i < N; i++) {
		    dp[i] = 0;
	    	int cur = amnt[i][k];
	    	int tmp = cur;
            cur = temp[i];

		    if (cur == 0) {
				dp[i] = amnt[i][k];
				ans += dp[i];
				prev_[i] = i;
				continue;
		    }

		    int indx = smallest_prev[i];
		    if (indx < prev_[i - 1]) indx = -1;
		    else if (amnt[indx][k] > cur) {
			    dp[i] += cur - amnt[indx][k];
		    }

		    if (indx == -1) {
				dp[i] = cur * (i - prev_[i - 1] + 1);
		    } else {
				dp[i] += cur * (i - indx);
				dp[i] += dp[indx];
		    }
		    
		    dp[i] += tmp - cur;
		    ans += dp[i];
		    prev_[i] = prev_[i - 1];
		}
    }
    
    cout << ans << "\n";
    
    return 0;
}
