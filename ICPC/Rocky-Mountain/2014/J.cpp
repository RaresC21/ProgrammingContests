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

vector<VI> clause;

bool eval(int mask) {
    FOR(i,0,SZ(clause)) {
        bool good = false;
        FOR(k,0,SZ(clause[i])) {
            int c = abs(clause[i][k]);
            bool want = clause[i][k] > 0 ? 1 : 0;
            bool cur = mask & (1 << c);
            if (cur == want) {
                good = true;
                break;
            }
        }
        if (!good) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        clause.clear();

        cin.ignore();
        FOR(j,0,M) {
            string s; getline(cin, s);
            int i = 0;
            VI v;
            while (i < SZ(s)) {
                bool opp = false;
                if (s[i] == '~') {
                    opp = true;
                    i ++;
                }
                i ++;
                int num = 0;
                while (i < SZ(s) && s[i] != ' ') {
                    num = num * 10 + (s[i] - '0');
                    i ++;
                }

                if (opp) num = -num;
                v.push_back(num);
                i += 3;
            }
            clause.push_back(v);
        }

        bool good = false;
        FOR(mask, 0, (1 << (N+1))) {
            if (eval(mask)) {
                cout << "satisfiable\n";
                good = true;
                break;
            }
        }
        if (!good) {
            cout << "unsatisfiable\n";
        }
    }

    return 0;
}