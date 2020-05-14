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

