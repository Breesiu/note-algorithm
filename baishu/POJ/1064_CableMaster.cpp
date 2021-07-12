#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int N,K;
vector<double> stock;
bool valid(double len){
    int cnt=0;
    for(int i=0;i<N;i++){
        cnt += int(stock[i]/len);
    }
    return cnt >= K;
}
int main(){
    freopen("in.txt","r",stdin);
    
    scanf("%d %d",&N,&K);
    double t;
    for(int i=0;i<N;i++){
        scanf("%lf",&t);
        stock.push_back(t);
    }
    double lo=0.001,hi=stock[0];
    while(hi-lo>0.0001){
        double mi = (lo+hi)/2;
        if(valid(mi)){
            lo = mi;
        }else{
            hi = mi;
        }
    }
    printf("%.2lf\n",lo);
    return 0;
}