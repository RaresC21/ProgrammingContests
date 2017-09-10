#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {

    int N; cin >> N;
    int b = N - 1;
    int ans = 0;
    for (int a = 1; a < N; a++) {
        if (a < b && gcd(a, b) == 1) {
            ans = a;
        }
        b--;
    }

    cout << ans << " " << N - ans << "\n";

    return 0;
}