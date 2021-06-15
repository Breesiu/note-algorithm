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
    const long M = 1e9+7;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%d %d",&N,&K);
        scanf("%s",s);
        ans = 0;
        int mid = (N-1)/2;
        long tmp=1;
        for(int j=mid;j>=0;j--){
            ans += ((s[j]-'a')*tmp)%M;
            ans %= M;
            tmp *= K;
            tmp %= M;
        }
        int j=mid+1;
        bool flag = false;
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
        ans %= M;
        printf("Case #%d: %ld\n",i,ans);
    }
    return 0;
}