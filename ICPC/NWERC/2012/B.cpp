#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<double> chance_to_pick(10);
vector<int> winners;
lli power[10];
double ans[10];

int main() {

    double total = 0;
    
    int N;
    while (scanf("%d", &N) == 1) {
	int K;
	scanf("%d", &K);
	
	power[N - 1] = 1;
	for (int i = N - 2; i >= 0; i--)
	    power[i] = power[i + 1] * 100;
    

	lli base = 0;
	int x;
	for (int i = 0; i < N; i++) {
	    scanf("%d", &x);
	    base = base * 100LL + x;
	    ans[i] = 0;
	}

	map<lli, double> prob;
	queue<lli> state;
	state.push(base);
	prob[base] = 1.0;
	
	while (state.size()) {
	    lli cur_state = state.front();
	    state.pop();

	    vector<lli> cur(N);
	    lli temp = cur_state;
	    for (int i = N - 1; i >= 0; i--) {
		cur[i] = temp % 100LL;
		temp /= 100LL;
	    }
	    
	    int sum = 0;
	    for (int i = 0; i < N; i++) {
		sum += cur[i];
	    }
	    
	    if (sum > K) {
		continue;
	    } else if (sum == K) {
		winners.clear();
		winners.push_back(0);
		for (int i = 1; i < N; i++) {
		    if (cur[i] == cur[winners[0]])
			winners.push_back(i);
		    else if (cur[i] > cur[winners[0]]) {
			winners.clear();
			winners.push_back(i);
		    }
		}

		double prob_cur = prob[cur_state];
		int ww = winners.size();
		for (int i = 0; i < ww; i++) {
		    ans[winners[i]] += prob_cur * 1.0  / (1.0 * ww);
		}
	    } else {
		for (int i = 0; i < N; i++) {
		    chance_to_pick[i] = cur[i] * 1.0 / (1.0 * sum);
		} 
		
		double current_prob = prob[cur_state];
		for (int i = 0; i < N; i++) {
		    lli temp = cur_state +  power[i];

		    auto it = prob.find(temp);
		    if (it != prob.end()) {
			it->second += current_prob * chance_to_pick[i];
		    } else {
			state.push(temp);
			prob[temp] += current_prob * chance_to_pick[i];
		    }
		}
	    }
	}
	for (int i = 0; i < N; i++) {
	    printf("pub %d: %.2f %%\n", i + 1, ans[i] * 100);
	}
	
    }
    
    return 0;
}
