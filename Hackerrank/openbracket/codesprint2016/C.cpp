#include <bits/stdc++.h>
using namespace std;

#define MAX 51
int a[MAX * MAX * MAX + 1];
int val[MAX][MAX][MAX];
int maxim[MAX][MAX][MAX];
int cur[MAX][MAX][MAX];

int main() {

    int T; cin >> T;
    while (T--) {
	int N; cin >> N;
	for (int i = 0; i < N * N * N; i++)
	    cin >> a[i];
	for (int i = 1; i <= N; i++)
	    for (int k = 1; k <= N; k++)
		for (int j = 1; j <= N; j++)
		    val[i][k][j] = a[(i - 1) * N * N + (k - 1) * N + j - 1];

	for (int k = 1; k <= N; k++) {
	    int ans = 0;
	    for (int a = k; a <= N; a++) {
		for (int b = k; b <= N; b++) {
		    for (int c = k; c <= N; c++) {
			if (k == 1)
			    cur[a][b][c] = val[a][b][c];
			else {
			    cur[a][b][c] = max(maxim[a - 1][b][c],
					       max(maxim[a][b - 1][c],
						   max(maxim[a][b][c - 1],
						       max(maxim[a - 1][b - 1][c],
							   max(maxim[a - 1][b][c - 1],
							       max(maxim[a][b - 1][c - 1],
								   max(maxim[a][b][c], maxim[a - 1][b - 1][c - 1])))))));
			}
		    }
		}
	    }
	    for (int a = k; a <= N; a++)
		for (int b = k; b <= N; b++)
		    for (int c = k; c <= N; c++) {
			maxim[a][b][c] = cur[a][b][c];
			if (maxim[a][b][c] == k) {
			    ans++;
			}
		    }

	    cout << ans << " ";
	}
	cout << "\n";
    }
    
    return 0;
}
