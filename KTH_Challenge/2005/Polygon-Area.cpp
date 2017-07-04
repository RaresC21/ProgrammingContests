#include <bits/stdc++.h>
using namespace std;

struct PT {
    double x, y;
    PT () {}
    PT (double x, double y) : x(x), y(y) {}
};

double ComputeSignedArea(const vector<PT> &p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

double ComputeArea(const vector<PT> &p) {
    return fabs(ComputeSignedArea(p));
}

// vector stuff. ---------------------------------
struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

vec toVec(PT a, PT b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y);
}

// returns true if point r is on the left side of line pq
bool is_ccw(PT p, PT q, PT r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

int main() {

    int N; cin >> N;
    while (N != 0) {
	vector<PT> v;
	for (int i = 0; i < N; i++) {
	    double x, y; cin >> x >> y;
	    v.push_back(PT(x, y));
	}

	double sum = 0;
	for (int i = 0; i < N; i++) {
	    sum += (v[(i + 1) % N].x - v[i].x) * (v[(i + 1) % N].y + v[i].y);
	}
	if (sum > 0) cout << "CW ";
	else cout << "CCW ";
	cout << fixed << setprecision(1) << ComputeArea(v) << "\n";
	
	cin >> N;
    }
    
    return 0;
}
