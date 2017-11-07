#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

const double EPS = 1e-9;
#define x real()
#define y imag()
typedef complex<double> PT;

inline double dot (PT a, PT b) { return real(conj(a) * b); }
inline double cross(PT a, PT b) { return imag(conj(a) * b); }
inline double dist2(PT a, PT b) { return norm(a - b); }

inline bool lineline(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (d == 0) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

vector<vector<PT> > v;
bool met[300];

double run = 0;
inline double area(double a, double b) {
    pair<double, int> event[200];
    int cnt = 0;
    for (int i = 0; i < SZ(v); i++) {
        for (int k = 0; k < SZ(v[i]); k++) {
            PT p1 = v[i][k];
            PT p2 = v[i][(k + 1) % SZ(v[i])];
            if (p1.x > p2.x) swap(p1, p2);

            if (p1.x <= a && p2.x >= b) {
                PT q1, q2;
                lineline(p1, p2, PT(a,0), PT(a,100), q1);
                lineline(p1, p2, PT(b,0), PT(b,100), q2);
                double yy = ((q1.y + q2.y) / 2);
                event[cnt++] = (MP(yy, i));
            }
        }
    }
    sort(event, event + cnt);

    double ans = 0;
    int amnt = 0;
    for (int i = 0; i < cnt; i++){
        double yy = event[i].A;
        int t = event[i].B;
        if (met[t]) {
            amnt --;
            if (amnt == 0) {
                ans += yy;
            }
            met[t] = false;
        } else {
            if (amnt == 0) {
                ans -= yy;
            }
            amnt ++;
            met[t] = true;
        }
    }
    run += ans * (b - a);
    return ans * (b - a);
}

double solve() {
    int N; cin >> N;
    v.resize(N);
    vector<pair<PT, PT> > all;  // INPUT
    for (int i = 0; i < N; i++) {
        int M; cin >> M;
        vector<PT> cur(M);
        for (int k = 0; k < M; k++) {
            int a, b; cin >> a >> b;
            cur[k] = PT(a, b);
        }
        for (int k = 0; k < M; k++) {
            int j = (k + 1) % M;
            all.push_back(MP(cur[k], cur[j]));
        }
        v[i] = cur;
    }

    vector<double> xs;
    for (int i = 0; i < SZ(all); i++) {
        xs.push_back(all[i].A.x);
        for (int k = 0; k < i; k++) {
            PT p;
            if (lineline(all[i].A, all[i].B, all[k].A, all[k].B, p)) {
                double xx = real(p);
                if (xx >= 0 && xx <= 1000 && imag(p) <= 1000 && imag(p) >= 0)
                    xs.push_back(xx);
            }
        }
    }

    sort(xs.begin(), xs.end());

    double ans = 0;
    for (int i = 0; i < xs.size() - 1; i++) {
        if (xs[i + 1] - xs[i] < EPS) continue;
        ans += area(xs[i], xs[i + 1]);
    }
    return ans;
}

int main() {
    cout << solve() << "\n";
    return 0;
}