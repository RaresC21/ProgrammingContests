#include "bits/stdc++.h"
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

LL N, S;
LL happiness;
LL total;
struct Person {
    LL s, a, b;
    LL diff;
    Person(LL s, LL a, LL b) : s(s), a(a), b(b) {
        diff = b - a;
    }
    bool operator < (const Person& other) const {
        return diff < other.diff;
    }
};
vector<Person> v;
LL surplus;

LL f(LL type2) {
    LL slices = min(type2 * S, total);
    LL h = happiness;

    LL cur = 0;
    vector<pair<LL, LL> > extra;
    for (int i = SZ(v) - 1; i >= 0; i--) {
        if (cur >= slices) break;

        LL remain = slices - cur;
        LL change = min(v[i].s, remain);
        extra.push_back(MP(change, v[i].diff));

        h += v[i].diff * change;
        cur += v[i].s;
    }

    cur = surplus;
    for (int i = SZ(extra) - 1; i >= 0; i--) {
        if (cur <= 0) break;
        if (extra[i].B < 0) {
            LL change = min(extra[i].A, cur);
            h -= extra[i].B * change;
            cur -= extra[i].A;
        }
    }

    return h;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> S;

    FOR(i,0,N) {
        LL s, a, b; cin >> s >> a >> b;
        v.push_back(Person(s, a, b));
        happiness += s * a;
        total += s;
    }

    LL pizzas = (total + S - 1) / S;
    surplus = S * pizzas - total;

    sort(v.begin(), v.end());
    LL ans = happiness;

    LL minim = 1, maxim = pizzas;
    while (minim <= maxim) {
        LL m1 = minim + (maxim - minim) / 3;
        LL m2 = maxim - (maxim - minim) / 3;

        LL f1 = f(m1), f2 = f(m2);
        ans = max(ans, f1);
        ans = max(ans, f2);
        if (f1 < f2) {
            minim = m1 + 1;
        } else {
            maxim = m2 - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}