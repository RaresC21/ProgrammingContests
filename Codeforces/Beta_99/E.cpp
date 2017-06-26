#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

// returns a^x mod p
double exponent_(double a, int x) {
    double ans = 1.0;
    while (x > 0) {
        if (x % 2 == 1)
            ans = (ans * a);
        x /= 2;
        a = (a * a);
    }
    return ans;
}

struct Event {
    int pos;
    int type;
    int prob;
    int power;
    Event(int pos, int type, int p = -1, int power = -1) : pos(pos), type(type), prob(p), power(power) {}
    bool operator < (const Event& other) {
        if (pos != other.pos) return pos < other.pos;
        return type < other.type;
    }
};

int powers[101];
vector<Event> event;

double calc(int power) {
    double cur = power;
    for (int i = 0; i <= 100; i++) {
        if (powers[i] != 0) {
            cur *= exponent_((100 - 1.0 * i) / 100.0, powers[i]);
        }
    }
    return cur;
}

int main() {

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; i++){
        int pos, h, l, r; cin >> pos >> h >> l >> r;
        event.pb(Event(pos - h, 1, l));
        event.pb(Event(pos - 1, 3, l));

        event.pb(Event(pos + 1, 1, r));
        event.pb(Event(pos + h, 3, r));
    }

    for (int i = 0; i < M; i++) {
        int pos, power; cin >> pos >> power;
        event.pb(Event(pos, 2, -1, power));
    }

    sort(event.begin(), event.end());

    double ans = 0;
    int n = event.size();
    int i = 0;
    while (i < n) {
        while (i < n && event[i].type == 1) {
            powers[event[i].prob] ++;
            i++;
        }

        while (i < n && event[i].type == 2) {
            ans += calc(event[i].power);
            i++;
        }

        while (i < n && event[i].type == 3) {
            powers[event[i].prob] --;
            i++;
        }
    }

    cout << fixed << setprecision(9) << ans << "\n";

    return 0;
}