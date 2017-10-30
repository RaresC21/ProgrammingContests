/*
   /home/rares/Documents/
   p.cpp
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

pii flip(pii frac) {
    return MP(frac.B, frac.A);
}

pii add(pii p, pii q) {
    return MP(p.A * q.B + q.A * p.B, p.B * q.B);
}

pii add (int n, pii frac) {
    return MP(frac.B * n + frac.A, frac.B);
}

pii sub(pii p, pii q) {
    q.A *= -1;
    return add(p, q);
}

pii mult(pii p, pii q) {
    return MP(p.A * q.A, p.B * q.B);
}

pii divide(pii p, pii q) {
    return mult(p, flip(q));
}

pii eval(const VI& v, int pos) {
    if (pos == SZ(v)-1) return MP(v[pos], 1);
    pii cur = eval(v, pos + 1);
    return add(v[pos], flip(cur));
}

int whole(pii& p) {
    int d = p.A / p.B;
    p.A %= p.B;
    return d;
}

VI compute(pii p) {
    VI ans;
    while (p.A != 0 && p.B != 0) {
        ans.push_back(whole(p));
        p = flip(p);
    }
    return ans;
}

#undef int
int main() {
#define int long long
    ios_base::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    VI a(N);
    FOR(i,0,N) {
        cin >> a[i];
    }

    auto n1 = eval(a, 0);

    VI b(M);
    FOR(i,0,M) {
        cin >> b[i];
    }

    auto n2 = eval(b, 0);

    auto v1 = add(n1, n2);
    auto v2 = sub(n1, n2);
    auto v3 = mult(n1, n2);
    auto v4 = divide(n1, n2);

    VI a1 = compute(v1);
    for (int a : a1) cout << a << " "; cout << "\n";

    VI a2 = compute(v2);
    for (int a : a2) cout << a << " "; cout << "\n";

    VI a3 = compute(v3);
    for (int a : a3) cout << a << " "; cout << "\n";

    VI a4 = compute(v4);
    for (int a : a4) cout << a << " "; cout << "\n";

    return 0;
}