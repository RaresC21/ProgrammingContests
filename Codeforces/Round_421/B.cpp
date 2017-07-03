#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, A; cin >> N >> A;
    double angle = (N - 2) * 180.0 / N;
    double single = angle / (N - 2);
    double cur = single;

    double best = -180;
    int v = -1;
    for (int i = 3; i <= N; i++) {
        if (v == -1 || fabs(cur - A) < fabs(best - A)) {
            best = cur;
            v = i;
        }
        cur += single;
    }

    cout << 2 << " " << 1 << " " << v << "\n";

    return 0;
}