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
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2 + 1] += lazy[node];
            lazy[node * 2] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// update current node normally with val passed in
// push this down lazily to children.
void SegTree::update(int node, int start, int end, int val) {
    tree[node] += (end - start + 1) * val;

    if (start != end) {
        lazy[node * 2] += val;
        lazy[node * 2 + 1] += val;
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