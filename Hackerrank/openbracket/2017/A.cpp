/* 
   /home/rares/ProgrammingContests/Hackerrank/openbracket/2017/
   A.cpp
*/

#include <iostream>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {
    
    string s; cin >> s;
    for (int i = 0; i < 5; i++) {
	if (s[i] < 'a' || s[i] > 'z') {
	    cout << "No\n";
	    return 0;
	}
    }

    string want = "hogwarts.com";
    int k = 0;
    for (int i = 5; i < s.size(); i++, k++) {
	if (s[i] != want[k]) {
	    cout << "No\n";
	    return 0;
	}
    }

    cout << "Yes\n";
    
    return 0;
}
