#include <bits/stdc++.h>
using namespace std;

int main() {

	map<string, vector<string> > pre;
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        int M; cin >> M;
        vector<string> need(M);
        for (int k = 0; k < M; k++) 
            cin >> need[k];
        pre[s] = (need);
    }
    
    
    map<string, bool> met;
    for (int i = 0; i < N; i++) {
        string cur; cin >> cur;
        for (string s : pre[cur]) {
            if (!met.count(s)) {
                cout << "BOOM!\n";
                return 0;
            }
        }

        met[cur] = true;
    }
    
    cout << "SAFE!\n";

    return 0;
}