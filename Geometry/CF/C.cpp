#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define SZ(x) ((int)(x).size())
#define x first
#define y second
typedef pair<int, int> PT;

inline int cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

double polygon_area(const vector<PT>& p) {
    int N = SZ(p);
    int ans = 0;
    FOR(i,0,N) {
        int nxt = (i + 1) % N;
        ans += cross(p[i], p[nxt]);
    }
    return abs(ans * 0.5);
}

int main() {
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);

    int N; cin >> N;
    vector<PT> p(N);
    int xx, yy;
    FOR(i,0,N) {
        cin >> xx >> yy;
        p[i] = PT(xx, yy);
    }

    cout << fixed << setprecision(9) << polygon_area(p) << "\n";

    return 0;
}