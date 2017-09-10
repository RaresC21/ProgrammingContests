#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define int lli
#define mp make_pair
#define pb push_back
#define MAX 600005
#define INF 100000000000000000
int to[MAX], from[MAX];
int to_amnt[MAX], from_amnt[MAX];
int best_to[MAX], best_from[MAX];

struct Flight {
    int day, a, b, c;
    Flight(int day, int a, int b, int c) : day(day), a(a), b(b), c(c) {}
    bool operator < (const Flight& other) const {
        return day < other.day;
    }
};

#undef int
int main() {
#define int lli

    memset(to, -1, sizeof(to));
    memset(from, -1, sizeof(from));

    int N, M, K; cin >> N >> M >> K;
    vector<Flight> v;
    for (int i = 0; i < M; i++) {
        int day, a, b, c;  cin >> day >> a >> b >> c;
        v.pb(Flight(day, a, b, c));
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i].b != 0) {
            if (i != 0) {
                best_to[i] = best_to[i - 1];
                to_amnt[i] = to_amnt[i - 1];
            }
            continue;
        }

        if (to[v[i].a] == -1) {
            to[v[i].a] = v[i].c;
            if (i != 0) {
                to_amnt[i] = to_amnt[i - 1] + 1;
                best_to[i] += best_to[i - 1] + v[i].c;
            }
            else {
                to_amnt[i] = 1;
                best_to[i] = v[i].c;
            }
        } else {
            if (i != 0)
                best_to[i] = min(best_to[i - 1], best_to[i - 1] - to[v[i].a] + v[i].c);
            else
                best_to[i] = v[i].c;

            to[v[i].a] = min(to[v[i].a], v[i].c);

            to_amnt[i] = to_amnt[i - 1];
        }
    }

    int vs = v.size();
    for (int i = vs - 1; i >= 0; i--) {
        if (v[i].a != 0) {
            from_amnt[i] = from_amnt[i + 1];
            best_from[i] = best_from[i + 1];
            continue;
        }

        if (from[v[i].b] == -1) {
            from[v[i].b] = v[i].c;
            if (i < vs - 1) {
                from_amnt[i] = from_amnt[i + 1] + 1;
                best_from[i] += best_from[i + 1] + v[i].c;
            }
            else {
                from_amnt[i] = 1;
                best_from[i] = v[i].c;
            }
        } else {
            if (i < vs - 1)
                best_from[i] = min(best_from[i + 1], best_from[i + 1] - from[v[i].b] + v[i].c);
            else
                best_from[i] = v[i].c;

            from[v[i].b] = min(from[v[i].b], v[i].c);
            from_amnt[i] = from_amnt[i + 1];
        }
    }

    int k = 0;
    int ans = INF;
    for (int i = 0; i < v.size(); i++) {
        while (k < v.size() && v[k].day - v[i].day <= K)
            k++;

        if (v[k].day - v[i].day <= K) break;

        if (to_amnt[i] != N) continue;
        if (from_amnt[k] != N) continue;

        ans = min(ans, best_to[i] + best_from[k]);
    }

    if (ans == INF) {
        cout << "-1\n";
    } else
        cout << ans << "\n";

    return 0;
}