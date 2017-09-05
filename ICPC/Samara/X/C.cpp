#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

int main() {

    int A, B, C; cin >> A >> B >> C;
    int N, M; cin >> N >> M;

    if (N < C || M < C) {
        cout << min(N, M) << "\n";
        return 0;
    }


    N -= C;
    M -= C;

    if (A > N && B > M) {
        cout << C + min(N, M) << "\n";
    } else if (A > N) {
        cout << C + N << "\n";
    } else if (B > M) {
        cout << C + M << "\n";
    } else {
        cout << A + B + C << "\n";
    }
}