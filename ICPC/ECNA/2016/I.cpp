/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   I.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair


// Dinic's Maxflow Template
const int INF = 1000000000;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
	from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic{
	int N;
	vector < vector < Edge > > G;
	vector < Edge * > dad;
	vector < int > Q;

	Dinic(int N) : N(N), G(N), dad(N), Q(N) {}

	void AddEdge(int from, int to, int cap){
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}

	long long BlockingFlow(int s, int t){
		fill(dad.begin(), dad.end(), (Edge *) NULL);
		dad[s] = &G[0][0] - 1;

		int head = 0, tail = 0;
		Q[tail++] = s;
	
		while(head < tail){
			int x = Q[head++];
			for (int i = 0; i < G[x].size(); i++){
				Edge &e = G[x][i];
				if(!dad[e.to] && e.cap - e.flow > 0){
					dad[e.to] = &G[x][i];
					Q[tail++] = e.to;
				}
			}
		}
		if (!dad[t]) return 0;

		long long totflow = 0;
		for (int i = 0; i < G[t].size(); i++){
			Edge *start = &G[G[t][i].to][G[t][i].index];
			int amt = INF;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]){
				if (!e) { amt = 0; break; }
				amt = min(amt, e->cap - e->flow);
			}
			if (amt == 0) continue;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
				e->flow += amt;
				G[e->to][e->index].flow -= amt;
			}
			totflow += amt;
		}
		return totflow;
	}

	long long GetMaxFlow(int s, int t){
		long long totflow = 0;
		while (long long flow = BlockingFlow(s, t)) totflow += flow;
		return totflow;
	}
};

#define MAX 105
int child[MAX], toy[MAX], category[MAX], categ_limit[MAX];
vector<int> likes[MAX];
int toy_categ[MAX];

int main() {

    int cnt = 2;
    int N, M, P; cin >> N >> M >> P;
    for (int i = 1; i <= N; i++) {
	child[i] = cnt++;

	int L; cin >> L;
	for (int k = 0; k < L; k++) {
	    int a; cin >> a;
	    likes[i].pb(a);
	}
    }

    for (int i = 1; i <= M; i++) {
	toy[i] = cnt++;
    }

    for (int i = 1; i <= P; i++) {
	category[i] = cnt++;

	int L; cin >> L;
	for (int k = 0; k < L; k++) {
	    int t; cin >> t;
	    toy_categ[t] = i;
	}

	cin >> categ_limit[i];
    }

    int source = 1;
    int sink = cnt;
    Dinic dinic(sink + 1);

    for (int i = 1; i <= N; i++) {
	dinic.AddEdge(source, child[i], 1);
	for (int t : likes[i])
	    dinic.AddEdge(child[i], toy[t], 1);
    }

    for (int i = 1; i <= M; i++) {
	if (toy_categ[i] == 0)
	    dinic.AddEdge(toy[i], sink, 1);
	else 
	    dinic.AddEdge(toy[i], category[toy_categ[i]], 1);
    }
    
    for (int i = 1; i <= P; i++) {
	dinic.AddEdge(category[i], sink, categ_limit[i]);
    }

    cout << dinic.GetMaxFlow(source, sink) << "\n";
    
    return 0;
}
