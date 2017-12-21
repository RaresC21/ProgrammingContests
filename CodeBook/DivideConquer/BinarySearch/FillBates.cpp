#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

void print_time(const clock_t& begin) {
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elapsed time: ";
    cerr << fixed << setprecision(4) << elapsed_secs << "\n";
}

const int INF = 1e9;

vector<vector<int> > v;

int next_position(int want, int pos) {
    int ans = INF;
    int minim = 0, maxim = v[want].size() - 1;
    while (minim <= maxim) {
        int mid = (minim + maxim) / 2;
        if (v[want][mid] >= pos) {
            ans = min(ans, v[want][mid]);
            maxim = mid - 1;
        } else {
            minim = mid + 1;
        }
    }
    return ans;
}

int main() {
    #ifdef TIMP
    clock_t start_time = clock();
    #endif
    io;

    string S; cin >> S;
    v.resize(200);
    for (int i = 0; i < S.size(); i++) {
        v[S[i]].pb(i);
    }

    int Q; cin >> Q;
    while (Q--) {
        string goal; cin >> goal;

        int start = next_position(goal[0], 0);
        int pos = start;
        for (int i = 1; i < goal.size(); i++) {
            pos = next_position(goal[i], pos + 1);
            if (pos == INF) {
                break;
            }
        }
        if (pos == INF) {
            cout << "Not matched\n";
        } else {
            cout << "Matched " << start << " " << pos << "\n";
        }
    }


    #ifdef TIMP
    print_time(start_time);
    #endif
    return 0;
}
