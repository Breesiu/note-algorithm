#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<queue>

using namespace std;

typedef long long LL;
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
#define inf 0x3fffffff
#define MAXN 10005

int N,L,P;

struct node{
	int dist,fuel;
};
bool cmp(node a,node b){
	return a.dist<b.dist;
}

vector<node> stops(MAXN);


int main(){
//	freopen("d:\\input.txt","r",stdin);
	cin>>N;
	_for(i,0,N){
		scanf("%d %d",&stops[i].dist,&stops[i].fuel);
	}
	cin>>L>>P;
	_for(i,0,N){
		stops[i].dist=L-stops[i].dist;
	}
	sort(stops.begin(),stops.begin()+N,cmp);

	int r=0,dist=0,cnt=0;

	while(r<N&&stops[r].dist<dist)r++;

	priority_queue<int> pq;

	while(1){
		dist+=P;
		if(dist>=L)break;
		while(r<N&&stops[r].dist<=dist){
			pq.push(stops[r].fuel);
			r++;
		}
		cnt++;
		if(pq.empty())break;
		P=pq.top();
		pq.pop();
	}

	if(dist<L){
		printf("-1\n");
	}else{
		printf("%d\n",cnt);
	}

	return 0;
}
