# 剑指offer

考察重点：
* 边界情况
* 递归和迭代、子问题的定义和求解

# 二.面试需要的基础知识

## 3.二维数组中的查找 p38

在一个二维数组中，每一行都按照从左到右的递增顺序，每一列车都是按照从下到下的递增顺序。输入一个整数，需要判断该数组中是否包含该整数。

从左下角到右上角，或者从右上角到左下角，相当于一个二叉判定树，不断的缩小题目范围

```cpp
bool Find(int target, vector<vector<int> > array) {
    int m=array.size(),n=array[0].size();
    int i=0,j=n-1;//行、列，从右上角开始
    while(i<m&&j>=0){
        if(array[i][j]==target)return true;
        else if(array[i][j]<target)i++;
        else j--;
    }
    return false;
}
```

## 4.替换空格 p44

将字符串中所有空格替换为%20,不允许新开数组。从前往后替代会覆盖，先计算空格个数，然后从后往前替代即可。

```cpp
void replaceSpace(char *str,int length) {
    int cnt=0;
    for(int i=0;i<length;i++){
        if(str[i]==' ')cnt++;
    }
    int i=length+cnt*2-1,j=length-1;
    while(j>=0){
        if(str[j]==' '){
            str[i--]='0';
            str[i--]='2';
            str[i--]='%';
            j--;
        }else
            str[i--]=str[j--];
    }
}
```

## 5.从尾到头打印链表 p51

输入一个链表的头结点，从尾到头反过来打印每个节点的值。

存到向量中后反转即可，比网上很多人说的栈实现要简单

## 6.重建二叉树 p55

略

## 7.用两个栈实现队列 p59

push算法直接插入到stack1即可，不用将stack2倒过来，pop直接删除stack2顶部即可，stack2为空是从stack1调入元素。

```cpp
class Solution{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                int t=stack1.top();stack1.pop();
                stack2.push(t);
            }
        }
        int t=stack2.top();stack2.pop();
        return t;
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};
```

## 8.旋转数组的最小元素 p66

输入一个递增数组的一个旋转，输出该数组中的最小值。

二分，判断中间元素是位于前一段递增数组还是后一段递增数组。本题难点在于特殊情况的讨论，即中间元素和前后元素相等的情况。比如{1 0 1 1 1}{1 1 1 0 1}这两种情况，这种情况存在，必然意味着前半部分或者后半部分的数字全部都一样，所以，可以直接顺序查找最小值，当然，这种情况下极端复杂度是O(n).

```cpp
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size == 0){
            return 0;
        }
        int left = 0,right = size - 1;
        int mid = 0;
        while(rotateArray[left] >= rotateArray[right]){
            if(right - left == 1){
                mid = right;
                break;
            }
            mid = left + (right - left) / 2;
            // 无法确定中间元素是属于前面还是后面的递增子数组,只能顺序查找
            if(rotateArray[left] == rotateArray[right] && rotateArray[left] == rotateArray[mid]){ 
                return MinOrder(rotateArray,left,right);
            }
            if(rotateArray[mid] >= rotateArray[left]){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        return rotateArray[mid];
    }
private:
    // 顺序寻找最小值
    int MinOrder(vector<int> &num,int left,int right){
        int result = num[left];
        for(int i = left + 1;i < right;++i){
            if(num[i] < result){
                result = num[i];
            }
        }
        return result;
    }
};
```

## 9.斐波那契数列

斐波那契数列考察的点无非就是迭代和递归，以及递归方法如何将复杂度。

其次，就是采用矩阵乘法和快速幂，在logn时间内求出第n项。

## 10.二进制中1的个数 p78

```cpp
//负数用补码表示，也要考虑到。所以，如果是把数右移判断最低位可能会陷入死循环。
 int  NumberOf1(int n) {
     int cnt=0,flag=1;
     while(flag!=0){
         cnt+=(flag&n)?1:0;
         flag=flag<<1;//非常坑的地方在于这里只写flag<<1居然flag的值在下次循环时并咩有改变
     }
     return cnt;
 }
//再进一步：把一个整数减去1，在和原来的数做与运算，就会把整数最右边的一个1变成0，那么，整数中有多少个1，就可以进行多少次操作。
int  NumberOf1(int n) {
    int cnt=0;
    while(n){
        cnt++;
        n=(n-1)&n;
    }
    return cnt;
}
```

