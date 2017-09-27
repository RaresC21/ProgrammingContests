#include "bits/stdc++.h"
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second
#define x real()
#define y imag()
typedef complex<double> PT;

const int MAX = 200005;
const int INF = 1000000009;

double cross(PT a, PT b) { return imag(conj(a) * b); }
double area(vector<PT> p) {
    double ans = 0;
    FOR(i,0,SZ(p)) {
	int nxt = (i + 1) % SZ(p);
	ans += cross(p[i], p[nxt]) * 0.5;
    }
    return abs(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int N; cin >> N;
    vector<PT> v;
    FOR(i,0,N) {
	double a, b; cin >> a >> b;
	v.push_back(PT(a, b));
    }
    
    cout << fixed << setprecision(6) << area(v) << "\n";
    return 0;
}
