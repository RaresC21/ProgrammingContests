#include <bits/stdc++.h>
using namespace std;

map<char, vector<string> > letter;

int main() {
    ios_base::sync_with_stdio(false);

    letter['A'] = {"***", "*.*", "***", "*.*", "*.*"};
    letter['B'] = {"***", "*.*", "***", "*.*", "***"};
    letter['C'] = {"***", "*..", "*..", "*..", "***"};
    letter['D'] = {"***", "*.*", "*.*", "*.*", "***"};
    letter['E'] = {"***", "*..", "***", "*..", "***"};

    int N; cin >> N;
    string s; cin >> s;
    for (int i = 0; i < 5; i++) {
        for (char c : s) {
            cout << letter[c][i];
        }
        cout << "\n";
    }

	return 0;
}
