#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
using namespace std;
#define MAXN 1000005
int main(){
    freopen("in.txt","r",stdin);
    int T,G;
    bool is_prime[MAXN];
    vector<int> prime;
    memset(is_prime,1,MAXN);
    for(int i=3;i<MAXN;i+=2){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j=i*2;j<MAXN;j+=i){
                is_prime[j] = false;
            }
        }
    }
    long ans;
    int rank_prime;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%d",&G);
        printf("%d\n",G);
        ans = 1;
        rank_prime = 0;
        while(G%2==0)G/=2;
        while(G!=1){
            printf("%d\n",G);
            int tmp=1;
            while(G%prime[rank_prime]==0){G/=prime[rank_prime];tmp++;}
            rank_prime++;
            ans *= tmp;
            printf("%d %d\n",tmp,rank_prime);
        }
        printf("Case #%d: %ld\n",i,ans);
    }
    return 0;
}