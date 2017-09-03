#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define x real()
#define y imag()
#define EPS 1e-8
const double PI = acos(-1);

typedef complex<double> PT;
double cross(const PT& a, const PT& b) { return imag(conj(a) * b); }
double dot(const PT& a, const PT& b) { return real(conj(a) * b); }

void LineCircleIntersection(const PT& a1, const PT& a2, double R,   PT& i1, PT& i2) {
  i1 = i2 = PT(1e18, 1e18);
  double d = fabs(cross(a1, a2-a1) / abs(a2-a1));
  if (d >= R) return;
  double x1 = dot(a1, a2-a1) / abs(a2-a1);
  double x2 = dot(a2, a2-a1) / abs(a2-a1);
  double y1 = -sqrt(R*R-d*d);
  double y2 = sqrt(R*R-d*d);
  if (y1 >= x1 && y1 <= x2 || y1 >= x2 && y1 <= x1) {
    i1 = a1 + (a2-a1)*(y1-x1)/(x2-x1);
  }
  if (y2 >= x1 && y2 <= x2 || y2 >= x2 && y2 <= x1) {
    i2 = a1 + (a2-a1)*(y2-x1)/(x2-x1);
    if (i1.x == 1e18) swap(i1, i2);
  }
}

double sector(PT a1, PT a2, double R) {
    return R*R * atan2(cross(a1, a2), dot(a1, a2)) / 2;
}

vector<PT> polygon;

int main() {
    cout << fixed << setprecision(10);

    int N, R;
    while (cin >> N >> R) {
        polygon.clear();
        for (int i = 0; i < N; i++) {
            double xx, yy; cin >> xx >> yy;
            polygon.pb(PT(xx, yy));
        }

        int start_ = 0;
        for (; start_ < N; start_++) if (abs(polygon[start_]) <= R) break;

        PT lp;
        double area = 0;
        for (int j = 0; j < N; j++) {
            int i = (start_ + j) % N;
            int nxt = (i + 1) % N;

            PT p1, p2;
            LineCircleIntersection(polygon[i], polygon[nxt], R, p1, p2);
            pair<PT, PT> intersect = mp(p1,p2);

            if (norm(polygon[i]) < R*R) {
                if (abs(polygon[nxt]) < R) {
                    area += 0.5 * cross(polygon[i], polygon[nxt]);
                } else {
                    area += 0.5 * cross(polygon[i], intersect.first);
                    lp = intersect.first;
                }
            } else {
                if (norm(polygon[nxt]) < R*R) {
                    area += sector(lp, intersect.first, R);
                    area += 0.5 * cross(intersect.first, polygon[nxt]);
                } else {
                    if (intersect.first.x <= 20000) {
                        area += 0.5 * cross(intersect.first, intersect.second);
                        area += sector(intersect.second, intersect.first, R);
                    }
                }
            }
        }

        cout << area << "\n";
    }

    return 0;
}