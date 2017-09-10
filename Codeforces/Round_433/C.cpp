#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define MAX 600005
long long cost[MAX];
long long ans[MAX];

int main() {
#define int long long

    int N, K; cin >> N >> K;
    vector<pair<int, int> > v;
    for (int i = 1; i <= N; i++) {
        int c; cin >> c;
        cost[i] = c;
        v.pb(mp(c, i));
    }

    sort(v.begin(), v.end());

    set<int> have;
    for (int i = K + 1; i <= N + K; i++) {
        have.insert(i);
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        int c = v[i].first;
        int pos = v[i].second;

        auto it = have.upper_bound(pos);
        int best = *it;
        if (it != have.begin()) {
            auto b = --it;
            if (*b >= pos) {
                best = *b;
            }
        }

        ans[pos] = best;

        have.erase(best);
    }

    int amnt = 0;
    for (int i = 1; i <= N; i++) {
        amnt += cost[i] * (ans[i] - i);
    }

    cout << amnt << "\n";
    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";
    cout << "\n";

    return 0;
}