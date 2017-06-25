#include <bits/stdc++.h>
using namespace std;

#define MAX 100005

class SegmentTree {
private:
    int N;
    int tree[MAX * 4];
    vector<int> A;
    int (*op) (int a, int b);

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = A[l];
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        tree[node] = (*op)(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int start_, int end_, int l, int r, const int LIMIT) {
        if (start_ > r || end_ < l) return LIMIT;
        if (start_ >= l && end_ <= r)
            return tree[node];

        int mid = (start_ + end_) / 2;
        int ql = query(node * 2, start_, mid, l, r, LIMIT);
        int qr = query(node * 2 + 1, mid + 1, end_, l, r, LIMIT);

        return (*op)(ql, qr);
    }

public:
    SegmentTree(vector<int>& a, int (*op) (int a, int b)) : A(a), op(op) {
        N = a.size();
        build(1, 1, N);
    }

    ~SegmentTree() {
        A.clear();
    }

    int query(int l, int r, const int LIMIT) {
        return query(1, 1, N, l, r, LIMIT);
    }
};

#define pb push_back
#define mp make_pair

int maxim(int a, int b) {
    if (a > b) return a;
    return b;
}

int minim(int a, int b) {
    if (a < b) return a;
    return b;
}

int main() {

    int N, K; cin >> N >> K;
    vector<int> height(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> height[i];
    }

    SegmentTree *max_seg = new SegmentTree(height, maxim);
    SegmentTree *min_seg = new SegmentTree(height, minim);

    int k = 1;
    int best = 0;
    vector<pair<int, int> > ans;
    for (int i = 1; i <= N; i++) {
        while (k <= N && max_seg->query(i, k, 0) - min_seg->query(i, k, MAX * 10) <= K) {
            k++;
        }

        if (k - i > best) {
            best = k - i;
            ans.clear();
            ans.pb(mp(i, k - 1));
        } else if (k - i == best) {
            ans.pb(mp(i, k - 1));
        }
    }

    cout << ans[0].second - ans[0].first + 1 << " " << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    delete min_seg;
    delete max_seg;

    return 0;
}