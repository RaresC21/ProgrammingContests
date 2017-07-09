#include <bits/stdc++.h>
using namespace std;
     
#define pb push_back
#define mp make_pair
     
#define MAX 100005
int arr[MAX];
int dp[MAX][501];
     
int main() {
     
    int N; cin >> N;
    int K; cin >> K;
    for (int i = 0; i < N; i++) {
    	cin >> arr[i];
    }
    dp[0][1] = arr[0];
    for (int i = 1; i < N; i++) {
    	dp[i][1] = min(dp[i - 1][1], arr[i]);
    }
        
    for (int i = 1; i < N; i++) {
    	for (int k = 2; k <= K; k++) {
     
    	    int minim = arr[i];
    	    for (int j = i - 1; j >= 0; j--) {
    		minim = min(minim, arr[j + 1]);
    		dp[i][k] = max(dp[i][k], dp[j][k - 1] + minim);
    	    }
    	}
    }
     
    cout << dp[N - 1][K] << "\n";
        
    return 0;
}
