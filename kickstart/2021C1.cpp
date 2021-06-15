#include <cstdio>
#include <algorithm>
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
using namespace std;

int main(){
    freopen("in.txt","r",stdin);
    int T,N,K;
    long ans;
    char s[100005];
    long preK[100005];
    preK[0] = 1;
    long M = 1e9+7;

    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%d %d",&N,&K);
        scanf("%s",s);
        for(int i=1;i<100005/2 && i<=N/2;i++){
            preK[i] = (preK[i-1]*K)%M;
        }
        if(N==1){
            ans = min(s[0]-'a',K);
        }else{
            int mid = (N-1)/2;
            ans = 0;
            for(int j=0;j<=mid;j++){
                ans += (s[j]-'a')*preK[mid-j]%M;
                ans %= M;
                // printf("%d %ld\n",j,ans);
            }
            int j=mid + 1;
            bool flag=false;
            while(j<N){
                if(s[N-1-j]<s[j]){
                    flag = true;
                    break;
                }else if(s[N-1-j]>s[j]){
                    flag = false;
                    break;
                }
                j++;
            }
            if(flag)ans++;
        }
        ans %= M;
        printf("Case #%d: %ld\n",i,ans);
    }
    return 0;
}