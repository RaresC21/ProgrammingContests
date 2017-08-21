#include <bits/stdc++.h>
using namespace std;

#define MAX 100
int dp[MAX][MAX];

int traderProfit(int K, int N, vector <int> A) {
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    
    for (int i = 0; i < A.size(); i++) {
        for (int k = i + 1; k < A.size(); k++) {
            int amnt = A[k] - A[i];
            dp[1][k] = max(dp[1][k], amnt);
            ans = max(ans, dp[1][k]);
        }
    }
    
    for (int i = 2; i <= K; i++) {
        for (int k = i + 1; k < A.size(); k++) {
            for (int j = k - 1; j >= 0; j--) {
                int cur = A[k] - A[j];
                
                for (int a = 0; a < j; a++) {
                    if (dp[i - 1][a] != -1)
                        dp[i][k] = max(dp[i][k], dp[i - 1][a] + cur);
                }
            }
            ans = max(ans, dp[i][k]);
        }
    }
    return ans;
}

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int k;
        cin >> k;
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
	    cin >> arr[arr_i];
        }
        int result = traderProfit(k, n, arr);
        cout << result << endl;
    }
    return 0;
}
