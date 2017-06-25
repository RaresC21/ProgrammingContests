#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

lli MIN, MAX, MEAN, MED;

bool check(lli i) {
    lli sum = i * MEAN - MIN - MAX;
    if (sum < 0) false;

    if (i % 2 == 0) {
        lli x = i - 4;
        sum -= 2 * MED;

        lli smallest = MIN * (x / 2) + (MED) * (x / 2);
        lli biggest = (MED) * (x / 2) + (MAX) * (x / 2);

        if (sum >= smallest && sum <= biggest) {
            return true;
        }
    } else {
        lli x = i - 3;
        sum -= MED;

        lli smallest = MIN * (x / 2) + MED * (x / 2);
        lli biggest = MED * (x / 2) + MAX * (x / 2);

        if (sum >= smallest && sum <= biggest) {
            return true;
        }
    }
    return false;
}

int main() {

    ifstream cin ("input.txt");
    ofstream cout ("ans.txt");

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        cin >> MIN >> MAX >> MEAN >> MED;

        if (MIN > MAX || MED < MIN || MED > MAX || MEAN < MIN || MEAN > MAX) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        if (MIN == MAX) {
            cout << "Case #" << t << ": ";
            if (MEAN == MIN && MED == MIN) {
                cout << "1\n";
            } else {
                cout << "IMPOSSIBLE\n";
            }
            continue;
        }

        if ((MIN + MAX) % 2 == 0) {
            if (MEAN == (MIN + MAX) / 2 && MED == MEAN) {
                cout << "Case #" << t << ": 2\n";
                continue;
            }
        }

        lli ans = 0;
        lli l = 3, r = 10000000000;
        while (l <= r) {
            lli mid = (l + r) / 2;
            if (check(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        for (lli i = max(3LL, l - 10000LL); i <= l + 10; i++) {
            if (check(i)) {
                ans = i;
                break;
            }
        }

        cout << "Case #" << t << ": ";
        if (ans == 0) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << "\n";
        }
        cerr << t << "\n";
    }

    return 0;
}