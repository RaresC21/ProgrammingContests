#include <bits/stdc++.h>
using namespace std;

const long double PI = 3.14159265358979323846;
#define MAX 100011

struct PT {
    long double angle;
    int id;
    PT (long double angle, int id) : angle(angle), id(id) {}
};

bool angleCmp (PT a, PT b) {
    return a.angle < b.angle;
}

int main() {

    int N; cin >> N;
    vector<PT> vec;
    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;
        vec.push_back(PT(atan2(x, y), i));
    }

    sort (vec.begin(), vec.end(), angleCmp);

    long double ans = 10;
    pair<int, int> indx;
    for (int i = 0; i < N; i++) {
        long double cur = vec[i].angle - vec[(i + 1) % N].angle;

        cur = fabs(cur);
        cur = min (cur, PI + PI - cur);

        if (ans > cur) {
            ans = cur;
            indx.first = vec[i].id;
            indx.second = vec[(i+1)%N].id;
        }
    }

    cout << indx.first << " " << indx.second << "\n";

    return 0;
}
