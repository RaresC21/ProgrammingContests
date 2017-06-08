#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define MAX 30
bool met[MAX];
vector<int> path[MAX];

void dfs(int node) {
  if (met[node]) return;
  met[node] = true;
  for (int adj : path[node])
    dfs(adj);
}
  
int main() {

  int T; cin >> T;
  while (T--) {
    for (int i = 0; i < MAX; i++) {
      path[i].clear();
      met[i] = false;
    }
    
    string s; cin >> s;
    while (s[0] != '*') {
      int a = s[1] - 'A';
      int b = s[3] - 'A';
      path[a].pb(b);
      path[b].pb(a);
      
      cin >> s;
    }

    cin >> s;
    vector<int> all;
    for (int i = 0; i < s.size(); i += 2) {
      int node = s[i] - 'A';
      all.pb(node);
    }


    int tree = 0, acorn = 0;
    for (int node : all) {
      if (!met[node]) {
	if (path[node].size() == 0) {
	  acorn ++;
	} else {
	  tree++;
	  dfs(node);
	}
      }
    }

    cout << "There are " << tree << " tree(s) and " << acorn << " acorn(s).\n";
  }
  
  return 0;
}
