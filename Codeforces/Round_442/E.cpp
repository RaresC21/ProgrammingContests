/* 
   /home/rares/ProgrammingContests/Codeforces/Round_442/
   E.cpp
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

const int MAX = 200005;

class SegTree {
    
private:
    
    int N;
    std::vector<int>& A;
    int tree[5 * MAX], lazy[5 * MAX];
    
    void build(int node, int start, int end);
    void lazy_updateRange(int node, int start, int end, int l, int r, bool flip);
    int lazy_queryRange(int node, int start, int end, int l, int r);
    void push_lazy(int node, int start, int end);
    void update(int node, int start, int end);
    
public:
    
    SegTree(std::vector<int>& a) : A(a) {
	N = A.size() - 1;
	build(1, 1, N);
    }
    
    void update_range(int l, int r) {
	lazy_updateRange(1, 1, N, l, r, true);
    }
    int query(int l, int r) {
	return lazy_queryRange(1, 1, N, l, r);
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
    
    tree[node] = (tree[2 * node] + tree[2 * node + 1]);
}

void SegTree::push_lazy(int node, int start, int end) {
    if (lazy[node]) {
	tree[node] = end - start + 1 - tree[node];
	if (start != end) {
	    lazy[node * 2 + 1] = !lazy[node * 2 + 1];
	    lazy[node * 2] = !lazy[node * 2];
	}
	lazy[node] = false;
    }
}

void SegTree::update(int node, int start, int end) {
    tree[node] = (end - start + 1) - tree[node];

    if (start != end) {
	lazy[node * 2] = !lazy[node * 2];
	lazy[node * 2 + 1] = !lazy[node * 2 + 1];
    }
}

void SegTree::lazy_updateRange(int node, int start, int end, int l, int r, bool flip) {
    push_lazy(node, start, end);
    
    if (start > end || start > r || end < l)
	return;

    if (start >= l && end <= r) {
	update(node, start, end);
	return;
    }
    
    int mid = (start + end) / 2;
    lazy_updateRange(node * 2, start, mid, l, r, flip);
    lazy_updateRange(node * 2 + 1, mid + 1, end, l, r, flip);
    
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

VI child[MAX];
int timp = 0;
VI light;
int in[MAX], out[MAX];
void dfs(int node) {
    in[node] = ++timp;
    for (int adj : child[node])
	dfs(adj);

    out[node] = timp;
}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    FOR(i,2,N+1) {
	int x; cin >> x;
	child[x].push_back(i);
    }

    dfs(1);

    light.resize(N+1);
    FOR(i,1,N+1) {
	int x; cin >> x;
	light[in[i]] = x;
    }

    SegTree* seg = new SegTree(light);

    int Q; cin >> Q;
    while (Q--) {
	string t; cin >> t;
	if (t == "get") {
	    int x; cin >> x;
	    int ans = seg->query(in[x], out[x]);
	    cout << ans << "\n";
	} else {
	    int x; cin >> x;
	    seg->update_range(in[x], out[x]);
	}
    }
    
    return 0;
}
