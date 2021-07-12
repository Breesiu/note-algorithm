#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

typedef long long LL;
#define _for(i,lo,hi) for(int i=(lo);i<(hi);i++)
#define inf 0x3fffffff
#define MAXN 25

//DFS即可
int cnt=1;

vector<vector<char> > grid(MAXN,vector<char>(MAXN));
int W,H;
int xx[4]={0,1,0,-1},yy[4]={1,0,-1,0};
bool isLegal(int y,int x){
	return x>=0&&x<H&&y>=0&&y<W&&grid[y][x]=='.';
}

void DFS(int y,int x){
	_for(i,0,4){
		int ny=y+yy[i],nx=x+xx[i];
		if(isLegal(ny,nx)){
			cnt++;grid[ny][nx]='#';
			DFS(ny,nx);
		}
	}
}


int main(){
//	freopen("d:\\input.txt","r",stdin);

	int x0,y0;
	string s;
	while(cin>>H>>W){
		if(W==0)break;
		_for(i,0,W){
			cin>>s;
			_for(j,0,H){
				grid[i][j]=s[j];
//				cout<<grid[i][j];
				if(grid[i][j]=='@'){
					y0=i;x0=j;
				}
			}
//			cout<<endl;
		}
		cnt=1;
		DFS(y0,x0);
		cout<<cnt<<endl;
	}


	return 0;
}
