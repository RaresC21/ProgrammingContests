#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

struct Roll {
    int sides, tosses, z;
    Roll (int s, int t, int z) : sides(s), tosses(t), z(z) {}
};

Roll parse(const string& s) {
    int i = 0;

    int tosses = 0;
    while (s[i] != 'd') {
        tosses = tosses * 10 + (s[i] - '0');
        i++;
    }
    i++;

    int sides = 0;
    while (i < s.size() && (s[i] != '-' && s[i] != '+')) {
        sides = sides * 10 + (s[i] - '0');
        i++;
    }


    bool neg = false;
    if (i < s.size() && s[i] == '-') neg = true;

    i++;

    int z = 0;
    while (i < s.size()) {
        z = z * 10 + (s[i] - '0');
        i++;
    }

    if (neg) z = -z;
    return Roll(sides, tosses, z);
}

vector<double> prob(Roll dice) {
    int sum = dice.sides * dice.tosses;
    vector<double> p(sum + 1);
    double single = 1.0 / dice.sides;
    for (int i = 1; i <= dice.sides; i++) {
        p[i] = single;
    }

    for (int i = 2; i <= dice.tosses; i++) {
        vector<double> cur(sum + 1);
        for (int k = 1; k <= sum; k++) {
            for (int r = 1; r <= dice.sides; r++) {
                if (k - r >= 1)
                    cur[k] += p[k - r] * single;
            }
        }
        p = cur;
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int H, N; cin >> H >> N;
        double ans = 0.0;
        for (int i = 0; i < N; i++) {
            string spell; cin >> spell;

            Roll dice = parse(spell);
            int cur_H = H - dice.z;

            vector<double> p = prob(dice);

            double cur = 0;
            for (int k = max(cur_H, 1); k < p.size(); k++) {
                cur += p[k];
            }

            ans = max(ans, cur);
        }

        cout << fixed << setprecision(6);
        cout << ans << "\n";
    }

    return 0;
}
