#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)

struct PT {
    double x, y;
    PT () {}
    PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator / (double c) const { return PT(x / c, y / c); }
    PT operator * (double c) const { return PT(x * c, y * c); }
    PT (double x, double y) : x(x), y(y) {}
};

void print(PT a) {
    cout << "(" << a.x << ", " << a.y << ")\n";
}

PT A, B, C;

double dist(PT a, PT b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
double cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }

PT line_intersection(PT a, PT b, PT c, PT d) {
    b = b - a;
    d = c - d;
    c = c - a;
    return a + b * cross(c, d) / cross(b, d);
}

PT rotateCCW(PT p, double t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

PT vec(PT a, PT b) {
    return b - a;
}

double angle(PT a, PT b) {
    return atan2(a.y, a.x) - atan2(b.y, b.x);
}

double area(double ab, double bc, double ca) {
    double s = 0.5 * (ab + bc + ca);
    return sqrt(s * (s - ab) * (s - bc) * (s - ca));
}

double area(PT a, PT b, PT c) {
    return area(dist(a, b), dist(a, c), dist(b, c));
}

PT ans;

double calc(double theta) {
    PT AA = A + rotateCCW(B - A, theta);
    PT BB = B + rotateCCW(C - B, theta);
    PT CC = C + rotateCCW(A - C, theta);

    PT X = line_intersection(A, AA, B, BB);
    PT Y = line_intersection(A, AA, C, CC);
    PT Z = line_intersection(B, BB, C, CC);

    ans = X;
    
    return area(X, Y, Z);
}

int main() {

    int P; scanf("%d", &P);
    for (int t = 1; t <= P; t++) {
	int K; cin >> K;
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	double a1 = fabs(angle(vec(A, B), vec(A, C)));
	double a2 = fabs(angle(vec(B, A), vec(B, C)));
	double a3 = fabs(angle(vec(C, A), vec(C, B)));
	double maxim = min(min(a1, a2), a3);
	double minim = 0;

	for (int i = 0; i < 100; i++) {
	    double l = minim + (maxim - minim) / 3;
	    double r = maxim - (maxim - minim) / 3;
	    double area1 = calc(l);
	    double area2 = calc(r);
	    
	    if (area1 > area2) {
		minim = l;
	    } else {
		maxim = r;
	    }
	}

	cout << t << " ";
	cout << fixed << setprecision(5) << ans.x << " " << ans.y << "\n";
    }
    
    
    return 0;
}
