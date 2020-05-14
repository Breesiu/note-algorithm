# 四.解决面试题的思路

* 编程前想好思路
* 画图可以让抽象问题形象化
* 举例让抽象问题具体化
* 分解让问题简单化

## 19.二叉树的镜像 p125

递归思路，先镜像左右孩子再镜像自己。

```cpp
void Mirror(TreeNode* pRoot) {
    if(!pRoot)return;
    Mirror(pRoot->left);
    Mirror(pRoot->right);
    TreeNode* tmp=pRoot->left;
    pRoot->left=pRoot->right;
    pRoot->right=tmp;
}
```

## 20.顺时针打印矩阵 p127

书上写的不是很好，类似迷宫问题需要设置方向矩阵。

防止审题不细致，比如人家可没说矩阵是n*n，实际上是n*m的。

```cpp
int n,m;
bool islegal(int i,int j,vector<vector<bool> >& vis){
    return i>=0&&i<n&&j>=0&&j<m&&!vis[i][j];
}
vector<int> printMatrix(vector<vector<int> > matrix) {
    n=matrix.size();
    m=matrix[0].size();
    int x[4]={1,0,-1,0},y[4]={0,1,0,-1};
    vector<int> ans;
    vector<vector<bool> > vis(n,vector<bool>(m,false));
    ans.push_back(matrix[0][0]);
    vis[0][0]=true;
    int i=0,j=0;
    while(ans.size()!=n*m){
        for(int k=0;k<4;k++){
            while(islegal(i+y[k],j+x[k],vis)){
                i+=y[k];j+=x[k];
                ans.push_back(matrix[i][j]);
                vis[i][j]=true;
            }
        }
    }
    return ans;
}
```

## 21.包含min函数的栈 p132

典型的用空间换时间的思路

```cpp
    stack<int> s1,s2;
    void push(int value) {
        s1.push(value);
        if(s2.empty())s2.push(value);
        else if(s2.top()>value)s2.push(value);
        else s2.push(s2.top());
    }
    void pop() {
        s1.pop();
        s2.pop();
    }
    int top() {
        return s1.top();
    }
    int min() {
        return s2.top();
    }
```

## 22.栈混洗 p134

熟悉的题目也不能掉以轻心

```cpp
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    stack<int> s;
    int j=0,i=0;
    while(i<pushV.size()){
        s.push(pushV[i++]);
        while(!s.empty()&&s.top()==popV[j]){s.pop();j++;}
    }
    return s.empty();
}
```

## 23.从上到下打印二叉树 p137

用队列实现层次遍历

## 24.二叉搜索树的后续遍历序列 p140

输入一个整数数组，判断该数组是不是某二叉搜索树的后续遍历的结果。

不用建树，用中序和后续可以生成唯一二叉树，以此为判断依据。

```cpp
bool fun(int inlo,int inhi,int postlo,int posthi,vector<int>& in,vector<int>& post){
    if(inlo>=inhi)return true;
    int t=post[posthi-1],r;
    for(r=inlo;r<inhi;r++){
        if(in[r]==t)break;
    }
    if(r==inhi)return false;
    return fun(inlo,r,postlo,postlo+r-inlo,in,post)&&fun(r+1,inhi,posthi-1-(inhi-r-1),posthi-1,in,post);
}
bool VerifySquenceOfBST(vector<int> sequence) {
    vector<int> in=sequence;
    vector<int>& post=sequence;
    sort(in.begin(),in.end());
    int n=in.size();
    if(n==0)return false;
    return fun(0,n,0,n,in,post);
}
```

## 25.二叉树中和为给定值的路径 p143

DFS，或者迭代版后序遍历

## 26.复杂链表的复制 p147

在复杂链表中，每个节点除了有一个next指针外，还有一个random指针。

思路2：用空间换时间，hash表。用hash表建立新地址和原地址的映射关系，第一次遍历时赋值节点，第二次遍历时设置random指针。

思路3：不用辅助空间。分三步，每一个顶点在其后复制一个相同顶点，然后设置random指针，最后再把链表奇偶序分开。

```cpp
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
map<RandomListNode*,RandomListNode*> mm;
RandomListNode* Clone(RandomListNode* p){
    if(!p)return p;
    RandomListNode* cp=new RandomListNode(p->label);
    mm[p]=cp;
    RandomListNode* i=p;
    RandomListNode* j=cp;
    while(i->next){
        i=i->next;
        j->next=new RandomListNode(i->label);
        j=j->next;
        mm[i]=j;
    }
    i=p;j=cp;
    while(i){
        j->random=mm[i->random];
        i=i->next;j=j->next;
    }
    return cp;
}
```

## 27.二叉搜索树与双向链表 p151

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的节点，只能条恒树中节点指针的指向。

改进中序遍历，保存遍历的上一个节点即可。

```cpp
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
TreeNode* last;
void inTrav(TreeNode* p){
    if(!p)return;
    inTrav(p->left);
    if(last){
        last->right=p;
        p->left=last;
    }
    last=p;
    inTrav(p->right);
}
TreeNode* Convert(TreeNode* p){
	if(!p)return p;
    last=NULL;
    TreeNode* ans=p;while(ans->left)ans=ans->left;
    inTrav(p);
    return ans;
}
```
## 28.字符串的排列 p154

输入一个字符串，打印出该字符串的所有排列。

方法一：DFS全排列

```cpp
vector<string> ans;
vector<bool> vis;
int n;
string tmp;
void DFS(string& str,int step){
    if(step==n){
        ans.push_back(tmp);
        return;
    }
    char c='!';
    for(int i=0;i<n;i++){
        if(!vis[i]&&str[i]!=c){
            vis[i]=true;
            tmp+=str[i];
            DFS(str,step+1);
            tmp.pop_back();
            vis[i]=false;
            c=str[i];
        }
    }
}
vector<string> Permutation(string str) {
    sort(str.begin(),str.end());
    n=str.size();
    if(n==0)return ans;
    vis.resize(n);
    fill(vis.begin(),vis.end(),false);
    DFS(str,0);
    return ans;
}
```

方法二：DFS回溯，逐个交换

```cpp
vector<string> ans;
int n;
void DFS(string& str,int step){
    if(step==n-1){
        ans.push_back(str);
        return;
    }
    for(int i=step;i<n;i++){
        if(i!=step&&str[step]==str[i])continue;//避免重复的关键代码
        swap(str[step],str[i]);
        DFS(str,step+1);
        swap(str[step],str[i]);
    }
}
vector<string> Permutation(string str) {
    sort(str.begin(),str.end());
    n=str.size();
    if(n==0)return ans;
    DFS(str,0);
    sort(ans.begin(),ans.end());
    return ans;
}
```