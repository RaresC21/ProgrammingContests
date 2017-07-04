#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int h[MAX];
int maxim[MAX];

int main() {

    int N; cin >> N;
    for (int i = 0; i < N; i++)
	cin >> h[i];

    sort(h, h + N);

    maxim[0]  = h[0];
    for (int i = 1; i < N; i++)
	maxim[i] = max(maxim[i - 1], h[i]);

    int ans = N;
    int cur = 0;
    for (int i = N - 1; i >= 0; i--) {
	ans = min(ans, maxim[i] + cur);
	cur++;
    }

    cout << ans << "\n";
    
    return 0;
}
