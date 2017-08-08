/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   C.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    const int N = 26;
    
    string a, b; cin >> a >> b;
    string ans = "";
    for (int i = 0; i < min(a.size(), b.size()); i++) {
	int c1 = a[i] - 'A';
	int c2 = b[i] - 'A';
	int cur = (c1 - c2 + N) % N;
	
	ans = ans + char(cur + 'A');
    }

    if (a.size() <= b.size()) {
	cout << ans << "\n";
	return 0;
    }

    int i = 0;
    for (int k = b.size(); k < a.size(); k++, i++) {
	int c1 = a[k] - 'A';
	int c2 = ans[i] - 'A';
	int cur = (c1 - c2 + N) % N;

	ans = ans + char(cur + 'A');
    }

    cout << ans << "\n";
    
    return 0;
}
