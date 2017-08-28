#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 1000006
#define INF 1000000000000000009

int amnt[MAX];
int ans[MAX];

class BitTree {
public:

    int N;
    int BIT[MAX];

    BitTree(int N) : N(N) {
        memset(BIT, 0, sizeof(BIT));
    }

    void update(int x, int val) {
        for(; x <= N; x += x & -x)
            BIT[x] += val;
    }

    int query(int x) {
        int sum = 0;
        for(; x > 0; x -= x & -x)
            sum += BIT[x];
        return sum;
    }
};

int main() {

    int N, M; cin >> N >> M;
    vector<vector<char> > grid (N, vector<char>(M, 0));

    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (int k = 0; k < M; k++)
            grid[i][k] = s[k];
    }

    vector<int> v;
    int single = 0;
    for (int i = 0; i < N; i++) {
        lli cur = 0;
        for (int k = 0; k < M; k++) {
            if (grid[i][k] == '.') cur++, single++;
            else {
                if (cur > 1)
                    v.pb(cur);
                cur = 0;
            }
        }
        if (cur > 1) v.pb(cur);
    }

    for (int i = 0; i < M; i++) {
        lli cur = 0;
        for (int k = 0; k < N; k++) {
            if (grid[k][i] == '.') cur++;
            else {
                if (cur > 1)
                    v.pb(cur);
                cur = 0;
            }
        }
        if (cur > 1) v.pb(cur);
    }

    sort(v.begin(), v.end());

    BitTree *bit = new BitTree(MAX - 1);
    for (int x : v) {
        amnt[x]++;
        bit->update(x, x);
    }

    for (int i = MAX - 1; i >= 0; i--) {
        amnt[i] += amnt[i + 1];
    }

    ans[1] = single;
    for (int i = 2; i <= max(N, M); i++) {

        int a = bit->query(MAX - 1) - bit->query(i - 1);
        ans[i] = a - amnt[i] * (i - 1);
    }

    for (int i = 1; i <= max(N, M); i++)
        cout << ans[i] << " ";
    cout << "\n";

    return 0;
}