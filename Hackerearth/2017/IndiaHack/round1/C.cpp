#include <bits/stdc++.h>
using namespace std;

#define MAX 400005
#define int long long
vector<long long> sum_left, sum_right, val;

class SegmentTree {
private:
    int N;
    vector<long long> A;
    long long tree[MAX * 2];
    
    long long op(long long a, long long b) {
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

    int query(int node, int start_, int end_, int l, int r) {
	if (r < start_ || l > end_) return 0;
	if (l <= start_ && r >= end_) {
	    return tree[node];
	}

	int mid = (start_ + end_) / 2;
	long long ql = query(node * 2, start_, mid, l, r);
	long long qr = query(node * 2 + 1, mid + 1, end_, l, r);
	return op(ql, qr);
    }

    void update(int node, int start_, int end_, long long val, int indx) {
	if (start_ == end_) {
	    A[indx] = val;
	    tree[node] = val;
	    return;
	}

	int mid = (start_ + end_) / 2;
	if (start_ <= mid && indx <= mid)
	    update(node * 2, start_, mid, val, indx);
	else
	    update(node * 2 + 1, mid + 1, end_, val, indx);

	tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }
    
public:
    SegmentTree(vector<long long>& a) : A(a) {
	N = a.size() - 1;
	build(1, 0, N);
    }

    ~SegmentTree() {
	A.clear();
    }
    
    void update(int val, int indx) {
	update(1, 1, N, val, indx);
    }

    int query(int l, int r) {
	return query(1, 1, N, l, r);
    }
};

int brute(int l, int r, int K) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
	for (int k = 0; k <= K; k++) {
	    ans += val[i - k];
	}
    }
    return ans;
}

#undef int
int main() {
#define int long long
    
    int N, Q; cin >> N >> Q;
    val.push_back(0);
    for (int i = 0; i < N; i++) {
	val.push_back(0);
    }

    for (int i = 1; i <= N; i++) {
	int x; cin >> x;
	val.push_back(x);
    }

    for (int i = 0; i < val.size(); i++) {
	sum_left.push_back(val[i] * i);
    }

    for (int i = val.size() - 1; i >= 0; i--)
	sum_right.push_back(val[i] * (val.size() - i));

    reverse(sum_right.begin(), sum_right.end());
    
    SegmentTree *seg_val = new SegmentTree(val);
    SegmentTree *seg_sum_left = new SegmentTree(sum_left);
    SegmentTree *seg_sum_right = new SegmentTree(sum_right);
    
    
    for (int q = 0; q < Q; q++) {
	int t; cin >> t;
	if (t == 1) {
	
	    int l, r, K; cin >> l >> r >> K;
	    l += N;
	    r += N;

	    int len = r - l + 1;
	    long long ans = 0;
	    int ll, rr, height;
	    
	    if (len < K + 1) {
		ll = r - K;
		rr = l;
		height = len;
	    } else {
		ll = l;
		rr = r - K;
		height = K + 1;
	    }

	    ans += height * seg_val->query(ll, rr);
	    
	    int first_ = l - K;
	    long long cur =  seg_sum_left->query(first_, ll - 1) - (first_ - 1) * seg_val->query(first_, ll - 1);
	    ans += cur;

	    ans += seg_sum_right->query(rr + 1, r) - (val.size() - 1 - r) * seg_val->query(rr + 1, r);
	    
	    cout << ans << "\n";
	    //	    cout << brute(l, r, K) << "\n";
	    
	} else {
	    int indx, X; cin >> indx >> X;
	    indx += N;
	    val[indx] = X;
	    seg_val->update(X, indx);
	    seg_sum_left->update(X * indx , indx);
	    seg_sum_right->update(X * (val.size() - indx), indx);
	}
    }

    delete seg_val;
    delete seg_sum_right;
    delete seg_sum_left;
    
    return 0;
}
