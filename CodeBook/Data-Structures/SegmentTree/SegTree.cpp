const int MAX = 100005;

template<class T>
class SegTree {
private:

    int N;
    std::vector<T>& A;
    T tree[4 * MAX];

    void build(int node, int start, int end);
    void update(int node, int start, int end, int indx, T val);
    T query(int node, int start, int end, int l, int r, T default_val);
    T merge (const T& a, const T& b);

public:

    SegTree(std::vector<T>& a) : A(a) {
        N = A.size();
        build(1, 0, N - 1);
    }

    void update(int indx, T val) {
        update(1, 0, N - 1, indx, val);
    }

    T query(int l, int r, T default_val) {
        return query(1, 0, N - 1, l, r, default_val);
    }
};

template<class T> // currently supports range minimum query.
T SegTree<T>::merge(const T& a,  const T& b) {
    if (a < b) return a;
    return b;
}

template<class T>
void SegTree<T>::build(int node, int start, int end) {
    if (start == end) { // leaf node
        tree[node] = A[start];
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    tree[node] = (*merge)(tree[2 * node], tree[2 * node + 1]);
}

template<class T>
void SegTree<T>::update(int node, int start, int end, int indx, T val) {
    if (start == end) {
        A[indx] = (*merge)(A[indx], val);
        tree[node] = (*merge)(tree[node], val);
        return;
    }

    int mid = (start + end) / 2;
    if (start <= mid && indx <= mid)
        update(2 * node, start, mid, indx, val);
    else
        update(2 * node + 1, mid + 1, end, indx, val);

    tree[node] = (*merge)(tree[node * 2], tree[node * 2 + 1]);
}

template<class T>
T SegTree<T>::query(int node, int start, int end, int l, int r, T default_val) {
    if (r < start || l > end)
        return default_val;

    if (l <= start && r >= end) // completely within range.
        return tree[node];

    //partially in range, partially out.
    int mid = (start + end) / 2;
    T p1 = query(node * 2, start, mid, l, r, default_val);
    T   p2 = query(node * 2 + 1, mid + 1, end, l, r, default_val);

    return (*merge)(p1, p2);
}
