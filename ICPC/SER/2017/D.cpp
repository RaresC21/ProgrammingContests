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

const int INF = 1000000000;
const int MAX = 2000;
string grid[MAX];

class SegTree {
private:
    int N;
    int tree[4 * MAX];

    inline void update(int node, int l, int r, int indx, int val) {
        if (l > indx || r < indx) return;
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;
        update(node * 2, l, mid, indx, val);
        update(node * 2 + 1, mid + 1, r, indx, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    inline int query(int node, int l, int r, int left, int right) {
        if (l > right || r < left) return INF;
        if (l >= left && r <= right) {
            return tree[node];
        }

        int mid = (l + r) / 2;
        int q1 = query(node * 2, l, mid, left, right);
        int q2 = query(node * 2 + 1, mid + 1, r, left, right);
        return min(q1, q2);
    }

public:
    SegTree() {
        N = 4 * MAX;
        for (int i = 0; i < N; i++) {
            tree[i] = INF;
        }
    }

    inline void update(int indx, int val) {
        update(1, 0, MAX - 1, indx, val);
    }

    inline int query(int a, int b) {
        return query(1, 0, MAX - 1, a, b);
    }
};  

SegTree row[MAX], col[MAX]; 

int main() {
    ios_base::sync_with_stdio(false);

    clock_t begin = clock();

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    row[0].update(0, 0);
    col[0].update(0, 0);
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (grid[i][k] == '#') continue;
            int d = min(row[i].query(max(0, k - K), k), col[k].query(max(0, i - K), i)) + 1;
            if (i == N - 1 && k == N - 1) {
                if (d >= INF) {
                    cout << "-1\n";
                } else {
                    cout << d - 1 << "\n";
                }
                return 0;
            }

            row[i].update(k, d);
            col[k].update(i, d);
        }
    }

    return 0;
}