# 三.高质量代码

* 规范性：清晰的书写、清晰的布局、合理的命名
* 完整性：功能测试、边界测试、负面测试
* 3种错误处理的方式：返回值、全局变量、异常

## 11.数值的整数次方 p90

鲁棒性：要考虑输入的边界条件等如何处理，比如指数是负数和0的情况。以及底数为0的情况等等，要让面试官明白，这些边界情况和违法输入自己都考虑到了

基础知识：判断底数是否为0时不能用==，因为浮点数误差，应该写函数判断其差在1e-8以内或其他。

```cpp
double Power(double base, int exponent) {
    if(exponent==0)return 1;
    if(exponent==1)return base;
    if(exponent<0){
        double f=Power(base,-exponent);
        f=1/f;
        return f;
    }
    if(exponent&1){
        double f=Power(base,exponent/2);
        return base*f*f;
    }else{
        double f=Power(base,exponent/2);
        return f*f;
    }
}
```

## 12.打印1到最大的n位数 p94

鲁棒性：题目没有说n的取值范围，需要考虑大数问题，没有注意到这个就跳进了面试官的陷阱。输入检测也是要考虑的，比如输入了0和-1

算法思想：在字符串模拟大数加法的解法，虽然能算，但是代码很长，想要十几分钟写的完全正确也不容易。用递归的全排列算法更加简洁。

所以，这个题目就转化成了dfs全排列

## 13.在O\(1\)时间内删除链表节点 p99

`void deleteNode(ListNode* head,ListNode* p)`

从头遍历的复杂度显然是O\(n\)，所以需要转变思路：是否一定要删除节点呢？可以把下一个节点的值赋值到这个节点，然后删除下一个节点即可。

鲁棒性：该节点是尾节点，或者只有一个节点。

## 14.调整数组顺序使奇数位于偶数前面 p102

初级方法：不需要额外空间，只需要维护两个指针，第一个指针初始化时指向数组的第一个数字，第二个指向最后一个数字，发现偶数在奇数前面，交换二者即可。

这种方法的思路类似于快速排序中的partition操作。

对于资深程序员，还要考虑可扩展性，比如题目改为负数放在正数前面等，把比较函数作为函数指针传入该方法，重定义排序规则时传入不同的比较函数即可，而主函数不需要任何改动。

## 15.链表中倒数第k个节点 p107

鲁棒性：双指针法，但是要考虑鲁棒性，即节点数不足k个，链表为空的特殊情况。

举一反三：类似双指针法，在链表中还经常用到快慢指针。

## 16.反转链表 p112

鲁棒性：面试时至少应考虑到输入的链表为空的边界情况，以及注意到在代码中防止链表断链。自己写好代码一定要先做好测试。

## 17.合并两个排序链表 p114

鲁棒性：应考虑到输入的空指针的边界情况。

## 18.树的子结构 p117

鲁棒性：树中涉及很多指针，一不留神就会留下安全隐患。

考察对二叉树遍历的运用和递归算法。

思路：第一步在树A中查找和树B根节点值一样的节点，第二步判断以该点为根是否和B相同。

```cpp
bool flag;
void postTrav(TreeNode* p1,TreeNode* p2){
    if(!p1)return;
    if(p1->val==p2->val){
        flag=true;
        fun(p1,p2);
    }
    if(!flag)postTrav(p1->left,p2);
    if(!flag)postTrav(p1->right,p2);
}
void fun(TreeNode* p1,TreeNode* p2){
    if(!p2)return;
    if(!p1||p1->val!=p2->val)flag=false;
    if(flag)fun(p1->left,p2->left);
    if(flag)fun(p1->right,p2->right);
}
bool HasSubtree(TreeNode* p1, TreeNode* p2){
    if(!p2||!p1)return false;
    postTrav(p1,p2);
    return flag;
}
```

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

