#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back
#define A first
#define B second
#define INF 1000000011

#define MAX 503
int P[MAX][MAX]; // container for 2D grid

struct Segtree2d {
    int T[4 * MAX * MAX]; // store maximum
    int S[4 * MAX * MAX]; // store minimum
    int n, m;

    // initialize and construct segment tree
    Segtree2d(int n, int m) {
        this -> n = n;
        this -> m = m;
        build(1, 1, 1, n, m);
    }

    // build a 2D segment tree from data [ (a1, b1), (a2, b2) ]
    // Time: O(n logn)
    void build(int node, int a1, int b1, int a2, int b2) {
        // out of range
        if (a1 > a2 || b1 > b2) {
            S[node] = INF;
            T[node] = -INF;
            return;
        }

        // if it is only a single index, assign value to node
        if (a1 == a2 && b1 == b2) {
            T[node] = S[node] = P[a1][b1];
            return;
        }

        // split the tree into four segments
        build(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2 );
        build(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2);
        build(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2);
        build(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2);

        T[node] = max (T[4*node - 2], max (T[4*node - 1], max (T[4*node + 0], T[4*node + 1])));
        S[node] = min (S[4*node - 2], min (S[4*node - 1], min (S[4*node + 0], S[4*node + 1])));
    }

    // helper function for query(int, int, int, int);
    pair<int, int> query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
        // if we out of range, return dummy
        if (x1 > a2 || y1 > b2 || x2 < a1 || y2 < b1 || a1 > a2 || b1 > b2)
            return make_pair(-INF, INF);

        // if it is within range, return the node
        if (x1 <= a1 && y1 <= b1 && a2 <= x2 && b2 <= y2)
            return make_pair(T[node], S[node]);

        // split into four segments
        int mx = -INF, mn = INF;
        pair <int, int> p1, p2, p3, p4;
        p1 = query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2);
        p2 = query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2);
        p3 = query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2);
        p4 = query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2);

        mx = max (p1.first, max (p2.first, max (p3.first, p4.first)));
        mn = min (p1.second, min (p2.second, min (p3.second, p4.second)));
        return make_pair(mx, mn);
    }

    // query from range [ (x1, y1), (x2, y2) ]
    // Time: O(logn)
    pair<int, int> query(int x1, int y1, int x2, int y2) {
        return query(1, 1, 1, n, m, x1, y1, x2, y2);
    }

    pair<int, int> update(int node, int a1, int b1, int a2, int b2, int x, int y, int val) {
        if (a1 > a2 || b1 > b2) {
            return make_pair(-INF, INF);
        }
        if (x > a2 || y > b2 || x < a1 || y < b1) {
            return make_pair(T[node], S[node]);
        }
        if (x == a1 && y == b1 && x == a2 && y == b2) {
            T[node] = val;
            S[node] = val;
            return make_pair(T[node], S[node]);
        }

        pair <int, int> p1, p2, p3, p4;
        p1 = update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x, y, val);
        p2 = update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x, y, val);
        p3 = update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x, y, val);
        p4 = update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x, y, val);
        T[node] = max(p1.first, max(p2.first, max(p3.first, p4.first)));
        S[node] = min(p1.second, min(p2.second, min(p3.second, p4.second)));
        return make_pair(T[node], S[node]);
    }

    pair<int, int> update(int x, int y, int value) {
        return update(1, 1, 1, n, m, x, y, value);
    }
};