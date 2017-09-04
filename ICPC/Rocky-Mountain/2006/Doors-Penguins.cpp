#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define x real()
#define y imag()
#define EPS 1e-8
const double PI = acos(-1);
typedef complex<double> PT;

double dot(const PT& a, const PT& b) { return real(conj(a) * b); }
double cross(const PT& a, const PT& b) { return imag(conj(a) * b); }
bool ccw(PT p, PT q, PT r) { return cross(q - p, r - p) > 0; }

double angle(PT a, PT o, PT b) {  // returns angle aob in rad
    PT oa = a - o, ob = b - o;
    return acos(dot(oa, ob) / sqrt(norm(oa) * norm(ob)));
}

bool point_in_polygon(PT pt, const vector<PT> &P) {
    double sum = 0;    // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);
        else
            sum -= angle(P[i], pt, P[i+1]);
    }
    return fabs(fabs(sum) - 2*PI) < EPS;
}

bool collinear(PT a, PT b, PT c) {
    PT A = b - a;
    PT B = c - a;
    return A.x * B.y == A.y * B.x;
}

bool on_line(const PT& a, const PT& b, const PT& p) {
    if (fabs(abs(a - p) + abs(b - p) - abs(a - b)) < EPS)
        return true;
    return false;
}

bool lineline(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (d == 0) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

bool segment_intersect(PT a1, PT a2, PT b1, PT b2) {
    PT c;
    if (!lineline(a1, a2, b1, b2, c)) return false;
    if (on_line(a1, a2, c) && on_line(b1, b2, c))
        return true;
    return false;
}

bool ok(const vector<PT>& white, const vector<PT>& black) {
    if (point_in_polygon(white[0], black) || point_in_polygon(black[0], white)) return false;
    for (int i = 0; i < white.size(); i++) {
        int i1 = (i + 1) % white.size();
        for (int k = 0; k < black.size(); k++) {
            int k1 = (k + 1) % black.size();
            if (segment_intersect(white[i], white[i1], black[k], black[k1])) {
                return false;
            }
        }
    }
    return true;
}

PT pivot;
bool angle_cmp(PT a, PT b) {
    if (collinear(pivot, a, b))
        return abs(pivot - a) < abs(pivot - b);
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<PT> convex_hull(vector<PT> P) {
    int i, j, n = (int)P.size();

    int P0 = 0;
    for (i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;

    swap(P[P0], P[0]);

    pivot = P[0];
    sort(++P.begin(), P.end(), angle_cmp);

    vector<PT> S;
    S.push_back(P[n-1]);
    S.push_back(P[0]);
    S.push_back(P[1]);
    i = 2;

    while (i < n) {
        j = (int)S.size()-1;
        if (ccw(S[j-1], S[j], P[i]))
            S.push_back(P[i++]);  // left turn, accept
        else
            S.pop_back();
    }
    return S;
}

void print_good(int t) { cout << "Case " << t << ": It is possible to separate the two groups of vendors.\n"; }
void print_bad(int t) { cout << "Case " << t << ": It is not possible to separate the two groups of vendors.\n"; }

int main() {

    int t = 1;
    int N, M; cin >> N >> M;
    while (true) {
        vector<PT> white, black;
        for (int i = 0; i < N; i++) {
            int xx, yy; cin >> xx >> yy;
            int xx2, yy2; cin >> xx2 >> yy2;
            white.pb(PT(xx, yy)); white.pb(PT(xx2, yy2));
            white.pb(PT(xx, yy2)); white.pb(PT(xx2, yy));
        }
        for (int i = 0; i < M; i++) {
            int xx, yy; cin >> xx >> yy;
            int xx2, yy2; cin >> xx2 >> yy2;
            black.pb(PT(xx, yy)); black.pb(PT(xx2, yy2));
            black.pb(PT(xx, yy2)); black.pb(PT(xx2, yy));
        }

        if (N == 0 || M == 0) {
            print_good(t++);
            continue;
        }

        vector<PT> hull_white = convex_hull(white);
        vector<PT> hull_black = convex_hull(black);

        if (ok(hull_white, hull_black))
            print_good(t++);
        else
            print_bad(t++);

        cin >> N >> M;
        if (!(N == 0 && M == 0)) {
            cout << "\n";
            break;
        }
    }

    return 0;
}