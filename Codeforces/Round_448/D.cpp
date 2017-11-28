#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 30;
int inverse[1000006];
int fact[1000006], inv_fact[1000006];
int cnt[MAX], original[MAX];

inline int mult(int a, int b) {
    long long x = a * 1LL * b;
    return x % MOD;
}

inline int add(int a, int b) {
    int x = a + b;
    if (x > MOD) x -= MOD;
    return x;
}

inline int exp(int a, int x) {
    int ans = 1;
    while (x) {
        if (x & 1) {
            ans = mult(ans, a);
        }
        x >>= 1;
        a = mult(a, a);
    }
    return ans;
}

inline int inv(int a) {
    if (a == 0) return 1;
    return exp(a, MOD - 2);
}

int solve(const string& s, const string& a) {
    vector<int> cnt(MAX);
    int prod = 1;
    int amnt = a.size();

    for (int i = 0; i < a.size(); i++) {
        cnt[a[i] - 'a'] ++;
        prod = mult(prod, i + 1);
    }

    for (int i = 0; i < MAX; i++) {
        if (cnt[i] != 0) prod = mult(prod, inv_fact[cnt[i]]);
    }

    int ans = 0;
    for (int i = 0; i < s.size(); i++) { // first difference at index i
        for (int k = 0; k < s[i] - 'a'; k++) { // put something smaller
            if (cnt[k] == 0) continue;
            int cur = mult(prod, inverse[amnt]);
            cur = mult(cur, cnt[k]);

            ans = add(ans, cur);
        }

        if (cnt[s[i] - 'a'] == 0) {
             break;
        }

        prod = mult(prod, inverse[amnt]);
        prod = mult(prod, cnt[s[i] - 'a']);

        cnt[s[i] - 'a'] --;
        amnt--;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    memset(inverse, -1, sizeof(inverse));
    fact[0] = 1;
    inv_fact[0] = 1;
    for (int i = 1; i < 1000006; i++) {
        fact[i] = mult(fact[i - 1], i);
        inv_fact[i] = inv(fact[i]);
    }
    for (int i = 1; i < 1000006; i++) {
        inverse[i] = inv(i);
    }

    string a, b; cin >> a >> b;

    cout << (solve(b, a) - solve(a, a) - 1 + MOD) % MOD << "\n";

    return 0;
}
