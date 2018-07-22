#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define mp make_pair
#define pb push_back

const int MOD = 1e9 + 7;
const int INF = 1e9;
const long long LLINF = 1e18;

const int MAX = 2005;
int l[MAX], r[MAX];
vector<int> val, pos;

vector<int> pre, post;
void pre_order(int node) {
  if (node == -1) return;
  pre.pb(node);
  pre_order(l[node]);
  pre_order(r[node]);
}

void post_order(int node) {
  if (node == -1) return;
  post_order(l[node]);
  post_order(r[node]);
  post.pb(node);
}

void fill(int node, int label) {
  if (val[pre[node]]) return;
  val[pre[node]] = label;
  fill(pos[post[node]], label);
}

int main() {

  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) {
      cin >> l[i] >> r[i];
      l[i] --;
      r[i] --;
    }
    
    pos.clear();
    val.clear();
    val.resize(N);
    pre.clear();
    post.clear();

    pre_order(0);
    post_order(0);
    
    pos.resize(N);
    for (int i = 0; i < N; i++) {
      pos[pre[i]] = i;
    }

    int k = 0;
    for (int i = 0; i < N; i++) {
      if (!val[pre[i]]) {
        if (k < K) k++;
        fill(i, k);
      }
    }

    cout << "Case #" << t << ": ";
    if (k < K) {
      cout << "Impossible\n";
    } else {
      for (int i = 0; i < N; i++) {
	      cout << val[i] << " ";
      }
      cout << "\n";
    }
  }
  
  return 0;
}
