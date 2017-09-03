#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define DELTA 1 - 1e-7
#define EPS 1e-8
typedef pair<int, int> PT;
int cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

int main() {

    int N;
    while (cin >> N) {
        vector<PT> p;

        int minx = 1000000000, maxx = -1000000000;
        for (int i = 0; i < N; i++) {
            int xx, yy; cin >> xx >> yy;

            if (yy == 0) {
                minx = min(minx, xx);
                maxx = max(maxx, xx);
            }
            p.pb(mp(xx, yy));
        }

        double mass = 0;
        double centroid = 0;
        double momentum = 0;
        for (int i = 1; i < N - 1; i++) {
            double cur_mass = 0.5 * cross(mp(p[i].x - p[0].x, p[i].y - p[0].y),
                                          mp(p[i+1].x - p[0].x, p[i+1].y - p[0].y));
            double x_center = 1.0 * (p[0].x + p[i].x + p[i + 1].x) / 3.0;

            mass += cur_mass;
            momentum += x_center * cur_mass;
        }

        if (mass < 0) {
            mass = -mass;
            momentum = -momentum;
        }
        centroid = momentum / mass;

        int xx = p[0].x;

        double left_ = ((mass * (minx - centroid)) / (xx - minx));
        double right_ = ((mass * (centroid - maxx)) / (maxx - xx));

        if (centroid < minx) {
            if (xx <= minx) {
                cout << "unstable\n";
            } else if (xx <= maxx) {
                cout << (int)(left_ + EPS);
                cout << " .. inf\n";
            } else {
                cout << (int)(left_ + EPS);
                cout << " .. ";
                cout << (int)(right_ + DELTA) << "\n";
            }
        } else if (centroid >= minx && centroid <= maxx) {
            if (xx < minx) {
                cout << "0 .. ";
                cout << (int)(left_ + DELTA) << "\n";
            } else if (xx <= maxx) {
                cout << "0 .. inf\n";
            } else {
                cout << "0 .. ";
                cout << (int)(right_ + DELTA) << "\n";
            }
        } else {
            if (xx >= maxx) {
                cout << "unstable\n";
            } else if (xx >= minx) {
                cout << (int)(right_ + EPS);
                cout << " .. inf\n";
            } else {
                cout << (int)(right_ + EPS) << " .. " << (int)(left_ + DELTA) << "\n";
            }
        }
    }

    return 0;
}