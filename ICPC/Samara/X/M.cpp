#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

int main() {

    int N; cin >> N;
    vector<pair<int, int> > v;
    for (int i = 1; i <= N; i++) {
        int amnt; cin >> amnt;
        v.pb({amnt, i});
    }

    sort(v.begin(), v.end());
    int k = 0;
    int amnt = 0;
    vector<pair<int, int> > ans;
    for (int i = 0; i < N; i++) {
        if (v[i].first > amnt) {
            cout << "NO\n";
            return 0;
        }
        amnt -= v[i].first;
        for (int j = 0; j < v[i].first; j++, k++) {
            ans.pb(mp(v[i].second, v[k].second));
        }
        amnt++;
    }

    cout << "YES\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}