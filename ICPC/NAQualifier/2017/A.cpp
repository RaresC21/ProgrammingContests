#include <bits/stdc++.h>
using namespace std;
typedef complex<double> PT;

#define EPS 1e-9
#define x real()
#define y imag()
double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }

bool lineline(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (d == 0) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

struct Line {
    double a, b, c;
    PT p, q;
    Line () {}
    Line (double a, double b, double c) : a(a), b(b), c(c) {
        if (b == 0) {
            p = PT(-c/a, 0);
            q = p + PT(0, 1);
        } else if (a == 0) {
            p = PT(0, -c/b);
            q = p + PT(1,0);
        } else if (c == 0) {
            p = PT(0,0);
            q = PT(-b, -a);
        } else {
            p = PT(0, -c/b);
            q = PT(-c/a, 0);
        }
    }
};

vector<PT> candle;
vector<Line> line;

bool opposie(PT a, PT b, Line l) {
    bool c1 = cross(l.p - l.q, a - l.p) < 0;
    bool c2 = cross(l.p - l.q, b - l.p) < 0;
    return c1^c2;
}

bool separate(PT a, PT b) {
    for (int i = 0; i < line.size(); i++)
        if (opposie(a, b, line[i]))
            return true;
    return false;
}

int main() {

    int N, M, R; cin >> N >> M >> R;
    candle.resize(N);
    for (int i = 0; i < N; i++) {
        double xx, yy; cin >> xx >> yy;
        candle[i] = PT(xx, yy);
    }
    line.resize(M);
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        line[i] = Line(a, b, c);
    }

    int region = M + 1;
    for (int i = 0; i < M; i++) {
        for (int k = i + 1; k < M; k++) {
            PT a;
            if (lineline(line[i].p, line[i].q, line[k].p, line[k].q, a)) {
                if (abs(a) <= R)
                    region++;
            }
        }
    }

    if (region != N) {
        cout << "no\n";
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int k = i + 1; k < N; k++) {
            if (!separate(candle[i], candle[k])) {
                cout << "no\n";
                return 0;
            }
        }
    }

    cout << "yes\n";

    return 0;
}