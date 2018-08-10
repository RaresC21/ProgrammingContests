#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;

int main() {
    io;

    int M, N; cin >> M >> N;
    vector<bool> lie(60);

    for (int i = 0; i < N; i++) {
      cout << "1\n";
      cout.flush();

      int resp; cin >> resp;
      if (resp == 0) {
	return 0;
      }

      if (resp == -1) {
	lie[i] = true;
      }
    }

    int minim = 1, maxim = M;
    for (int i = N; i < 60; i++) {
      int mid = (minim + maxim) / 2;
      cout << mid << "\n";
      cout.flush();

      int resp; cin >> resp;
      if (resp == 0) return 0;

      if (lie[i % N]) resp *= -1;
      if (resp == -1) maxim = mid - 1;
      else minim = mid + 1;
    }
    
    return 0;
}
