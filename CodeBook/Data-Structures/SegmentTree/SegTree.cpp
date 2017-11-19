const int MAX = 100005;

class SegTree {
private:

    int N;
    std::vector<int>& A;
    int tree[2 * MAX], lazy[2 * MAX];
    int (*op) (int a, int b);

    void build(int node, int start, int end);
    void update(int node, int start, int end, int indx, int val);
    int query(int node, int start, int end, int l, int r, int default_val);

public:

    SegTree(std::vector<int>& a, int (*op)(int a, int b)) : A(a), op(op) {
        N = A.size();
        build(1, 0, N - 1);
    }

    void update(int indx, int val) {
        update(1, 0, N - 1, indx, val);
    }

    int query(int l, int r, int default_val) {
        return query(1, 0, N - 1, l, r, default_val);
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

    tree[node] = (*op)(tree[2 * node], tree[2 * node + 1]);
}

void SegTree::update(int node, int start, int end, int indx, int val) {
    if (start == end) {
        A[indx] = (*op)(A[indx], val);
        tree[node] = (*op)(tree[node], val);
        return;
    }

    int mid = (start + end) / 2;
    if (start <= mid && indx <= mid)
        update(2 * node, start, mid, indx, val);
    else
        update(2 * node + 1, mid + 1, end, indx, val);

    tree[node] = (*op)(tree[node * 2], tree[node * 2 + 1]);
}

int SegTree::query(int node, int start, int end, int l, int r, int default_val) {
    if (r < start || l > end)
        return default_val;

    if (l <= start && r >= end) // completely within range.
        return tree[node];

    //partially in range, partially out.
    int mid = (start + end) / 2;
    int p1 = query(node * 2, start, mid, l, r, default_val);
    int p2 = query(node * 2 + 1, mid + 1, end, l, r, default_val);

    return (*op)(p1, p2);
}