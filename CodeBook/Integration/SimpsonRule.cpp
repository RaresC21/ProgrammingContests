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

/*
    example problem.
    Find the volume sections of an ellipse
*/

double a, b;
const double eps = 1e-8;
const double PI = acos(-1);

double f (double x) {
    double y = a*a * (1 - (x*x / (b*b)));
    return PI * y;
}
/*
    numercial integration. Must provide function f(x) which evaluates the function at point x
*/

inline double simpson(double fl,double fr,double fmid,double l,double r) { return (fl+fr+4.0*fmid)*(r-l)/6.0; }

double rsimpson(double slr,double fl,double fr,double fmid,double l,double r) {
    double mid = (l+r)*0.5;
    double fml = f((l+mid)*0.5);
    double fmr = f((mid+r)*0.5);
    double slm = simpson(fl,fmid,fml,l,mid);
    double smr = simpson(fmid,fr,fmr,mid,r);
    if(fabs(slr-slm-smr) < eps) return slm+smr;
    return rsimpson(slm,fl,fmid,fml,l,mid)+rsimpson(smr,fmid,fr,fmr,mid,r);
}

double integrate(double l,double r) {
    double mid = (l+r)*.5;
    double fl = f(l);
    double fr = f(r);
    double fmid = f(mid);
    return rsimpson(simpson(fl,fr,fmid,l,r),fl,fr,fmid,l,r);
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> a >> b;
    a /= 2, b /= 2;

    int N; cin >> N;
    double p = -b;
    double w = 2*b / N;

    cout << fixed << setprecision(9);
    for (int i = 0; i < N; i++) {
        double q = p + w;
        cout << integrate(p, q) << "\n";
        p += w;
    }

    return 0;
}