# DFS和BFS

## DFS

DFS是一种枚举所有完整路径来遍历所有情况的搜索方法。最佳实现方法：递归。当然也可以自建栈代替递归，但是往往较麻烦，递归相当于调用系统栈，本质一样。

其中一类DFS问题的解法：给定一个序列，枚举这个序列所有的子序列（可以不连续）。

* 例1：01背包问题的DFS解法

  对于每一个物品，DFS有两个分支，遍历所有的分支。当选择物品的综合超过背包容量，说明该路径走入了死胡同，则需要回到最近的一个岔道口。核心代码如下。

注意到每件物品都有两种选择，故时间复杂度是O\(2^n\)，优化的点有，在sumW+W\[index\]小于V时再进入迭代

```cpp
void DFS(int index,int sumW,int sumC){
    if(index==n){已经完成物品选择的处理}
    DFS(index+1,SumW,sumC);//不选第index件物品
    DFS(index+1,SumW+W[index],sumC+C[index]);//选第index件物品
}
```

* 例2：N个整数中选择K个数的和等于X的所有方案，冲突的话选择其平方和最大的一个。用向量记录添加进方案当中的元素，进入DFS下一步的时候将元素入栈。

```cpp
void DFS(int index,int nowK,int sum,int sumSqu){
    if(nowk==k&&sum==x){
        if(sumSqu>maxsumSqu){
            maxsumSqu=sumSqu;
            ans=tmp;
        }
        return;
    }
    if(index==n||nowk>k||sum>x)return;

    //在DFS递归前和递归后分别设置状态和取消状态，是回溯的典型特征。
    //选择index元素
    tmp.push_back(A[index]);
    DFS(index+1,nowk+1,sum+A[index],sumSqu+A[index]*A[index]);
    tmp.pop_back();
    //不选index

    DFS(index+1,nowk,sum,sumSqu);

}
```

* DFS应用之全排列

阿哈算法：将问题形象化为降1-n编号的扑克牌放入n个盒子中，用book\[\]数组记录该数字已经放过。

```cpp
#define maxn 100
int n;
vector<int> book(maxn,0),vec(maxn);
//step表示现在放第step个盒子，n表示全排列总数
void DFS(int step){
    if(step>n)return;
    for(int i=1;i<=n;i++){
        if(!book[i]){
            book[i]=1;
            vec[step]=i;
            DFS(step+1);
            book[i]=0;//DFS关键一步，收回刚放的牌
        }
    }
}

DFS的伪代码如下：
dfs(int step){
    判断边界
    尝试每一种可能{
        标记数组记录该次选择
        DFS(step+1)
        取消标记数组的选择
    }
    返回
}
```

* DFS和BFS配合vis数组，都可以用来求解连通域的个数
* DFS回溯法解n皇后

邓书改进迭代版本，原版见cppSTL。

```cpp
 /*书中写的虽然代码短，但是不好理解是如何实现的，我根据自己的思路写的这个，思路很清晰
     感觉没必要为了少几行代码将思路搞得很不一般，就像归并排序一样，末尾有元素剩余单独处理就好
    循环不变性：初始进入循环的是有效元素，每次根据在栈中有没有找到相同元素判断是否可以入栈
    入栈情况：
        当栈满时，意味着找到了一种结果，记录并输出。然后y不变，x++，当然，如果x也到了最大值，就要回溯（此时的回溯必定可以找到有元素的x非最大值，因为此前的元素各不相同）
        栈不满时，y++,x=0
    不入栈的情况：
        x没达到最大值，x++即可
        x达到了最大值，回溯，回溯到的元素不是第一行最大值时，x++即可，否则，退出循环。这是循环退出的唯一条件
 */
#include<iostream>
#include"string.h"
using namespace std;
//试探回溯法解八皇后问题
struct Queen{
    int x,y;
     Queen(int xx=0,int yy=0):x(xx),y(yy){}
     Queen(Queen& b){x=b.x;y=b.y;}
     bool operator==(Queen b){
         return x==b.x||y==b.y||x+y==b.x+b.y||x-y==b.x-b.y;
     }
};

int find(Queen* solu,Queen& q,int lo,int hi){//查找范围[lo,hi),找不到返回hi
    for(int i=lo;i<hi;i++){
         if(solu[i]==q)return i;
    }
    return hi;
}
void placeQueens(int N){
     Queen* solu=new Queen[N];int top=0;
     //用数组模拟栈,入栈solu[top++]=q;出栈q=solu[--top];
     int nsolu=0;//记录满足条件的答案的数量
     Queen q(0,0);
     solu[top++]=q;q.y++;
     //不断的试探回溯,忒休斯的绳索是栈，入栈是进一步，出栈是退一步
     while(1){
         //循环不变性：初始进入循环的q是有效的
         //首先判断q应该前进（入栈）还是后退（出栈）
        int r=find(solu,q,0,top);
        if(r==top){//前进
            solu[top++]=q;
            //判断是否满足题意，确保下一次循环内的元素满足条件
            if(top==N){//得到满足题意的一个结果
                nsolu++;
                for(int i=0;i<N;i++)printf("%d ",solu[i].x);
                printf("\n");
                //得到下一个有效点，回溯，以进入下一次循环
                while(q.x==N-1&&top>0)q=solu[--top];
                q.x++;
            }else{
                q.y++;q.x=0;
            }
        }else{
            if(q.x==N-1){//说明此种情况不符合条件，应回溯
                while(q.x==N-1&&top>0)q=solu[--top];
                if(top==0&&q.x==N-1)break;
                else q.x++;
            }else{
                q.x++;
            }
        }
    }
     cout<<nsolu;
}
int main(){
    //freopen("d:\\CodeBlockSpace\\input.txt","r",stdin);
    placeQueens(8);
    return 0;
}
```

