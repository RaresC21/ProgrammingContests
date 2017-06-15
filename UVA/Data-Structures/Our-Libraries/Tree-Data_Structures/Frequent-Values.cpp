#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define MAX 100005

class SegmentTree {
private :
    #define op max
    int N;
    int tree[MAX * 2];
    vector<int> A;

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
	if (l > end_ || r < start_) return -1;
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
	N = A.size();
	build(1, 0, N - 1);
    }

    int query(int l, int r) {
	return query(1, 0, N - 1, l, r);
    }
};

int arr[MAX];
int section[MAX];
int dist[MAX];

int main() {
    
    int N, M; cin >> N;
    while (N != 0) {
	cin >> M;

	vector<int> freq;
	int cnt = 1, which = 0;
	for (int i = 0; i < N; i++) {
	    cin >> arr[i];
	    if (i == 0) continue;
	    if (arr[i] == arr[i - 1]) {
		cnt++;
	    } else {
		freq.pb(cnt);
		cnt = 1;
		which++;
	    }
	    section[i] = which;
	}
	freq.pb(cnt);
	
	dist[N - 1] = 1;
	for (int i = N - 2; i >= 0; i--) {
	    if (arr[i] == arr[i + 1]) {
		dist[i] = dist[i + 1] + 1;
	    } else {
		dist[i] = 1;
	    }
	}

	SegmentTree *seg = new SegmentTree(freq);

	for (int i = 0; i < M; i++) {
	    int l, r; cin >> l >> r; l--, r--;
	    if (section[l] == section[r]) {
		cout << r - l + 1 << "\n";
	    } else {
		int left_len = dist[l];
		int right_len = freq[section[r]] - dist[r] + 1;
		
		int best_inside = 0;
		if (section[l] + 1 <=  section[r] - 1)
		    best_inside = seg->query(section[l] + 1, section[r] - 1);
		
		cout << max(max(left_len, right_len), best_inside) << "\n";
	    }
	}
	
	delete seg;
	cin >> N;
    }
	    
   
    return 0;
}
