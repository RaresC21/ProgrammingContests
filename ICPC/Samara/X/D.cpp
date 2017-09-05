#include <bits/stdc++.h>
using namespace std;


int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {


    int N, X; cin >> N >> X;

    int g; cin >> g;
    for (int i = 1; i < N; i++) {
        int x; cin >> x;
        g = gcd(g, x);
    }

    if (X % g == 0)  {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}