防止审题不细致，比如人家可没说矩阵是n_n，实际上是n_m的。

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

判断给定的两个数组是不是栈混洗的结果，直接模拟即可。

另外，如果给出一个数组，输出全部栈混洗的序列，这时候还是需要用栈和DFS来模拟。

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

# 五.优化时间和空间效率

## 29.数组中出现超过一半的数字 p163

解法一：类似快排partition，O\(n\)找中位数，这种方法适用于所有序列找中位数。

解法二：根据数组特点，如果两个数字出现次数相同，则可删除该数字，数组中最后留下的元素即为结果。

## 30.最小的K个数 p167

解法一：和上题一致，用partition找第k大的元素，其左边的元素即为答案。此解法在允许修改数组数据的时候可用。 牛客网OJ系一直过不了的原因是错误检测，需判断输入参数是否合法。

解法二：O\(nlogk\)，先创建一个大小为k的大顶堆，然后将其他元素如果比堆顶小的话，删除堆顶，插入该元素。该方法特别适合处理海量数据，比如数据无法一次性读入内存，那么解法一就失效了。这个堆既可以用priority\_queue实现，也可以用set实现（STL中set是用RB树实现的）

## 31.连续子数组的最大和 p171

动态规划

## 32.从1到n中1出现的次数 p174

PAT原题，一位一位计算，需要思路清晰，自己写功能测试、边界测试。

```text
int NumberOf1Between1AndN_Solution(int n){
    int r=1,cnt=0;
    while(n/r!=0){
        cnt+=n/(10*r)*r;
        if(n/r%10==1)cnt+=n%r+1;
        else if(n/r%10>1)cnt+=r;
        r*=10;
    }
    return cnt;
}
```

## 33.把数组排成最小的数 p177

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印出能拼接出的所有数字中最小的一个。例如输入数组{3,32,321}，则打印出这3个数字能排成的最小数字321323.

掌握用stringstream将数字转换为字符串的方法。用ss.str\(""\)进行字符串清空，clear不管用。

证明此方法的有效性：首先证明定义的比较是有效的，需要证明自反性、对称性、传递性；然后可以用反证法证明此方法得到的数组是最小的。

```cpp
static bool cmp(const string& a,const string& b){
    return a+b<b+a;
}
string PrintMinNumber(vector<int> nums) {
    stringstream ss;
    int n=nums.size();
    vector<string> strs(n);
    for(int i=0;i<nums.size();i++){ss<<nums[i];strs[i]=ss.str();ss.str("");}
    sort(strs.begin(),strs.end(),cmp);
    string ans;
    for(int i=0;i<nums.size();i++)ans+=strs[i];
    return ans;
}
```

## 34.丑数 p182

如何按顺序生成所有的丑数呢？例如6,8是丑数，14不是。习惯上把1当做第一个丑数。在已有的丑数中，所有的数分别乘2,3,5可以得到所有的候选丑数，从中取最小的即可。

维护三个指针，分别指向该次候选的乘2,3,5的丑数

注意处理重复的问题。

```cpp
int GetUglyNumber_Solution(int n) {
    vector<int> v(n+1);
    v[0]=1;
    int r2=0,r3=0,r5=0;
    for(int i=1;i<n;i++){

        if(v[r2]*2==v[i-1])r2++;
        if(v[r3]*3==v[i-1])r3++;
        if(v[r5]*5==v[i-1])r5++;

        if(v[r2]*2<=v[r3]*3&&v[r2]*2<=v[r5]*5){
            v[i]=v[r2]*2;r2++;
        }else if(v[r2]*2>=v[r3]*3&&v[r3]*3<=v[r5]*5){
            v[i]=v[r3]*3;r3++;
        }else if(v[r2]*2>=v[r5]*5&&v[r3]*3>=v[r5]*5){
            v[i]=v[r5]*5;r5++;
        }
    }
    return v[n-1];
}
```

## 35.第一个只出现一次的字符 p186

