#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

#define MAX 200005
string name[MAX];
int amnt[MAX];

int main() {

    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> name[i + 1];
    }

    int M; cin >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        amnt[a] = amnt[b] + 1; 
        name[a] = name[b];
    }

    string ans = "";
    for (int i = 0; i < amnt[1]; i++)
        cout << "I_love_";
    cout << name[1] << "\n";
}