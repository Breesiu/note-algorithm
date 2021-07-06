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
#define MAXN 50005

int N,K;
vector<int> fa(MAXN,0);//0表示未划归分类，-1、-2、-3分别表示ABC三类

void findFa(int x){
	return fa[x]<=0?x:(fa[x]=findFa(fa[x]));
}

void Union(int x,int y){
	int fx=findFa(x);
	int fy=findFa(y);
	if(fx!=fy){
		fa[fx]=fy;
	}
}

vector<int> v(3,0);//表示三种类别的代表元素

int main(){
//	freopen("d:\\input.txt","r",stdin);
	cin>>N>>K;
	int d,x,y;
	int cnt=0;
	_for(i,0,K){
		scanf("%d %d %d",&d,&x,&y);
		if(x<1||x>N||y<1||y>N){
			cnt++;
			continue;
		}
		int fx=findFa(x);
		int fy=findFa(y);

		if(d==1){
			if(fx==fy)continue;
			if(fa[fx]==0&&fa[fy]==0){
				fa[fx]=fy;
			}else if(fa[fx]==0){
				fa[fx]=fy;
			}else if(fa[fy]==0){
				fa[fy]=fx;
			}else{
				if(fa[fx]!=fa[fy]){
					cnt++;
				}else{
					fa[fx]=fy;
				}
			}
		}else{
			if(x==y||fx==fy){
				cnt++;
				continue;
			}
			if(v[0]==0){//一类还没分
				v[0]=fx;fa[fx]=-1;
				v[1]=fy;fa[fy]=-2;
			}else if(v[2]==0){//分了两类
				if(fa[fx]!=0&&fa[fy]==0){
					if(-1-fa[fx]==0){//fx属于第0类
						fa[fy]=v[1];
					}else{//fx属于第1类
						fa[fy]
					}
				}else if(fa[fx]==0&&fa[fy]!=0){
					if(-1-fa[fy]==0){//fy属于第0类

					}else{//fy属于第1类

					}
				}else{
					if(fa[fx]-fa[fy]==1||fa[fx]-fa[fy]==-2){

					}else{
						cnt++;
					}
				}
			}else{//分了三类

			}
		}
	}

	return 0;
}