打表记录各个字符出现的次数，遍历两次即可。

```cpp
int FirstNotRepeatingChar(string str) {
    int n=str.size(),ans=-1;
    int v[256]={0};
    for(int i=0;i<n;i++)v[str[i]]++;
    for(int i=0;i<n;i++)if(v[str[i]]==1){ans=i;break;}
    return ans;
}
```

## 36.数组中的逆序对 p189

方法一：类似归并排序，时间O\(nlogn\)，空间O\(n\)

```cpp
int cnt;
void merge(vector<int>& data,int lo,int mi,int hi){
    int i=0,j=mi,k=lo;
    vector<int> tmp(mi-lo);
    for(int t=0;t<mi-lo;t++)tmp[t]=data[lo+t];
    while(i<mi-lo&&j<hi){
        if(tmp[i]<=data[j]){
            data[k]=tmp[i];
            i++;k++;
        }else{
            data[k]=data[j];
            cnt+=(mi-lo-i);
            cnt%=M;
            k++;j++;
        }
    }
    while(i<mi-lo){data[k]=tmp[i];i++;k++;}
}
void fun(vector<int>& data,int lo,int hi){
    if(lo>=hi-1)return;
    int mi=(lo+hi)/2;
    fun(data,lo,mi);
    fun(data,mi,hi);
    merge(data,lo,mi,hi);
}
int InversePairs(vector<int> data) {
    cnt=0;
    fun(data,0,data.size());
    return cnt;
}
```

方法二：树状数组

此方法中如果数据中有负数或者离散很大，需要首先进行离散化处理。因为树状数组中的元素对应的是1-n，不包括负数和0.

## 37.两个链表的第一个公共节点 p193

略

# 六.面试中的各项能力

* 沟通能力：介绍自己的项目经验时思路清晰、重点突出、观点明确
* 学习能力：IT是发展很快的学科，要让面试官看到自己的学习力
* 善于学习沟通的人也善于提问。对面试题有疑问时，要问清楚问题表述，确保自己理解正确。高质量的问题也能给自己加分。比如丑数的问题，不确定1是不是丑数，这个就得询问。LCA的问题，没有给出二叉树的结构的话要问清楚，根据不同的结构采用不同的方法。
* 知识迁移能力：即举一反三，往往是经典问题的变形。

## 38.数字在排序数组中出现的次数 p204

既然是排序数组，那么必然二分查找。把语义设置为找到小于等于k的最大秩，则search\(k\)-search\(k-1\)即为所求。

## 39.二叉树的深度 p207

直接递归即可，先求出孩子的深度，自己的深度是其中较大者加一。

```cpp
int dep(TreeNode* p,int t){
    if(!p)return t;
    return max(dep(p->left,t+1),dep(p->right,t+1));
}
int TreeDepth(TreeNode* pRoot){
    return dep(pRoot,0);
}
```

拓展：判断平衡二叉树（注意每个节点遍历一次即可）

```cpp
int Balanced(TreeNode* p){
    if(!p)return 0;
    int left=Balanced(p->left);
    if(left==-1)return -1;
    int right=Balanced(p->right);
    if(right==-1)return -1;
    if(abs(left-right)<=1)return max(left,right)+1;
    else return -1;
}
bool IsBalanced_Solution(TreeNode* p) {
    return Balanced(p)!=-1;
}
```

## 40.数组中只出现一次的数字 p211

一个整型数组里除了两个数字之外，其他的数字都出现了两次。找出这个只出现一次的数字。要求时间复杂度是O\(n\)，空间O\(1\)。

可以用位运算实现，如果将所有所有数字相异或，则最后的结果肯定是那两个只出现一次的数字异或的结果，所以根据异或的结果1所在的最低位，把数字分成两半，每一半里都还有只出现一次的数据和成对出现的数据。这样继续对每一半相异或则可以分别求出两个只出现一次的数字

```cpp
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    int f=0,n=data.size();
    for(int i=0;i<n;i++)f^=data[i];
    int t=f&(-f),nf=f;
    for(int i=0;i<n;i++)if(data[i]&t)f^=data[i];
    *num1=f;
    *num2=f^nf;
}
```

