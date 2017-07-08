#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-12
struct PT {
    double x, y;
    PT () {}
    PT (double x, double y) : x(x), y(y) {}
    PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator * (double c) const { return PT(x * c, y * c); }
    PT operator / (double c) const { return PT(x / c, y / c); }
};

struct Mouse {
    PT p;
    PT speed;
    Mouse () {}
    Mouse (PT p, PT s) : p(p), speed(s) {}
};


double dist(PT p, PT q) {
    double dx = p.x - q.x;
    double dy = p.y - q.y;
    return sqrt(dx * dx + dy * dy);
}
double cross(PT p, PT q) { return p.x * q.y - p.y * q.x; };

bool lines_parallel(PT a, PT b, PT c, PT d) {
    return fabs(cross(b - a, c - d)) < EPS;
}

bool lines_collinear(PT a, PT b, PT c, PT d) {
    return lines_parallel(a, b, c, d)
	&& fabs(cross(a - b, a - c)) < EPS && fabs(cross(c - d, c - a)) < EPS;
}

// line a-b intersect segment c-d
PT line_intersect_segment(PT a, PT b, PT c, PT d) {
    PT cc = c;
    PT dd = d;
    
    b = b - a;
    d = c - d;
    c = c - a;
    PT ans = a + b * cross(c, d) / cross(b, d);

    if (cc.x > dd.x) swap(cc, dd);
    if (ans.x < cc.x || ans.x > dd.x) return PT(-1, -1);

    if (cc.y > dd.y) swap(cc, dd);
    if (ans.y < cc.y || ans.y > dd.y) return PT(-1, -1);
    
    return ans;
}

#define MAX 100005
Mouse mouse[MAX];
PT rect[4];

bool inside(PT p) {
    if (p.x >= rect[0].x && p.x <= rect[2].x &&
	p.y >= rect[0].y && p.y <= rect[2].y)
	return true;
    return false;
}

int main() {

    int N; cin >> N;
    cin >> rect[0].x >> rect[0].y >> rect[2].x >> rect[2].y;
    rect[1] = PT(rect[0].x, rect[2].y);
    rect[3] = PT(rect[2].x, rect[0].y);

    vector<pair<double, int> > timp;
    for (int i = 0; i < N; i++) {
	cin >> mouse[i].p.x >> mouse[i].p.y;
	cin >> mouse[i].speed.x >> mouse[i].speed.y;

	PT p1 = mouse[i].p;
	PT p2 = p1 + mouse[i].speed;
	for (int k = 0; k < 4; k++) {
	    int j = (k + 1) % 4;
	    if (lines_collinear(p1, p2, rect[k], rect[j])) {
		cout << "-1\n";
		return 0;
	    }
	}

	vector<double> hit;
	if (inside(p1)) {
	    hit.push_back(0);
	    if (mouse[i].speed.x == 0 && mouse[i].speed.y == 0)
		hit.push_back(100000000);
	}
	
	for (int k = 0; k < 4; k++) {
	    int j = (k + 1) % 4;
	    PT cur = line_intersect_segment(p1, p2, rect[k], rect[j]);
	    if (cur.x < -0.5) continue;
	    double dx = cur.x - p1.x;
	    double dy = cur.y - p1.y;
	    if (mouse[i].speed.x != 0 && dx != 0) {
		double h = dx / mouse[i].speed.x;
		if (h >= 0)
		    hit.push_back(h);
	    } else if (mouse[i].speed.y != 0 && dy != 0) {
		double h = dy / mouse[i].speed.y;
		if (h >= 0)
		    hit.push_back(dy / mouse[i].speed.y);
	    }
	}
	sort(hit.begin(), hit.end());

	vector<double> v;
	for (int k = 0; k < hit.size(); k++) {
	    if (k > 0 && fabs(hit[k] - hit[k - 1]) < EPS) {
		continue;
	    }
	    v.push_back(hit[k]);
	}
	if (v.size() % 2 == 1) continue;
	for (int k = 0; k < v.size(); k++) {
	    timp.push_back(make_pair(v[k], 1 - k));
	}
    }

    sort(timp.begin(), timp.end());

    double last = 0;
    int amnt = 0;
    int i = 0;
    while (i < timp.size()) {
	while (i < timp.size() && fabs(last - timp[i].first) < EPS) {
	    if (timp[i].second == 1) amnt++;
	    else amnt--;
	    i++;
	}

	if (amnt == N) {
	    cout << fixed << setprecision(9) <<  timp[i - 1].first << "\n";
	    return 0;
	}
	last = timp[i].first;
    }

    cout << "-1\n";
    
    return 0;
}
