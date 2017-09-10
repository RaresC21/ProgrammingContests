#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define mp make_pair
#define pb push_back
#define int lli
#define MAX 1000006

class BitTree {
public:
    int N;
    int BIT[MAX];
    BitTree(int N) : N(N) {
        memset(BIT, 0, sizeof(BIT));
    }
    void update(int x, int val) {
        for(; x <= N; x += x & -x) BIT[x] += val;
    }
    int query(int x) {
        int sum = 0;
        for(; x > 0; x -= x & -x) sum += BIT[x];
        return sum;
    }
};

struct Query {
    int l, d, r, u;
    int LD, LU, RD, RU;
    int XX1, XX2, YY1, YY2;
    Query(int l, int d, int r, int u) : l(l), d(d), r(r), u(u) {}
};

struct PT {
    int x, y;
    PT (int x, int y) : x(x), y(y) {}
};

int less_x[MAX], less_y[MAX];
vector<PT> v, vx, vy;
vector<Query> query;
int point_cnt[MAX];
int N, Q;

inline bool x_cmp(const PT& a, const PT& b) {
    return a.x < b.x;
}

inline bool cmp_overlap_x(const pair<PT, pair<int, pair<int, int > > >& a, const pair<PT, pair<int, pair<int, int > > >& b) {
    if (a.first.x == b.first.x) return a.second.second.first < b.second.second.first;
    return a.first.x < b.first.x;
}

inline bool y_cmp(const PT& a, const PT& b) {
    return a.y < b.y;
}

void overlap() {
    vector<pair<PT, pair<int, pair<int, int> > > > event;
    for (PT p : v) {
        event.pb(mp(p, mp(0, mp(0, -1))));
    }
    int cnt = 0;
    for (Query& q : query) {
        q.LD = cnt;
        event.pb(mp(PT(-1,0), mp(q.d - 1, mp(-1, cnt)))); // bottom left
        event.pb(mp(PT(q.l - 1, 0), mp(q.d - 1, mp(2, cnt++))));

        q.LU = cnt;
        event.pb(mp(PT(-1, q.u + 1), mp(N, mp(-1, cnt))));  // top left
        event.pb(mp(PT(q.l - 1, q.u + 1), mp(N, mp(2, cnt++))));

        q.RD = cnt;
        event.pb(mp(PT(q.r + 1, 0), mp(q.d - 1, mp(-1, cnt))));    // bottom right
        event.pb(mp(PT(N + 1, 0), mp(q.d - 1, mp(2, cnt++))));

        q.RU = cnt;
        event.pb(mp(PT(q.r + 1, q.u + 1), mp(N, mp(-1, cnt))));    // top right
        event.pb(mp(PT(N + 1, q.u + 1), mp(N, mp(2, cnt++))));
    }

    sort(event.begin(), event.end(), cmp_overlap_x);
    BitTree *bit = new BitTree(MAX - 1);
    for (int i = 0; i < event.size(); i++) {
        if (event[i].second.second.first == 0)
            bit->update(event[i].first.y, 1);
        else if (event[i].second.second.first == -1) {
            point_cnt[event[i].second.second.second] = bit->query(event[i].first.y + event[i].second.first) - bit->query(event[i].first.y - 1);
        }
        else {
            int indx = event[i].second.second.second;
            point_cnt[indx] = bit->query(event[i].first.y + event[i].second.first) - bit->query(event[i].first.y - 1) - point_cnt[indx];
        }
    }
}

void to_left() {
    vector<pair<int, pair<int, int > > > event;
    for (auto p : v)
        event.pb(mp(p.x, mp(1, -1)));
    for (auto q : query) {
        event.pb(mp(q.l - 1, mp(2, q.XX1)));
        event.pb(mp(q.r, mp(2, q.XX2)));
    }
    sort(event.begin(), event.end());
    int amnt = 0;
    for (int i = 0; i < event.size(); i++) {
        if (event[i].second.first == 1)
            amnt++;
        else
            less_x[event[i].second.second] = amnt;
    }
}

void to_right() {
    vector<pair<int, pair<int, int > > > event;
    for (auto p : v)
        event.pb(mp(p.y, mp(1, -1)));
    for (auto q : query) {
        event.pb(mp(q.d - 1, mp(2, q.YY1)));
        event.pb(mp(q.u, mp(2, q.YY2)));
    }
    sort(event.begin(), event.end());
    int amnt = 0;
    for (int i = 0; i < event.size(); i++) {
        if (event[i].second.first == 1)
            amnt++;
        else
            less_y[event[i].second.second] = amnt;
    }
}

#undef int
int main() {
#define int lli

    scanf("%lld%lld", &N, &Q);
    for (int x = 1; x <= N; x++) {
        int y; scanf("%lld", &y);
        v.push_back(PT(x, y));
    }

    lli ans = 0;
    int cnt = 0;
    for (int i = 0; i < Q; i++) {
        int l, d, r, u; scanf("%lld%lld%lld%lld", &l, &d, &r, &u);
        query.pb(Query(l, d, r, u));
        query.back().XX1 = cnt++; query.back().XX2 = cnt++; query.back().YY1 = cnt++; query.back().YY2 = cnt++;
    }
    overlap();
    to_left(), to_right();

    for (int i = 0; i < Q; i++) {
        int l = query[i].l, r = query[i].r, d = query[i].d, u = query[i].u;

        lli LL = less_x[query[i].XX1]; LL = (LL * (LL - 1)) / 2;
        lli DD = less_y[query[i].YY1]; DD = (DD * (DD - 1)) / 2;
        lli RR = N - less_x[query[i].XX2]; RR = (RR * (RR - 1)) / 2;
        lli UU = N - less_y[query[i].YY2]; UU = (UU * (UU - 1)) / 2;

        lli LD = point_cnt[query[i].LD]; LD = (LD * (LD - 1)) / 2;
        lli LU = point_cnt[query[i].LU]; LU = (LU * (LU - 1)) / 2;
        lli RD = point_cnt[query[i].RD]; RD = (RD * (RD - 1)) / 2;
        lli RU = point_cnt[query[i].RU]; RU = (RU * (RU - 1)) / 2;

        lli ans = N * (N - 1) / 2 - (LL + DD + RR + UU - LD - LU - RD - RU);
        printf("%lld\n", ans);
    }

    return 0;
}