## 41.和为s的两个数组 VS 和为s的连续整数序列 p214

双指针

## 42.翻转单词顺序

两次翻转，先翻转句子，然后再翻转单词。

```cpp
string ReverseSentence(string s) {
    reverse(s.begin(),s.end());
    for(int i=0;i<s.size();i++){
        int j=i;
        while(j<s.size()&&s[j]!=' ')j++;
        reverse(s.begin()+i,s.begin()+j);
        i=j;
    }
    return s;
}
```

扩展：左旋字符串。比如输入字符串"abcdefg"和整数2，返回左旋2位的结果是"cdefgab"。

## 43.n个骰子的点数 p223

将n个骰子扔在地上，所有的骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

方法一:递归。类似全排列计算所有可能的情况的和，将和在数组中计数。

方法二：思路1这种方法保存了很多冗余信息，比如我们并不需要知道和分别是每个骰子的点数为几合成的。所以，联想到动态规划中的无后效性。当我们已经知道n-1个骰子的点数分布的时候，再加一个骰子，可以求出n个骰子的点数分布。

注意数据用LL，否则回溢出

```cpp
LL gcd(LL x,LL y){
    return x%y==0?y:gcd(y,x%y);
}
int main(){
    //freopen("d:\\input.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    LL V[25][150]={0};
    vector<int> v(6*n+1);
    _for(i,1,7)V[1][i]=1;
    _for(i,2,n+1){
        _for(j,i,6*i+1){
            _for(k,1,7){
                if(j-k>0)V[i][j]+=V[i-1][j-k];
                else break;
            }
            //printf("%d %d %lld\n",i,j,V[i][j]);
        }
    }
    LL cnt=0,sum=0;
    _for(i,n,6*n+1){
        sum+=V[n][i];
        if(i>=m)cnt+=V[n][i];
    }
    if(m<=n)printf("1");
    else if(m>6*n)printf("0");
    else{
        LL t=gcd(cnt,sum);
        printf("%lld/%lld",cnt/t,sum/t);
    }
    return 0;
}
```

## 44.扑克牌顺子 p226

数组排序后统计0的个数，如果统计空缺的个数小于等于0的个数，就是连续的。同时要排除数组中有非0数相同的情况。

```cpp
bool IsContinuous( vector<int> ns ) {
    if(ns.size()!=5)return false;
    sort(ns.begin(),ns.end());
    int cnt=0,i=0;
    for(;i<5;i++)if(ns[i]==0)cnt++;else break;
    int t=ns[i];
    for(int j=i;j<4;j++)if(ns[j]==ns[j+1])return false;
    return ns[4]-ns[i]+1-(5-i)-cnt<=0;
}
```

## 45.圆圈中最后剩下的数字 p228

n个人围成一个圈，每个人分别标注为1、2、...、n，要求从1号从1开始报数，报到k的人出圈，接着下一个人又从1开始报数，如此循环，直到只剩最后一个人时，该人即为胜利者。例如当n=10,k=4时，依次出列的人分别为4、8、2、7、3、10，9、1、6、5，则5号位置的人为胜利者。给定n个人，请你编程计算出最后胜利者标号数。

约瑟夫问题，创新解法虽然分析复杂，但是代码却十分简洁明了，时间O\(n\)，空间O\(1\)，这就是数学的魅力。

主要思想：n个人第一个删除的人的秩为`(k-1)%n`，假如我们已经知道了n-1个人时，最后胜利者的编号为x，利用映射关系逆推，就可以得出n个人时，胜利者的编号为\(x+k\)%n（要注意的是这里是按照映射后的序号进行的）。可以总结为： $$f(n,k)= ( f(n-1,k)+k )\%n$$

```cpp
int LastRemaining_Solution(int n, int m){
    if(n<1||m<1)return -1;
    int last=0;
    for(int i=2;i<=n;i++)
        last=(last+m)%i;
    return last;
}
```

