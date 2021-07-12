//思维转换：两只蚂蚁相遇后，可以认为是它们保持原样交错前进。思维转变后，代码如此简单。
//这个题目是考察想象力的经典例子
int main(){
	//freopen("d:\\input.txt","r",stdin);
	int t,L,n,tmp;
	cin>>t;
	while(t--){
		cin>>L>>n;
		int mintime=0,maxtime=0;
		_for(i,0,n){
			scanf("%d",&tmp);//用cin会超时
			mintime=max(mintime,min(tmp,L-tmp));
			maxtime=max(maxtime,max(tmp,L-tmp));

		}
		printf("%d %d\n",mintime,maxtime);
	}
	return 0;
}