递归版本

```cpp
class Solution {
public:
    vector<vector<int> > ans;
    vector<vector<string> > strans;
    vector<int> tmp;
    vector<bool> vis;
    bool conflicted(vector<int>& tmp,int x){
        for(int i=0;i<tmp.size();i++){
            if(x==tmp[i])return false;
            if(tmp.size()+x==i+tmp[i])return false;//斜对角线
            if(tmp.size()-x==i-tmp[i])return false;//正对角线
        }
        return true;
    }
    void solve(int step,int n){
        if(step==n){
            ans.push_back(tmp);
            //cout<<ans[0][0]<<endl;
            return;
        }
        for(int i=0;i<n;i++){
            if(!vis[i]){
                if(conflicted(tmp,i)){
                    vis[i]=true;
                    tmp.push_back(i);
                    solve(step+1,n);
                    tmp.pop_back();
                    vis[i]=false;
                }
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vis.resize(n,false);
        fill(vis.begin(),vis.end(),false);
        int step=0;
        solve(step,n);
        for(int i=0;i<ans.size();i++){
            vector<string> strtmp;
            for(int j=0;j<ans[i].size();j++){
                string s;
                for(int k=0;k<n;k++){
                    if(ans[i][j]==k)s+="Q";
                    else s+=".";
                }
                strtmp.push_back(s);
            }
            strans.push_back(strtmp);
        }
        return strans;
    }
};

//思路相同，但是相对更加简单点的方法
//8皇后问题
#define N 8
vector<int> v(N,0);//表示每一行中皇后的位置
int cnt=0;
bool conflict(int step){
    _for(i,0,step){
        if(v[i]==v[step]||v[i]-i==v[step]-step||v[i]+i==v[step]+step)
            return true;
    }
    return false;
}
void DFS(int step){
    if(step==N){
        _for(i,0,N){
            printf("%d ",v[i]);
        }
        printf("\n");
        cnt++;
        return;
    }
    _for(i,0,N){
        v[step]=i;
        if(!conflict(step))
            DFS(step+1);
    }
}
int main(int argc, char** argv) {
    int step=0;
    DFS(step);
    cout<<cnt<<endl;
    return 0;
}
```

## BFS

相比DFS用递归系统栈实现，BFS用自建队列实现。

* BFS的模板

```cpp
void BFS(int s){
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        取出队首元素top
        访问队首元素top
        将队首元素出队
        将top的下一层未入队的节点入队，并标记为已入队
    }
}
```

* 用BFS求m\*n矩阵中连通域的个数。（注意，这里可以用x\[4\],y\[4\]枚举四个方向）
* 迷宫中求S到T的最少步数，用BFS，并且记录节点深度（S深度为0，然后每一层深度是上一层+1）
* 队中元素时是结构体的注意事项，如果直接在队列汇中存储结构体，那么，对队列中的副本的修改不会影响原元素。这就是说，如果需要对队列中的元素进行修改，最好在队列中存储元素的编号而非元素本身，如果数组的话则是下标。
* BFS求二叉树的层次遍历
* BFS求二叉树的最小深度
* BFS判断是否是满二叉树，将空节点也入队，如果出队的是空节点，而此时已经出队了n个元素，则是满二叉树
* m\*n图中的最短路径问题，都可以用BFS来最方便实现

