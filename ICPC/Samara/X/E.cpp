#include "bits/stdc++.h"
using namespace std;
typedef long long int lli;

#define INF 1000000000000000000
vector<lli> tele, bonus;

int upper(lli x) {
    int minim = 0, maxim = bonus.size() - 1;
    int ans = maxim + 1;
    while (minim <= maxim) {
        int mid = (minim + maxim) / 2;
        if (bonus[mid] >= x) {
            ans = min(ans, mid);
            maxim = mid - 1;
        } else {
            minim = mid + 1;
        }
    }
    return ans;
}

int lower(lli x) {
    int minim = 0, maxim = bonus.size() - 1;
    int ans = -1;
    while (minim <= maxim) {
        int mid = (minim + maxim) / 2;
        if (bonus[mid] <= x) {
            ans = max(ans, mid);
            minim = mid + 1;
        } else {
            maxim = mid - 1;
        }
    }
    return ans;
}


int main() {

    int N, M; cin >> N >> M;

    tele.push_back(-INF);
    for (int i = 0; i < N; i++) {
        int temp; cin >> temp;
        tele.push_back(temp);
    }
    tele.push_back(INF);

    for (int i = 0; i < M; i++) {
        int temp; cin >> temp;
        bonus.push_back(temp);
    }

    lli ans = 0;
    for (int i = 0; i < tele.size() - 1; i++) {
        int l = upper(tele[i]);
        int r = lower(tele[i + 1]);
        if (r == -1 || bonus[r] < tele[i]) continue;

        lli cur = tele[i + 1] - tele[i];
        cur = min(cur, 2LL * (bonus[r] - tele[i]));
        cur = min(cur, 2LL * (tele[i + 1] - bonus[l]));
        for (int k = l; k < r; k++) {
            cur = min(cur, 2LL * (bonus[k] - tele[i]) + 2LL * (tele[i + 1] - bonus[k + 1]));
        }
        ans += cur;
    }

    cout << ans << "\n";

    return 0;
}