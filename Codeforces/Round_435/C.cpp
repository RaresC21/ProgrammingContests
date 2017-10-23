#include "bits/stdc++.h"
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

const int MAX = 200005;
const int INF = 1000000009;


int main() {
    ios_base::sync_with_stdio(false);

    int N, X; cin >> N >> X;

    if (N == 1) {
        cout << "YES\n";
        cout << X << "\n";
        return 0;
    }

    if (N == 2 && X == 0) {
        cout << "NO\n";
        return 0;
    }

    if (N == 2) {
        cout << "YES\n";
        cout << 0 << " " << X << "\n";
        return 0;
    }

    int val = 0;
    cout << "YES\n";

    srand(time(NULL));
    while (true) {
        VI cur;
        val = 0;
        set<int> s;
        int last = 0;
        for (int i = 0; i < N - 3; i++) {
            int r = last + 1;
            last = r;
            val ^= r;
            cur.push_back(r);
            s.insert(r);
        }

        int r = rand() % 1000;
        cur.push_back(last + r);
        s.insert(last + r);

        val ^= (last + r);
        val ^= X;

        if (val == 0 && X != 0) {
            for (int a : cur)
                cout << a << " ";
            cout << 0 << " " << X << "\n";
            return 0;
        }

        int magic = (1 << 19);
        cur.push_back(magic);
        cur.push_back(val | magic);
        s.insert(magic);
        s.insert(val | magic);

        if (s.size() == N) {
            for (int a : cur)
                cout << a << " ";
            cout << "\n";
            return 0;
        }
    }

    return 0;

}