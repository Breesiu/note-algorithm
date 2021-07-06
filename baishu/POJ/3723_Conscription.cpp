
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

#define MAXN 50005
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
//#define M 100
#define inf 0xfffffff
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
typedef long long LL;
typedef pair<int,int> P;

struct edge{
	int from,to,cost;
	edge(){	}
	edge(int from,int to,int cost):from(from),to(to),cost(cost){}
};

bool cmp(const edge& a,const edge& b){
	return a.cost>b.cost;
}


vector<edge> edges(10005);

int N,R;

//并查集
vector<int> fa(MAXN*2,-1);//元素的秩为x+MAXN

int findFa(int x){
	return fa[x]==-1?x:(fa[x]=findFa(fa[x]));
}

void combi(int x,int y){
	int fx=findFa(x),fy=findFa(y);
	if(fx!=fy){
		fa[fx]=fy;
	}
}



int main(){
//	freopen("d:\\input.txt","r",stdin);
	int n,N,M,R;
	cin>>n;
	_for(i,0,n){

		fill(fa.begin(),fa.end(),-1);
		scanf("%d %d %d",&N,&M,&R);
//		printf("%d %d %d\n",N,M,R);
		getchar();
		_for(j,0,R){
			scanf("%d %d %d",&edges[j].from,&edges[j].to,&edges[j].cost);
			edges[j].from=MAXN-1-edges[j].from;
			edges[j].to+=MAXN;
		}

		sort(edges.begin(),edges.begin()+R,cmp);

		int ans=10000*(M+N);

		_for(j,0,R){
			edge& e=edges[j];
//			printf("%d %d\n",e.from,e.to);
			if(findFa(e.from)!=findFa(e.to)){
				combi(e.from,e.to);
				ans-=e.cost;
			}
		}
		printf("%d\n",ans);

	}


	return 0;
}
 
