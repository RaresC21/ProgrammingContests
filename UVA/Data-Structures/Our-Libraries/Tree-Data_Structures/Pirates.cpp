#include <bits/stdc++.h>
using namespace std;

#define MAX 2030006

class SegmentTree {
private:
    int N;
    vector<int> A;
    int tree[MAX * 2], lazy[2 * MAX];

    int op(int a, int b) {
	return a + b;
    }
    
    void build(int node, int l, int r) {
	if (l == r) {
	    tree[node] = A[l];
	    return;
	}
	int mid = (l + r) / 2;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);

	tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    void local_update(int node, int val, int len) {
	if (val == 1)
	    tree[node] = len;
	else if (val == 2)
	    tree[node] = 0;
	else if (val == 3)
	    tree[node] = len - tree[node];
    }

    void update_lazy(int node, int val) {
	if (val == 3) {
	    if (lazy[node * 2] == 1) lazy[node * 2] = 2;
	    else if (lazy[node * 2] == 2) lazy[node * 2] = 1;
	    else if (lazy[node * 2] == 3) lazy[node * 2] = 0;
	    else lazy[node * 2] = 3;
	    
	    if (lazy[node * 2 + 1] == 1) lazy[node * 2 + 1] = 2;
	    else if (lazy[node * 2 + 1] == 2) lazy[node * 2 + 1] = 1;
	    else if (lazy[node * 2 + 1] == 3) lazy[node * 2 + 1] = 0;
	    else lazy[node * 2 + 1] = 3;
	} else {
	    lazy[node * 2] = lazy[node * 2 + 1] = val;
	}
    }
    
    void update(int node, int start_, int end_, int l, int r, int val) {
	if (lazy[node] != 0) {
	    local_update(node, lazy[node], end_ - start_ + 1);
	    if (start_ != end_)
		update_lazy(node, lazy[node]);
	    lazy[node] = 0;
	}
		
	if (start_ > end_ || start_ > r || end_ < l) return;
	if (start_ >= l && end_ <= r) {
	    local_update(node, val, end_ - start_ + 1);
	    if (start_ != end_) {
		update_lazy(node, val);
	    }
	    return;
	}

	int mid = (start_ + end_) / 2;
	update(node * 2, start_, mid, l, r, val);
	update(node * 2 + 1, mid + 1, end_, l, r, val);
	
	tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int start_, int end_, int l, int r) {
	if (start_ > end_ || start_ > r || end_ < l)
	    return 0;
	
	if (lazy[node] != 0) {
	    local_update(node, lazy[node], end_ - start_ + 1);
	    if (start_ != end_) {
		update_lazy(node, lazy[node]);
	    }
	    lazy[node] = 0;
	}
	
	if (start_ >= l && end_ <= r) {
	    return tree[node];
	}

	int mid = (start_ + end_) / 2;
	int ql = query(node * 2, start_, mid, l, r);
	int qr = query(node * 2 + 1, mid + 1, end_, l, r);

	return op(ql, qr);
    }
    
    
public:
    SegmentTree(vector<int>& a) : A(a) {
	memset(lazy, 0, sizeof(lazy));
	memset(tree, 0, sizeof(tree));
	N = A.size();
	
	build(1, 0, N - 1);
    }

    int query(int l, int r) {
	return query(1, 0, N - 1, l, r);
    }

    void update(int l, int r, int val) {
	update(1, 0, N - 1, l, r, val);
    }
};

int main() {

    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
	int M; cin >> M;
	vector<int> v;
	for (int i = 0; i < M; i++) {
	    int K; cin >> K;
	    string cur; cin >> cur;
	    for (int k = 0; k < K; k++) {
		for (int j = 0; j < cur.size(); j++)
		    v.push_back(cur[j] - '0');
	    }
	}

	SegmentTree *seg = new SegmentTree(v);
	
	printf("Case %d:\n", t);
	
	int Q; cin >> Q;
	int qq = 1;
	for (int q = 1; q <= Q; q++) {
	    char t; cin >> t;
	    int a, b; cin >> a >> b;
	    if (t == 'F') {
		seg->update(a, b, 1);
	    } else if (t == 'E') {
		seg->update(a, b, 2);
	    } else if (t == 'I') {
		seg->update(a, b, 3);
	    } else if (t == 'S') {
		cout << "Q" << qq << ": " << seg->query(a, b) << "\n";
		qq++;
	    }
	}

	delete seg;
    }
    
    return 0;
}
