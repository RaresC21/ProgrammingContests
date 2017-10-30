/*
   /home/rares/Documents/
   p.cpp
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

const int MAX = 50;
int s[MAX];

LL pascal_triangle[MAX][MAX];
void make_pascal() {
    for (int line = 0; line < MAX; line++) {
        for (int i = 0; i <= line; i++) {
            if (line == i || i == 0)
                pascal_triangle[line][i] = 1;
            else
                pascal_triangle[line][i] = pascal_triangle[line-1][i-1] +
            pascal_triangle[line-1][i];
        }
    }
}

LL solve(int score, int critics) {
    return pascal_triangle[score + critics - 1][critics - 1];
}

int main() {
    ios_base::sync_with_stdio(false);

    make_pascal();

    int N; cin >> N;
    while (N != 0) {
        int sum = 0;
        FOR(i,0,N) {
            cin >> s[i];
            sum += s[i];
        }

        LL ans = 0;
        FOR(i,0,sum) {
            ans += solve(i, N);
        }

        int total = 0;
        FOR(i,0,N) {
            FOR(k,0,s[i]) {
                ans += solve(sum - k - total, N - i - 1);
            }
            total += s[i];
        }

        cout << ans + 1 << "\n";
        cin >> N;
    }

    return 0;
}