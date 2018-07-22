#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1001;
char grid[3][MAX];

int main () {

  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    int N; cin >> N;
    for (int r = 0; r < 3; r++) {
      string s; cin >> s;
      for (int i = 0; i < N; i++) {
      	grid[r][i] = s[i];
      }
    }
    
    cout << "Case #" << t << ": ";

    if (grid[0][0] == '#' || grid[1][0] == '#' || grid[1][N-1] == '#' || grid[2][N-1] == '#') {
      cout << "0\n";
      continue;
    }

    if (N % 2 != 0) {
      cout << "0\n";
      continue;
    }
    

    long long total = 1;
    for (int i = 1; i < N - 1; i+=2) {
      int amnt = 0;
      if (grid[0][i] == '.' && grid[0][i+1] == '.') amnt++;
      if (grid[2][i] == '.' && grid[2][i+1] == '.') amnt++;
      if (grid[1][i] == '#' || grid[1][i+1] == '#') amnt = 0;
      total = (total * amnt) % MOD;
    }

    cout << total << "\n";
  }

  return 0;
}
