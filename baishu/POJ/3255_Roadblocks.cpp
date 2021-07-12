
//明明和书上代码一模一样，但还是超时了
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;

#define MAXN 5005
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define M 100
#define inf 0xfffffff
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
typedef long long LL;
typedef pair<int,int> P;

struct edge{
	int to,cost;
	edge(int to,int cost):to(to),cost(cost){}
};

vector<vector<edge> > grid(MAXN);

vector<int> dist(MAXN,inf),dist2(MAXN,inf);

int N,R;


int main(){
//	freopen("d:\\input.txt","r",stdin);
	scanf("%d %d",&N,&R);
	int a,b,d;
	_for(i,0,R){
		scanf("%d %d %d",&a,&b,&d);
		grid[a].push_back(edge(b,d));
		grid[b].push_back(edge(a,d));
	}

	dist[1]=0;
	priority_queue<P> pq;
	pq.push(P(0,1));

	while(!pq.empty()){
		P p=pq.top();pq.pop();
		int v=p.second,d=p.first;
		if(d>dist2[v])continue;

		_for(i,0,grid[v].size()){
			edge& e=grid[v][i];
			int d2=d+e.cost;
			if(dist[e.to]>d2){
				swap(dist[e.to],d2);
				pq.push(P(dist[e.to],e.to));
			}
			if(d2>dist[e.to]&&d2<dist2[e.to]){
				dist2[e.to]=d2;
				pq.push(P(dist2[e.to],e.to));
			}
		}
	}

	cout<<dist2[N]<<endl;

	return 0;
}
