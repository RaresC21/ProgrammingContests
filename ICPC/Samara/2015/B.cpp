 #include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 5005

int amnt[MAX];

int main() {

    ios_base::sync_with_stdio(false);

    string s;
    int N, M; cin >> N >> M;
    vector<string> v;
    for (int i = 0; i < N; i++) {
        cin >> s;

        int amnt = 0;
        for (int k = 0; k < M; k++) {
            if (s[k] == '1') amnt++;
        }
        if (amnt >= 8 && amnt <= 15) {
            v.pb(s);
        }
    }

    sort(v.begin(), v.end());

    int cur = 1, ans = 0;
    string tasks = "";
    v.pb("dummy");
    for (int i = 1; i < v.size(); i++) {
        if (v[i] == v[i - 1]) {
            cur++;
        } else {
            if (ans < cur) {
                tasks = v[i - 1];
                ans = cur;
            }
            cur = 1;
        }
    }

    if (tasks == "") {
        for (int i = 0; i < 8; i++) cout << '1';
        for (int i = 8; i < M; i++) cout << '0';
        cout << "\n";
    }
    cout << tasks << "\n";

    return 0;
}

