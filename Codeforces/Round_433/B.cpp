#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair


int main() {

    int N, K; cin >> N >> K;
    if (K == 0) { cout << "0 0\n"; return 0; }
    int minim = min(N - K, 1);
    int maxim = min(N - K, 2 * K);

    cout << minim << " " << maxim << "\n";

    return 0;
}
