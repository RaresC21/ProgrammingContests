/*
The Ox axis of coordinates has n segments, the i-th segment starts in position l_i and ends in position r_i (we will mark it as [li, ri]). 
Your task is to process m queries, each consists of number cnt_i and a set of cnt_i coordinates of points located on the Ox axis. 
The answer to the query is the number of segments, such that each of them contains at least one point from the query. 
Segment [l, r] contains point q, if l ≤ q ≤ r.

Codeforces Round 216 E.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000006;

class SegTree {

private:

    int N;
    vector<vector<int> > A;
    vector<int> tree[4 * MAX];
    inline void merge_vec(vector<int>& res, const vector<int>& a, const vector<int>& b) {
        merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    }

    inline void build(int node, int start, int end);
    inline int query(int node, int start, int end, int l, int r, int K, int default_val);

public:

    SegTree(vector<vector<int> > a) : A(a) {
        N = A.size();
        build(1, 0, N - 1);
    }

    inline int query(int l, int r, int K, int default_val = 0) {
        return query(1, 0, N - 1, l, r, K, default_val);
    }
};

inline void SegTree::build(int node, int start, int end) {
    if (start == end) { // leaf node
        tree[node] = A[start];
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    merge_vec(tree[node], tree[node * 2], tree[node * 2 + 1]);
}

inline int SegTree::query(int node, int start, int end, int l, int r, int K, int default_val) {
    if (r < start || l > end)
        return default_val;

    if (l <= start && r >= end) { // completely within range.
        int total = tree[node].size();
        int less_than = upper_bound(tree[node].begin(), tree[node].end(), K) - tree[node].begin();
        return total - less_than;
    }

    //partially in range, partially out.
    int mid = (start + end) / 2;
    int p1 = query(node * 2, start, mid, l, r, K, default_val);
    int p2 = query(node * 2 + 1, mid + 1, end, l, r, K, default_val);

    return p1 + p2;
}

int main() {

    int N; scanf("%d", &N);
    int Q; scanf("%d", &Q);
    vector<vector<int> > v(MAX);
    for (int i = 0; i < N; i++) {
        int a, b; scanf("%d %d", &a, &b);
        v[b].push_back(a);
    }

    for (int i = 1; i < MAX; i++) 
        sort(v[i].begin(), v[i].end());

    SegTree* seg = new SegTree(v);

    int x;
    while (Q--) {
        int M; scanf("%d", &M);
        int ans = N;
        int last = 0;
        for (int i = 0; i < M; i++) {
            scanf("%d", &x);
            if (last + 1 <= x - 1) {
                ans -= seg->query(last + 1, x - 1, last);
            }
            last = x;
        }
        ans -= seg->query(last + 1, MAX - 1, last);

        printf("%d\n", ans);
    }

    return 0;
}