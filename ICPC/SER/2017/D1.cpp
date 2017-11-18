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

deque<pii> col[MAX], row[MAX];

void update_row(int r, int val, int indx) {
    while (!row[r].empty() && row[r].back().A >= val) {
        row[r].pop_back();
    }
    row[r].push_back(MP(val, indx));
}

void update_col(int c, int val, int indx) {
    while (!col[c].empty() && col[c].back().A >= val) {
        col[c].pop_back();
    }
    col[c].push_back(MP(val, indx));
}

int main() {
    ios_base::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    if (N == 1) {
        cout << "0\n";
        return 0;
    }

    row[0].push_front(MP(0, 0));
    col[0].push_front(MP(0, 0));
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (grid[i][k] == '#') continue;

            while (!row[i].empty() && k - row[i].front().B > K) row[i].pop_front();
            while (!col[k].empty() && i - col[k].front().B > K) col[k].pop_front();

            pii best_in_row = MP(INF, -1), best_in_col = MP(INF, -1);
            if (!row[i].empty())
                best_in_row = row[i].front();
            if (!col[k].empty())
                best_in_col = col[k].front();

            int d = min(best_in_col.A, best_in_row.A) + 1;
            if (i == N - 1 && k == N - 1) {
                if (d >= INF) {
                    cout << "-1\n";
                } else {
                    cout << d << "\n";
                }
                return 0;
            }

            update_row(i, d, k);
            update_col(k, d, i);
        }
    }

    return 0;
}