/* 
   /home/rares/ProgrammingContests/Codeforces/AIMTech/2017/
   A.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {
    
    string s; cin >> s;
    int K; cin >> K;

    if (K > s.size()) {
	cout << "impossible\n";
	return 0;
    }

    set<char> diff;
    for (int i = 0; i < s.size(); i++)
	diff.insert(s[i]);

    if (diff.size() >= K) {
	cout << "0\n";
	return 0;
    }

    cout << K - diff.size() << "\n";
    
    return 0;
}
