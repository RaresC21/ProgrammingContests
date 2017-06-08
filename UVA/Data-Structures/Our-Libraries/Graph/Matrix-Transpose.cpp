#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define MAX 10004

vector<pair<int, int> > mat[MAX];

int main() {

    int R, C;
    while (cin >> R >> C) {

	cout << C << " " << R << "\n";

	for (int i = 1; i <= C; i++)
	    mat[i].clear();
	
	for (int r = 1; r <= R; r++) {

	    int N; cin >> N;
	    vector<int> indx(N + 1);	    
	    for (int i = 1; i <= N; i++) {
		cin >> indx[i];
	    }
	    
	    for (int i = 1; i <= N; i++) {
		int val; cin >> val;
		mat[indx[i]].pb(mp(r, val));
	    }
	}

	for (int i = 1; i <= C; i++) {
	    sort(mat[i].begin(), mat[i].end()); 
	}
	
	for (int i = 1; i <= C; i++) {
	    cout << mat[i].size();
	    for (int k = 0; k < mat[i].size(); k++) {
		cout << " " << mat[i][k].first;
	    }
	    cout << "\n";
	    for (int k = 0; k < mat[i].size(); k++) {
		cout << mat[i][k].second;
		if (k != mat[i].size() - 1)
		    cout << " ";
	    }
	    cout << "\n";
	}
    }
    
   
    return 0;
}
