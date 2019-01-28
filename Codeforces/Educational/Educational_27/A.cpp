/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   A.cpp
*/

/*
  We can put the first N highest rated players on the team we want to 
  win. This way, even the lowest rated player on the team we want to win, 
  will be better than even the best person on the other team. 
  The only time is not the case is if the lowest rated person has the same 
  rating as the highest rated person on the other team.
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

int rating[200];

int main() {
    
    int N; cin >> N;
    for (int i = 0; i < 2 * N; i++)
	cin >> rating[i];
	
    sort(rating, rating + 2 * N);
    
    if (rating[N] == rating[N - 1]) {
	cout << "NO\n";
    } else {
	cout << "YES\n";
    }
    
    return 0;
}
