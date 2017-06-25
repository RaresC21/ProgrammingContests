#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int main() {

    ifstream cin ("input.txt");
    ofstream cout ("ans.txt");

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        string w; cin >> w;
        w = " " + w;

        vector<char> real(70);

        real[2] = w[1] - 'A';
        for (int i = 4; i < w.size(); i += 2) {
            real[i] = (w[i - 1] - 'A' - real[i - 2] + 26) % 26;
        }

        int last = w.size() - 1;
        real[last - 1] = w[last] - 'A';
        for (int i = last - 3; i >= 1; i -= 2) {
            real[i] = (w[i + 1] - real[i + 2] - 'A' + 26) % 26;
        }

        cout << "Case #" << t << ": ";

        if (w.size() % 2 == 0) {
            cout << "AMBIGUOUS\n";
        } else {
            for (int i = 1; i < w.size(); i++) {
                real[i] %= 26;
                real[i] = (real[i] + 26) % 26;
                cout << char(real[i] + 'A');
            }
            cout << "\n";
        }
    }

    return 0;
}