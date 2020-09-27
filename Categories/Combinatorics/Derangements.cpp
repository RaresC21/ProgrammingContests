/*
    Codeforces Educational Round 32.

    Let's call a permutation an almost identity permutation iff there exist at
    least n - k indices i (1 ≤ i ≤ n) such that p_i = i.
    Your task is to count the number of almost identity permutations for given numbers n and k.

    Constraints:
        N <= 1000
        K <= 4
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX = 1003;
LL fact[5];
LL comb[MAX][5];
LL derangements[5];

LL binom(int n, int r) {
    if (comb[n][r] != -1) return comb[n][r];

    LL ans = 1;
    for (int i = n; i > n - r; i--) {
        ans *= i;
        ans /= (n - i + 1);
    }
    return comb[n][r] = ans;
}

void init() {
    memset(comb, -1, sizeof(comb));
    fact[0] = 1;
    for (int i = 1; i < 5; i++)
        fact[i] = fact[i - 1] * i;

    // derangements -- these could be brute forced.
    for (int j = 1; j <= 4; j++) {
        for (int a = 0; a <= j; a++) {
            LL cur = binom(j, a) * fact[j - a];
            int sgn = (a % 2 == 0) ? 1 : -1;
            derangements[j] += cur * sgn;
        }
    }
}

int main() {

    init();

    int N, K; cin >> N >> K;

    LL ans = 1;
    for (int j = 1; j <= K; j++) {
        ans += binom(N, j) * derangements[j];
    }

    cout << ans << "\n";

    return 0;
}