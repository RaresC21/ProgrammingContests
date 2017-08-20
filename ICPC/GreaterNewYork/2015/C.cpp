/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   C.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MOD 1000000000

void multiply_fibo(lli F[2][2], lli M[2][2]) {
    lli x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    lli y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    lli z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    lli w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x%MOD;
    F[0][1] = y%MOD;
    F[1][0] = z%MOD;
    F[1][1] = w%MOD;
}

void power_fibo(lli F[2][2], lli n) {
    if (n == 0 || n == 1) return;
    lli M[2][2] = { { 1,1 }, { 1,0 } };

    power_fibo(F, n / 2);
    multiply_fibo(F, F);
    if (n % 2 != 0)
        multiply_fibo(F, M);
}

lli fib(lli n) {
    lli F[2][2] = {{ 1,1 }, { 1,0 }};
    if (n == 0)
        return 0;
    power_fibo(F, n - 1);
    return F[0][0];
}

int main() {
    
    int T; cin >> T;
    while (T--) {
	int t; cin >> t;
	lli N; cin >> N;

	cout << t << " " << fib(N) << "\n";
    }
    
    return 0;
}
