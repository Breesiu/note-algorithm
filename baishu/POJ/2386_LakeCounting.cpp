//普通连通域问题
//#include<bits/stdc++.h>//包含全部头文件 POJ不支持
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

#define MAXN 1002
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define M 100
#define inf 0x7fffffff
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
typedef long long LL;

int _i[8]={1,-1,0,0,-1,-1,1,1},_j[8]={0,0,1,-1,-1,1,-1,1};
int n,m;
char G[100][100];
bool vis[100][100]={0};
bool valid(int i,int j){
	return i>=0&&i<n&&j>=0&&j<m&&!vis[i][j];
}
int DFS(int i,int j){
	vis[i][j]=true;
	_for(k,0,8){
		int ni=i+_i[k],nj=j+_j[k];
		if(valid(ni,nj))DFS(ni,nj);
	}
}
int main(){
	//freopen("d:\\input.txt","r",stdin);

	cin>>n>>m;getchar();
	memset(vis,0,sizeof(vis));
	_for(i,0,n){
		_for(j,0,m){
			G[i][j]=getchar();
			if(G[i][j]=='.')vis[i][j]=true;
			//printf("%c",G[i][j]);
		}
		getchar();
		//printf("\n");
	}
	int cnt=0;
	_for(i,0,n){
		_for(j,0,m){
			if(!vis[i][j]){
				cnt++;
				DFS(i,j);
			}
		}
	}
	printf("%d\n",cnt);

	return 0;
}
