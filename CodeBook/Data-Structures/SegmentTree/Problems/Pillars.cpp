/* 
   /home/rares/ProgrammingContests/CodeBook/Data-Structures/SegmentTree/Problems/
   Pillars.cpp

   Marmot found a row with n pillars. The i-th pillar has the height of hi meters.
   Starting from one pillar i1, Marmot wants to jump on the pillars i2, ..., ik. 
   (1 ≤ i1 < i2 < ... < ik ≤ n). From a pillar i Marmot can jump on a pillar j only if i < j 
   and |hi - hj| ≥ d, where |x| is the absolute value of the number x.

   Now Marmot is asking you find out a jump sequence with maximal length and print it.


   Input
   The first line contains two integers n and d (1 ≤ n ≤ 10^5, 0 ≤ d ≤ 10^9).
   The second line contains n numbers h1, h2, ..., hn (1 ≤ h_i ≤ 10^15).
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

const int INF = 1e8;
const int MAX = 100005;

class SegTree {
private:

    int N;
    std::vector<int> A;
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

    SegTree(int (*op)(int a, int b)) : op(op) {
	N = MAX - 1;
	A = vector<int>(N);
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

int maxim(int a, int b) {
    if (a < b) return b;
    return a;
}

LL h[MAX];
int dp[MAX];
VLL all;
map<LL, int> conv;

int find_smaller(LL v) {
    int ans = -1;
    int minim = 0, maxim = SZ(all) - 1;
    while (minim <= maxim) {
	int mid = (minim + maxim) / 2;
	if (all[mid] <= v) {
	    ans = max(ans, mid);
	    minim = mid + 1;
	} else {
	    maxim = mid - 1;
	}
    }
    return ans;
}

int find_greater(LL v) {
    int ans = INF;
    int minim = 0, maxim = SZ(all) - 1;
    while (minim <= maxim) {
	int mid = (minim + maxim) / 2;
	if (all[mid] >= v) {
	    ans = min(ans, mid);
	    maxim = mid - 1;
	} else {
	    minim = mid + 1;
	}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int N;
    LL D; cin >> N >> D;
    FOR(i,0,N) {
	cin >> h[i];
	all.push_back(h[i]);
    }

    sort(all.begin(), all.end());
    int cnt = 0;
    FOR(i,0,N) {
	if (!conv.count(all[i])) {
	    conv[all[i]] = cnt++;
	}
    }

    VI height(N);
    FOR(i,0,N) {
	height[i] = conv[all[i]];
    }
    
    SegTree *seg = new SegTree(maxim);
    memset(dp, -1, sizeof(dp));

    int ans = 0;
    FOR(i,0,N) {
	int l = find_smaller(h[i] - D);
	int r = find_greater(h[i] + D);

	int cur = 0;
	if (l != -1){
	    cur = max(cur, seg->query(0, height[l], 0));
	}
	if (r != INF) {
	    cur = max(cur, seg->query(height[r], MAX - 1, 0));
	}

	cur += 1;
	seg->update(conv[h[i]], cur);
	
	ans = max(ans, cur);
	dp[i] = cur;
    }

    cout << ans << "\n";

    int want = ans;
    int last = -1;
    VI sol;
    for (int i = N - 1; i >= 0; i--) {
	if (dp[i] == want && (last == -1 || abs(h[last] - h[i]) >= D)) {
	    sol.push_back(i + 1);
	    want --;
	    last = i;
	}
    }

    ROF(i,0,SZ(sol)) {
	cout << sol[i] << " ";
    }
    
    cout << "\n";
    
    return 0;
}
