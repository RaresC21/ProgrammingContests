#include <bits/stdc++.h>
using namespace std;

const int MAX = 100005;
int Height;

class SegTree {

private:

    int N;
    std::vector<int>& A;
    int tree[5 * MAX];
    void build(int node, int start, int end, bool is_or);
    void update(int node, int start, int end, int indx, int val, bool is_or);

public:

    SegTree(std::vector<int>& a) : A(a) {
        N = A.size();
        build(1, 0, N-1, Height % 2);
    }

    void update(int indx, int val) {
        update(1, 0, N-1, indx, val, Height % 2);
    }

    int query() {
        return tree[1];
    }
};

void SegTree::build(int node, int start, int end, bool is_or) {
    if (start == end) {
        tree[node] = A[start];
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid, !is_or);
    build(2 * node + 1, mid + 1, end, !is_or);

    if (is_or)
        tree[node] = tree[2 * node] | tree[2 * node + 1];
    else
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

void SegTree::update(int node, int start, int end, int indx, int val, bool is_or) {
    if (start == end) {
        A[indx] = val;
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;
    if (start <= mid && indx <= mid)
        update(2 * node, start, mid, indx, val, !is_or);
    else
        update(2 * node + 1, mid + 1, end, indx, val, !is_or);

    if (is_or) tree[node] = tree[node * 2] | tree[node * 2 + 1];
    else tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
}

int main() {

    cin >> Height;
    int Q; cin >> Q;
    vector<int> v((1 << Height));
    for (int i = 0; i < (1 << Height); i++) {
        cin >> v[i];
    }

    SegTree * seg = new SegTree(v);

    while (Q--) {
        int x, val; cin >> x >> val;
        x--;
        seg->update(x, val);
        cout << seg->query() << "\n";
    }

    return 0;
}