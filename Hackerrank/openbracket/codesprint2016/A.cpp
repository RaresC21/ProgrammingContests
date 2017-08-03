#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main() {

    int N; cin >> N;
    lli receive = 5;
    lli ans = 0;
    for (int i = 0; i < N; i++) {
	lli like = receive / 2;
	ans += like;
	receive = like * 3;
    }

    cout << ans << "\n";
    
    return 0;
}
