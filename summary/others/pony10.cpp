/*

pony.ai一面出了这个题目，需要用递归回溯法

复杂度O(n)
*/
#include <cstdio>
#include <iostream>
using namespace std;
// 递归回溯法
// 复杂度O(n)，递归n次，回溯n次
bool flag;//表示某一个数字选取了不相等的值
bool have_ans;
int n_a=0,n_b=0;

void dfs(int* _a,int* _b,int* num,int step){
  printf("step: %d\n",step);
  for(int i=0;i<n_a;i++)printf("%d ",_a[i]);printf("\n");
  for(int i=0;i<n_a;i++)printf("%d ",_b[i]);printf("\n");
  for(int i=0;i<10;i++)printf("%d ",num[i]);printf("\n");
  if(step<0){
    if(flag)have_ans = true;
    return;
  }
  if(flag){// 前面某个数字已经选取了较小的值，剩下的选最大值即可
    // find max
    for(int i=9;i>=0;i--){
      if(num[i]>0){
        _a[step] = i;
        num[i] --;
        dfs(_a,_b,num,step-1);
        break;
      }
    }
  }else{
    if(num[_b[step]]!=0){ // 可以选相等的值
      _a[step] = _b[step];
      num[_b[step]]--;
      dfs(_a,_b,num,step-1); //递归
      num[_b[step]]++; //回溯
    }
    if(have_ans)return;
    // 回溯找更小的值
    int i=_b[step]-1;
    while(i>=0){
      if(num[i]>0)break;
      i--;
    }
    if(i<0)return;//没有更小的值，回溯到上一步
    flag = true;//找到更小的值
    _a[step] = i;
    num[i]--;
    dfs(_a,_b,num,step-1);
    num[i]++;
  }
}

long long solve_fun(long long a, long long b){
  int _a[18],_b[18],num[10];
  n_a=0,n_b=0;
  for(int i=0;i<10;i++)num[i]=0;
  for(int i=0;i<18;i++){
    if(a!=0){n_a++;}
    if(b!=0){n_b++;}
    _b[i] = b%10;
    if(a!=0)num[a%10] ++;
    a /= 10;
    b /= 10;
  }
  long long ans=0;
  printf("%d %d\n",n_a,n_b);
  if(n_a < n_b){
    sort(_a,_a+n_a);
    for(int i=n_a-1;i>=0;i--){
      ans *= 10;
      ans += _a[i];
    }
    return ans;
  }else if(n_a > n_b ){
    return 0;
  }else{
    flag = false;
    have_ans = false;
    dfs(_a,_b,num,n_b-1);
    if(!have_ans)return -1;
    else{
      for(int i=n_a-1;i>=0;i--){
        ans *= 10;
        ans += _a[i];
      }
      return ans;
    }
  }
}

int main(){
    freopen("in.txt","r",stdin);
    long long a;
    long long b;
    cin >> a >> b;
    cout << solve_fun(a,b) << endl;
    return 0;
}