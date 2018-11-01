#include <bits/stdc++.h>
using namespace std;
 
struct PT {
    double x, y;
    PT() {}
    PT (double x, double y) : x(x), y(y) {}
}pt[40];
double cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }
 
double cc[40];
double area[40];
 
double dist(PT a, PT b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
 
bool cmp(PT a, PT b) {
    return (atan2(a.y, a.x) - atan2(b.y, b.x)) < 0;
}
 
int main() {
 
    int N; cin >> N;
    pt[N-1] = PT(0,0);
    for (int i = 0; i < N-1; i++) {
        cin >> pt[i].x >> pt[i].y;
    }
 
    vector<int> h;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        h.push_back(x);
    }
 
    sort(pt, pt+N-1, cmp);
    for (int i = 0; i < N-1; i++) {
        cc[i] = cross(pt[i], pt[(i+1)%(N-1)]) * 0.5;
    }
 
    for (int i = 0; i < N-1; i++) {
        area[i] += cc[i];
        area[i] += cc[(i-1+N-1)%(N-1)];
    }
 
    sort(area, area+N-1);
    sort(h.begin(), h.end());
 
    double ans = 0;
    for (int i = 0; i < N-1; i++) {
        double a1 = h[i] * area[i];
        double a2 = h[N-1] * cc[i];
        ans += a1 + a2;
    }
 
    cout << fixed << setprecision(2) << ans / 3.0 << "\n";
 
    return 0;
}
