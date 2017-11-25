/* 
   /home/rares/ProgrammingContests/CodeBook/Data-Structures/SegmentTree/Problems/
   lazy-LIS.cpp

   Codeforces Round 104. Div1. E
*/

#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

const int MAX = 1000006;
class SegTree {   
private:
    
    int N;
    std::vector<int>& A;
    int four[5 * MAX], seven[5 * MAX], inc[5 * MAX], dec[5 * MAX];
    int tree[5 * MAX], lazy[5 * MAX];
    
    void build(int node, int start, int end);
    void lazy_updateRange(int node, int start, int end, int l, int r);
    int lazy_queryRange(int node, int start, int end, int l, int r);
    void push_lazy(int node, int start, int end);
    void update(int node, int start, int end);
    void merge(int node, int a, int b);
    
public:
    
    SegTree(std::vector<int>& a) : A(a) {
        N = A.size();
        build(1, 0, N - 1);
    }
    
    void update_range(int l, int r) {
        lazy_updateRange(1, 0, N - 1, l, r);
    }

    int query() {
	return inc[1];
    }
};

void SegTree::merge(int node, int a, int b) {
    four[node] = four[a] + four[b];
    seven[node] = seven[a] + seven[b];
    inc[node] = max(max(four[a] + seven[b], inc[a] + seven[b]), four[a] + inc[b]);
    dec[node] = max(max(seven[a] + four[b], dec[a] + four[b]), seven[a] + dec[b]);
}

void SegTree::build(int node, int start, int end) {
    if (start == end) { // leaf node
	inc[node] = dec[node] = 1;
        if (A[start] == 4) {
	    four[node] = 1;
	} else {
	    seven[node] = 1;
	}
        return;
    }
    
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    merge(node, node * 2, node * 2 + 1);
}

// update current node with whatever is stored in lazy. Pass the lazy on to the children
void SegTree::push_lazy(int node, int start, int end) {
    if (lazy[node]) {
	swap(four[node], seven[node]);
	swap(inc[node], dec[node]);
        if (start != end) {
            lazy[node * 2 + 1] ^= 1;
            lazy[node * 2] ^= 1;
        }
        lazy[node] = 0;
    }
}

// update current node normally with val passed in
// push this down lazily to children.
void SegTree::update(int node, int start, int end) {
    swap(four[node], seven[node]);
    swap(inc[node], dec[node]);
    
    if (start != end) {
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
    }
}

void SegTree::lazy_updateRange(int node, int start, int end, int l, int r) {
    push_lazy(node, start, end);
    
    if (start > end || start > r || end < l)
        return;

    if (start >= l && end <= r) {
        update(node, start, end);
        return;
    }
    
    int mid = (start + end) / 2;
    lazy_updateRange(node * 2, start, mid, l, r);
    lazy_updateRange(node * 2 + 1, mid + 1, end, l, r);

    merge(node, node * 2, node * 2 + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int N, Q; cin >> N >> Q;
    string s; cin >> s;

    VI v(N);
    for (int i = 0; i < SZ(s); i++) {
	v[i] = s[i] - '0';
    }

    SegTree* seg = new SegTree(v);

    string t;
    while (Q--) {
	cin >> t;
	if (t[0] == 'c') {
	    cout << seg->query() << "\n";
	} else {
	    int l, r; cin >> l >> r;
	    l --, r--;
	    seg->update_range(l, r);
	}
    }
    
    return 0;
}
