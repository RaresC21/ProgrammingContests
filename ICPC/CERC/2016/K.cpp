#include <bits/stdc++.h>
using namespace std;

#define pb push_back

int main() {

    string s; cin >> s;

    int amnt = 0;
    for (int i = 0; i < s.size() - 1; i++)
	if (s[i] != s[i + 1]) amnt++;
    if (amnt + 1 >= 2 * s.size() / 3) {
	cout << "0\n";
	return 0;
    }
    
    vector<int> v;
    for (int i = 0; i < s.size(); i += 3) {
	string cur = "";
	cur = cur + s[i];
	cur = cur + s[i + 1];
	cur = cur + s[i + 2];

	if (cur == "000") {
	    v.pb(i + 1);
	} else if (cur == "001") {
	    v.pb(i + 1);
	} else if (cur == "100") {
	    v.pb(i);
	} else if (cur == "110") {
	    v.pb(i + 1);
	} else if (cur == "011") {
	    v.pb(i);
	} else if (cur == "111") {
	    v.pb(i);
	}
    }

    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++)
	cout << v[i] + 1 << " ";
    cout << "\n";
    
    return 0;
}
