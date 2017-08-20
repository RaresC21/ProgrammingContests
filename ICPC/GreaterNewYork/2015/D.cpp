/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   D.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 10011

int lp[MAX + 1];
int phi[MAX + 1];
vector<int> pr;
void phi_primes_sieve(int N) {
    phi[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            phi[i] = i - 1;
            pr.push_back(i);
        }
        else {
            //Calculating phi
            if (lp[i] == lp[i / lp[i]])
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

int main() {
    
    phi_primes_sieve(MAX - 1);
    
    int T; cin >> T;
    while (T--) {
	int t; cin >> t;
	int N; cin >> N;
	lli ans = 2;
	for (int i = 2; i <= N; i++) {
	    ans += phi[i];
	}
	cout << t << " " << ans << "\n";
    }
    
    return 0;
}
