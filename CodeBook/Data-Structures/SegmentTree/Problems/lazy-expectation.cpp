/*
    Codeforces: Round_448. E. 
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100005;

template<class T>
class SegTree {
private:
    int N;
    T ZERO;
    std::vector<T>& A;
    T tree[4 * MAX];
    T add[5 * MAX], mult[4 * MAX];

    void build(int node, int start, int end);
    void lazy_updateRange(int node, int start, int end, int l, int r, T add_val, T mult_val);
    T lazy_queryRange(int node, int start, int end, int l, int r);
    void push_lazy(int node, int start, int end);
    void update(int node, int start, int end, T add_val, T mult_val);

public:
    SegTree(vector<T>& a, T default_val) : A(a) {
        ZERO = default_val;
        N = A.size();
        build(1, 0, N - 1);
    }
    void update_range(int l, int r, T add_val, T mult_val);
    T query(int l, int r);
};

template<class T>
void SegTree<T>::update_range(int l, int r, T add_val, T mult_val) {
    lazy_updateRange(1, 0, N - 1, l, r, add_val, mult_val);
}

template<class T>
T SegTree<T>::query(int l, int r) {
    return lazy_queryRange(1, 0, N - 1, l, r);
}

template<class T>
void SegTree<T>::build(int node, int start, int end) {
    if (start == end) { // leaf node
        tree[node] = A[start];
        mult[node] = 1;
        add[node] = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
    mult[node] = 1;
    add[node] = 0;
}

// update current node with whatever is stored in lazy. Pass the lazy on to the children
template<class T>
void SegTree<T>::push_lazy(int node, int start, int end) {
    tree[node] *= mult[node];
    tree[node] += (end - start + 1) * add[node];
    if (start != end) {
        mult[node * 2] *= mult[node];
        mult[node * 2 + 1] *= mult[node];
        add[node * 2] *= mult[node];
        add[node * 2 + 1] *= mult[node];
        add[node * 2] += add[node];
        add[node * 2 + 1] += add[node];
    }
    mult[node] = 1.0;
    add[node] = 0.0;
}

// update current node normally with val passed in
// push this down lazily to children.
template<class T>
void SegTree<T>::update(int node, int start, int end, T add_val, T mult_val) {
    tree[node] *= mult_val;
    tree[node] += (end - start + 1) * add_val;

    if (start != end) {
        mult[node * 2] *= mult_val;
        mult[node * 2 + 1] *= mult_val;
        add[node * 2] *=  mult_val;
        add[node * 2 + 1] *= mult_val;
        add[node * 2] += add_val;
        add[node * 2 + 1] += add_val;
    }
}

template<class T>
void SegTree<T>::lazy_updateRange(int node, int start, int end, int l, int r, T add_val, T mult_val) {
    push_lazy(node, start, end);

    if (start > end || start > r || end < l)
        return;

    if (start >= l && end <= r) {
        update(node, start, end, add_val, mult_val);
        return;
    }

    int mid = (start + end) / 2;
    lazy_updateRange(node * 2, start, mid, l, r, add_val, mult_val);
    lazy_updateRange(node * 2 + 1, mid + 1, end, l, r, add_val, mult_val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

template<class T>
T SegTree<T>::lazy_queryRange(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l)
        return ZERO;

    push_lazy(node, start, end);

    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;
    T p1 = lazy_queryRange(2 * node, start, mid, l, r);
    T p2 = lazy_queryRange(2 * node + 1, mid + 1, end, l, r);

    return p1 + p2;
}

int main() {

    int N; cin >> N;
    int Q; cin >> Q;

    vector<double> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    SegTree<double> *seg = new SegTree<double>(v, 0.0);

    cout << fixed << setprecision(9);
    for (int q = 0; q < Q; q++) {
        int t; cin >> t;
        if (t == 1) {
            int r1, l1; cin >> l1 >> r1;
            int r2, l2; cin >> l2 >> r2;
            l1--, r1--;
            l2--, r2--;

            double left_ex = seg->query(l1, r1) / (r1 - l1 + 1);
            double right_ex = seg->query(l2, r2) / (r2 - l2 + 1);

            // multiply everyting by (r - l) / (r - l + 1)
            // add (expecation / (r - l + 1))
            seg->update_range(l1, r1, right_ex / (r1 - l1 + 1), (r1 - l1) * 1.0 / (r1 - l1 + 1));
            seg->update_range(l2, r2, left_ex / (r2 - l2 + 1), (r2 - l2) * 1.0 / (r2 - l2 + 1));
        } else {
            int l, r; cin >> l >> r;
            l--, r--;

            cout << seg->query(l, r) << "\n";
        }
    }

    return 0;
}
