# 第七章 暴力求解法

## 7.3 自己生成
### 7.3.1 增量构造法

```cpp
int n;//元素总的个数、不同元素的数目
vector<int> P,R;//P表示元素的值,R是元素的秩的集合
void print_subset(int cur){
    _for(i,0,R.size())printf("%d ",P[R[i]]);
    printf("\n");
    int s=cur?R.back()+1:0;//这里用到了定序的技巧，避免了同一个集合枚举两次
    _for(i,s,n){
        R.push_back(i);
        print_subset(cur+1);
        R.pop_back();
    }
}
int main(){
    freopen("d:\\input.txt","r",stdin);
    cin>>n;
    P.resize(n);
    _for(i,0,n)cin>>P[i];
    print_subset(0);
    return 0;
}
```

### 7.3.2 位向量法

```cpp
void print_subset(int cur){
    if(cur==n){输出序列；返回；}//当B[i]==1时表示该元素在集合当中
    B[cur]=1;//选当前元素
    print_subset(cur+1);
    B[cur]=2;//不选当前元素
    print_subset(cur+1);
}
```

### 7.3.3 二进制法

     集合与二进制数的一一对应关系
* A&B A|B A^B 分别对应集合的交、并、对称差。
```cpp
void print_subset(int n,int s){
    _for(i,0,n)
        if(s&1<<i)printf("%d ",i);
    printf("\n");
}
_for(i,0,1<<n)print_subset(n,i);
```