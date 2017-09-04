#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define MAX 1003
#define pb push_back
lli grid[MAX][MAX], ans[MAX][MAX];
lli owe[MAX], gain[MAX], overall[MAX];

int main() {

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            scanf("%lld", &grid[i][k]);
            owe[i] += grid[i][k];
            gain[k] += grid[i][k];
        }
    }

    vector<int> positive, negative;
    for (int i = 0; i < N; i++) {
        if (gain[i] > owe[i]) {
            overall[i] = gain[i] - owe[i];
            positive.pb(i);
        } else {
            overall[i] = owe[i] - gain[i];
            negative.pb(i);
        }
    }

    int k = 0;
    for (int i = 0; i < positive.size(); i++) {
        int to = positive[i];
        for (; overall[to] && k < negative.size(); k++) {
            int from = negative[k];
            if (overall[from] <= overall[to]) {
                ans[from][to] = overall[from];
                overall[to] -= overall[from];
            } else {
                ans[from][to] = overall[to];
                overall[from] -= overall[to];
                overall[to] = 0;
                k--;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            printf("%lld ", ans[i][k]);
        } printf("\n");
    }

    return 0;
}