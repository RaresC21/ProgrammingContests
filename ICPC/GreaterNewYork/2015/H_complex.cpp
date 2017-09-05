#include <bits/stdc++.h>
using namespace std;

#define x real()
#define y imag()
typedef complex<double> PT;

double cross(PT a, PT b) { return (conj(a) * b).y; }

bool lineline(PT a1, PT a2, PT b1, PT b2, PT &isect) {
	double d = cross(a2-a1, b2-b1);
  	if (d == 0) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
  	return true;
}

// rotate a about point p by theta degrees
PT rotateCCW(PT p, PT a, double theta) {
	return (a-p) * polar(1.0, theta) + p;
}

double angle(PT a, PT b, PT c) {
	return abs(remainder(arg(a-b) - arg(c-b), 2.0 * M_PI));
}

PT ans;
double area(double angle, PT A, PT B, PT C) {
	PT AA = rotateCCW(A, B, angle);
	PT BB = rotateCCW(B, C, angle);
	PT CC = rotateCCW(C, A, angle);

	PT p1, p2, p3; 
	lineline(A, AA, B, BB, p1);
	lineline(B, BB, C, CC, p2);
	lineline(C, CC, A, AA, p3);
	ans = p1;

	return 0.5 * cross(p2 - p1, p3 - p1);
}

int main() {

	int T; cin >> T;
	while(T--) {
		int t; cin >> t;
		PT A, B, C; cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

		double aa = angle(B, A, C);
		double bb = angle(A, B, C);
		double cc = angle(A, C, B);
		double minim = 0, maxim = min(min(aa, bb), cc);
		for (int i = 0; i < 100; i++) {
			double m1 = minim + (maxim - minim) / 3;
			double m2 = maxim - (maxim - minim) / 3;
			if (area(m1, A, B, C) < area(m2, A, B, C)) {
				maxim = m2;
			} else {
				minim = m1;
			}
		}

		cout << fixed << setprecision(5);
		cout << t << " " << ans.x << " " << ans.y << "\n";
	}

	return 0;
}