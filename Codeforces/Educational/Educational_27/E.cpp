/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   E.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define int lli
#define INF 1000000009
#define pb push_back
#define mp make_pair

int N, M;
int K;
vector<pair<int, int> > fire;

bool full_fire(vector<pair<int, int> >& seg, int edge) {
    if (seg.size() == 0) return false;
    sort(seg.begin(), seg.end());
    int ret = 0;
    int last = 0;
    for (int i = 0; i < seg.size(); i++) {
	int l = max(seg[i].first, last + 1);
	ret += max(0LL, seg[i].second - l + 1);
	last = max(last, seg[i].second);
    }
    return ret >= edge;
}

bool check(int t) {
    vector<int> x, y;
    x.pb(1), x.pb(N);
    y.pb(1), y.pb(M);
    for (int i = 0; i < fire.size(); i++) {
        x.pb(max(1LL, fire[i].first - t - 1));
        x.pb(min(N, fire[i].first + t + 1));

        y.pb(max(1LL, fire[i].second - t - 1));
        y.pb(min(M, fire[i].second + t + 1));
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    int left_x = INF, right_x = -1, top_y = -1, bot_y = INF;
    
    // handle column
    for (int i = 0; i < x.size(); i++) {
	vector<pair<int, int> > alight;
	for (int k = 0; k < fire.size(); k++) {
	    if (abs(fire[k].first - x[i]) > t) continue;
	    alight.pb(mp(max(1LL, fire[k].second - t),
			 min(fire[k].second + t, M)));
	}

	if (!full_fire(alight, M)) {
	    left_x = min(left_x, x[i]);
	    right_x = max(right_x, x[i]);
	}
    }

    // handle rows
    for (int i = 0; i < y.size(); i++) {
	vector<pair<int, int> > alight;

	for (int k = 0; k < fire.size(); k++) {
	    if (abs(fire[k].second - y[i]) > t) continue;
	    alight.pb(mp(max(1LL, fire[k].first - t),
			 min(fire[k].first + t, N)));
	}

	if (!full_fire(alight, N)) {
	    top_y = max(top_y, y[i]);
	    bot_y = min(bot_y, y[i]);
	}
    }

    if (left_x == INF) return true;

    return (right_x - left_x <= 2 * t) && (top_y - bot_y <= 2 * t);
}

#undef int
int main() {
#define int lli
    
    cin >> N >> M;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int x, y; cin >> x >> y;
        fire.pb(mp(x, y));
    }

    int minim = 0, maxim = INF;
    int ans = maxim * 10;
    while (minim <= maxim) {
        int mid = (minim + maxim) / 2;
        if (check(mid)) {
            maxim = mid - 1;
            ans = min(ans, mid);
        } else {
            minim = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
