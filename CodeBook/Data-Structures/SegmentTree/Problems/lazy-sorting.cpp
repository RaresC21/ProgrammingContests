/* 
    Codeforces: Round 312. E
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 100005;
class SegTree {   
private:
    
    int N;
    std::vector<int>& A;
    int tree[5 * MAX], lazy[5 * MAX];
    
    void build(int node, int start, int end);
    void lazy_updateRange(int node, int start, int end, int l, int r, int val);
    int lazy_queryRange(int node, int start, int end, int l, int r);
    void push_lazy(int node, int start, int end);
    void update(int node, int start, int end, int val);
    
public:
    
    SegTree(std::vector<int>& a) : A(a) {
        N = A.size();
        build(1, 0, N - 1);
    }
    
    void update_range(int l, int r, int val) {
        lazy_updateRange(1, 0, N - 1, l, r, val);
    }
    int query(int l, int r) {
        return lazy_queryRange(1, 0, N - 1, l, r);
    }
};

void SegTree::build(int node, int start, int end) {
    if (start == end) { // leaf node
        tree[node] = A[start];
        return;
    }
    
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// update current node with whatever is stored in lazy. Pass the lazy on to the children
void SegTree::push_lazy(int node, int start, int end) {
    if (lazy[node]) {
        if (lazy[node] == -1)
            tree[node] = 0;
        else
            tree[node] = (end - start + 1);
        if (start != end) {
            lazy[node * 2 + 1] = lazy[node];
            lazy[node * 2] = lazy[node];
        }
        lazy[node] = 0;
    }
}

// update current node normally with val passed in
// push this down lazily to children.
void SegTree::update(int node, int start, int end, int val) {
    if (val == -1) tree[node] = 0;
    else tree[node] = (end - start + 1) * val;

    if (start != end) {
        lazy[node * 2] = val;
        lazy[node * 2 + 1] = val;
    }
}

void SegTree::lazy_updateRange(int node, int start, int end, int l, int r, int val) {
    push_lazy(node, start, end);
    
    if (start > end || start > r || end < l)
        return;

    if (start >= l && end <= r) {
        update(node, start, end, val);
        return;
    }
    
    int mid = (start + end) / 2;
    lazy_updateRange(node * 2, start, mid, l, r, val);
    lazy_updateRange(node * 2 + 1, mid + 1, end, l, r, val);
    
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int SegTree::lazy_queryRange(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l)
        return 0;
    
    push_lazy(node, start, end);
    
    if (start >= l && end <= r)
        return tree[node];
    
    int mid = (start + end) / 2;
    int p1 = lazy_queryRange(2 * node, start, mid, l, r);
    int p2 = lazy_queryRange(2 * node + 1, mid + 1, end, l, r);
    
    return p1 + p2;
}


int main() {
    ios_base::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    string s; cin >> s;

    vector<int> v[26];
    vector<SegTree> seg;
    for (int i = 0; i < 26; i++) {
        vector<int> v(N);
        for (int k = 0; k < N; k++) {
            if (s[k] == i + 'a')
                v[k] = 1;
        }
        seg.push_back(SegTree(v));
    }

    while (Q--) {
        int a, b, t; cin >> a >> b >> t;
        a--, b--;
        if (t == 1) {
            vector<int> amnt(26);
            for (int i = 0; i < 26; i++) {
                amnt[i] = seg[i].query(a, b);
            }
            int total = a;
            for (int i = 0; i < 26; i++) {
                if (total != a)
                    seg[i].update_range(a, total - 1, -1);
                if (total + amnt[i] <= b)
                    seg[i].update_range(total + amnt[i], b, -1);
                if (amnt[i] != 0) {
                    seg[i].update_range(total, total + amnt[i] - 1, 1);
                }
                total += amnt[i];
            }

        } else {    
            vector<int> amnt(26);
            for (int i = 0; i < 26; i++) {
                amnt[i] = seg[i].query(a, b);
            }
            int total = a;
            for (int i = 25; i >= 0; i--) {
                if (total != a) {
                    seg[i].update_range(a, total - 1, -1);
                }
                if (total + amnt[i] <= b) {
                    seg[i].update_range(total + amnt[i], b, -1);
                }
                if (amnt[i] != 0) {
                    seg[i].update_range(total, total + amnt[i] - 1, 1);
                }
                total += amnt[i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < 26; k++) {
            if (seg[k].query(i, i)) {
                cout << char(k + 'a');
            }
        }
    }

    cout << "\n";

    return 0;
}