#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define int lli
struct Event {
    int a, b, u;
    int indx;
    Event(int a, int b, int u, int i) : a(a), b(b), u(u), indx(i) {}
    bool operator < (const Event& other) const {
        return a < other.a;
    }
};

struct End {
    int end;
    int k;
    End(int end, int k) : end(end), k(k) {}
    bool operator < (const End& other) const {
        return end > other.end;
    }
};

#define INF 1000000009
#define MAX 200005
int map_to[MAX];
pair<int, int> dp[MAX];
int last[MAX];

#undef int
int main() {
#define int lli

    int N; cin >> N;
    vector<Event> v;
    for (int i = 0; i < N; i++) {
        int a, b, c; cin >> a >> b >> c;
        v.push_back(Event(a, b, c, i + 1));
        dp[i] = {c, b - a};
        last[i] = -1;
    }

    sort(v.begin(), v.end());
    for (int i = 0; i < N; i++)
        map_to[i] = v[i].indx;

    int k = 0;
    pair<int, pair<int, int> > best = {0, {0, -1}};
    priority_queue<End> q;

    int ans = -1, indx = -1;
    for (int i = 0; i < N; i++) {
        while (q.size() && q.top().end <= v[i].a) {
            int k = q.top().k;
            // cout << dp[k].first << " " << best.first << " " << dp[k].second << " " << best.second.first << "\n";
            if (dp[k].first > best.first) {
                best.first = dp[k].first;
                best.second.first = dp[k].second;
                best.second.second = k; 
            } else if (dp[k].first == best.first &&
                        dp[k].second < best.second.first) {
                best.second.first = dp[k].second;
                best.second.second = k;
            }
            q.pop();
        }

        // cout << i + 1 << " " << best.first << "\n";

        dp[i].first = best.first + v[i].u;
        dp[i].second = best.second.first + v[i].b - v[i].a;
        last[i] = best.second.second;

        if (dp[i].first > ans) {
            ans = dp[i].first;
            indx = i;
        } else if (dp[i].first == ans && dp[i].second < dp[indx].second) {
            indx = i;
        }

        q.push(End(v[i].b, i));
    }


    vector<int> sol;
    int duration = 0, use = 0;
    int pos = indx;
    while (indx != -1) {
        sol.push_back(indx);
        indx = last[indx];
    }

    cout << sol.size() << " " << dp[pos].first << " " << dp[pos].second << "\n";
    for (int i = sol.size() - 1; i >= 0; i--) {
        cout << map_to[sol[i]] << " ";
    } cout << "\n";

    return 0;
}