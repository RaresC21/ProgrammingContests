#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define mp make_pair
#define pb push_back
#define x first
#define y second

typedef pair<int, int> PT;
struct Seg {
    int x1, x2, y, pos;
    pair<int, int> slope;
    Seg(int x1, int x2, int y, int pos = 0) : x1(x1), x2(x2), y(y) {}
};
vector<Seg> v;

struct Event {
    pair<int, int> slope;
    int pos;
    int len;
    Event(pair<int, int> s, int pos, int len) : slope(s), pos(pos), len(len) {}
    bool operator < (const Event& other) const {
        lli LHS = 1LL * slope.y * other.slope.x;
        lli RHS = 1LL * slope.x * other.slope.y;
        if (LHS == RHS)
            return pos > other.pos;
        return LHS < RHS;
    }
};

int solve(PT pivot, int cur_len) {
    vector<Event> cur;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].y == pivot.y) continue;
        pair<int, int> s1 = mp(v[i].x1 - pivot.x, v[i].y - pivot.y);
        pair<int, int> s2 = mp(v[i].x2 - pivot.x, v[i].y - pivot.y);
        int len = v[i].x2 - v[i].x1;
        if (v[i].y > pivot.y) {
            cur.pb(Event(s1, 1, len));
            cur.pb(Event(s2, 2, len));
        } else {
            cur.pb(Event(mp(s1.x * (-1), s1.y * (-1)), 2, len));
            cur.pb(Event(mp(s2.x * (-1), s2.y * (-1)), 1, len));
        }
    }

    sort(cur.begin(), cur.end());
    reverse(cur.begin(), cur.end());

    int ans = cur_len;
    int oil = cur_len;
    for (int i = 0; i < cur.size(); i++) {
        if (cur[i].pos == 1) oil += cur[i].len;
        else oil -= cur[i].len;
        ans = max(ans, oil);
    }

    return ans;
}

int main() {

    int N;
    while (cin >> N) {
        v.clear();
        for (int i = 0; i < N; i++) {
            int x1, x2, yt; cin >> x1 >> x2 >> yt;
            if (x1 > x2) swap(x1, x2);
            v.pb(Seg(x1, x2, yt));
        }

        int ans = 0;
        for (Seg p : v) {
            int len = p.x2 - p.x1;
            ans = max(ans, solve(PT(p.x1, p.y), len));
            ans = max(ans, solve(PT(p.x2, p.y), len));
        }

        cout << ans << "\n";
    }
}