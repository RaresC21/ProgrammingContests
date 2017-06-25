#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
long long a[MAX];
map<long long, int> met;

int main() {

    long long N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    sort(a, a + N);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (!met[a[i]]) {
            met[a[i]] = true;
            ans ++;
            met[a[i] * K] = true;
        }
    }

    cout << ans << "\n";

    return 0;
}