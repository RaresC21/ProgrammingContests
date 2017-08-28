#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 1000006
#define INF 1000000000000000009
#define int lli

// returns g = gcd(a, b); finds x, y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}

int mine(int a, int b) {
    int x, y;
    int gcd = extended_euclid(a, b, x, y);

    if (gcd != 1) {
        return (a * b) / gcd;
    } else {
        int p = a * x; p = abs(p);
        int q = b * y; q = abs(q);
        return max(p, q);
    }
}

#undef int
int main() {
#define int lli

    int a, b; cin >> a >> b;
    if (a == 1 && b != 1) {
        cout << 2 << "\n";
    } else if (a != 1 && b == 1) {
        cout << 2 << "\n";
    } else if (a == 1 && b == 1) {
        cout << 1 << "\n";
    } else
        cout << mine(a, b) << "\n";

    return 0;
}

