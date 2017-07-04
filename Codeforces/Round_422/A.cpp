#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    int A, B; cin >> A >> B;
    int minim = min(A, B);
    long long ans = 1;
    for (int i = 1; i <= minim; i++)
	ans *= i;
    cout << ans << "\n";
    
    return 0;
}
