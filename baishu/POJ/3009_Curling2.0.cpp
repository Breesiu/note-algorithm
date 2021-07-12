//被碰撞后障碍会消失，前面有障碍的话不能投
//终点是一个摩擦力很大的区域，冰壶若到达终点3，就会停止在终点的位置不再移动
//想不通哪里错了

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
#define MAXN 25

vector<vector<bool> > vis(MAXN,vector<bool>(MAXN,false));
vector<vector<int> > grid(MAXN,vector<int>(MAXN));

int W,H;
int x0,y0,x1,y1;
int cnt,ans;
int xx[4]={0,1,0,-1},yy[4]={1,0,-1,0};
bool isLegal(int y,int x){
	return x>=0&&x<W&&y>=0&&y<H;
}
struct node{
	int y,x;
	node(int y,int x):y(y),x(x){}
};
vector<node> path,anspath;


void DFS(int y,int x){
//	printf("cnt:%d y=%d x=%d y1=%d x1=%d\n",cnt,y,x,y1,x1);
	if(cnt>10)return;
	if(y==y1&&x==x1){
		if(cnt<ans){
			ans=cnt;
			anspath=path;
		}
		return;
	}

	_for(i,0,4){
		int ty=y,tx=x;
		while(isLegal(ty+yy[i],tx+xx[i])&&grid[ty+yy[i]][tx+xx[i]]==0){
			ty+=yy[i];tx+=xx[i];
			if(ty==y1&&tx==x1)break;
		}
		if(isLegal(ty+yy[i],tx+xx[i])){
			grid[ty+yy[i]][tx+xx[i]]=0;
		}
		if(!vis[ty][tx]&&!(ty==y&&tx==x)){
			vis[ty][tx]=true;
			cnt++;
			path.push_back(node(ty,tx));
			DFS(ty,tx);
			cnt--;
			path.pop_back();
			vis[ty][tx]=false;
		}
		if(isLegal(ty+yy[i],tx+xx[i])){
			grid[ty+yy[i]][tx+xx[i]]=1;
		}
	}
}

int main(){
//	freopen("d:\\input.txt","r",stdin);

	while(cin>>W>>H){
		if(W==0)break;
		_for(i,0,H){
			_for(j,0,W){
				cin>>grid[i][j];
				vis[i][j]=false;
				if(grid[i][j]==2){
					y0=i;x0=j;
					grid[i][j]=0;
				}
				if(grid[i][j]==3){
					y1=i;x1=j;
					grid[i][j]=0;
				}
//				cout<<grid[i][j];
			}
//			cout<<endl;
		}

		cnt=0,ans=inf;

		DFS(y0,x0);

//		_for(i,0,anspath.size()){
//			printf("->(%d,%d)",anspath[i].y,anspath[i].x);
//		}
//		printf("\n");

		if(ans!=inf&&ans<=10){
			printf("%d\n",ans);
		}else{
			printf("-1\n");
		}
	}

	return 0;
}
