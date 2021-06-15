# 全书笔记

## 2、输入输出

* 补充：重载输入输出流操作符

```cpp
ostream& operator<<(ostream& out,vector<int>& vec){
    out<<vec[0];
    _for(i,1,vec.size())out<<" "<<vec[i];
    out<<endl;
    return out;
}
```

* stringstream将一行数据一个一个的输入到string中

```cpp
getline(cin,strline);
stringstream ss(strline);
string str;
ss>>str;
```

* sscanf、sprintf用法

比如：char a\[100\]="123";sscanf\(a,"%d",&n\);

再比如：int n=123;char a\[100\];sprintf\(a,"%s\n",n\);

当然了，也可以用于格式化文件读写，比如：

```cpp
FILE* fp=fopen("d:\\codeBlockSpace\\output.txt","w"); 
for(int i=0;i<10;i++)
    fprintf(fp,"%d %d\n",i,i+3);
```

将一个文件的内容复制到另一个文件，`while(sscanf("%s",a)!=EOF)`这时会将空格和回车省去不复制。也可以用`fscanf(fp,"%s",a)`

* scanf\printf用法

```cpp
// %m.nf    %md    %-md    %0md    %lld    %lf
scanf("%lld",&a);
printf("%lld",a);
//用printf输出string用str.c_str()即可
//输入整行
char a[100];
getline(a);
string a;
getline(cin,str1);
```

* getchar、putchar、gets、puts用法
  * getchar\(\)和putchar\(c\)用来输入输出单个字符
  * gets\(&a\)用来输入一行字符串，gets识别换行符作为结束标志，因此scanf输入一个完整数组后，应该先用getchar吸收整数后的换行符在使用gets。
  * puts\(&a\)输出数组信息并自动添加一个换行

在标准C语言中，getline函数是不存在的。下面是一个简单的实现方式：

```cpp
int getline_(char s[],int lim){
    int c,i;
    i=0;
    while((c=getchar())!=EOF&&c!='\n'&&i<lim-1)
        s[i++]=c;
    s[i]='\0';
    return i;
}
```

* 判断输入输出结束

```cpp
//注意，scanf的返回值是读取到的变量的个数
string a, b; 
char c; 
while (cin >> a >> b >> c){}
while (scanf("%s %s %c", &a, &b, &c) != EOF){}
```

* 重定向

```cpp
freopen("d:\\input.txt","r",stdin);
freopen("d:\\output.txt","w",stdout);
```

* 直接从文件读数据

```cpp
//C
#include"stdio.h"
FILE* fp=fopen("D:\\test.txt","r");
char buffer[50];
fgets(buffer,50,fp);
sscanf(buffer,"%d %d",&m,&n);
fgets(buffer,50,fp);
sscanf(buffer,"%d %d",num1+i,num2+i);
fclose(fp);

//C++
#include <fstream>
#include <iostream>
#include <sstream>
ifstream fp("D:\\data.txt");
string buffer;
stringstream ss;
getline(fp,buffer);ss<<buffer;ss>>n;cout<<n<<endl;
getline(fp,buffer);
cout<<buffer<<endl;
```

## 3小技巧&基础知识

* 四种基本数据类型
  * 整形`int    longlong    %d    %lld    %md  %0md    %.md`
  * 浮点型`float\double  %f   %lf`
  * 字符型`char`
  * 布尔型`bool`
* 用order数组记录结构体秩并移动

存储结构体数组并且涉及到数组的移动删除操作时，如果结构体空间较大，则用`order[]`数据记录各元素的位置。即用`vector<node>`存储数组，用`vector[order[i]]`按顺序访问数组，这样移动和删除操作都是对int类型进行处理了。

* 判断是否能被2整除时，可以直接用位运算&1

## 4入门篇：算法初步

### 4.1 排序

见专题

### 4.2 散列

* 做题套路：基本考察点就是用256数组存储各个字符出现的次数，判断各个字符是否有效。用set去重，用map计数，基本就这三种套路
* 数据不大时，直接把输入的数当做数组下标来对这个数据的性质进行统计，是很实用的以空间换时间的方法
* hash开放定址法：线性试探法试探H\(key\)+1。平方试探法试探H\(key\)+1,H\(key\)-1,H\(key\)+4,H\(key\)-4。注意有些题目说明了平方试探发只试探一边。封闭定址法有：链地址法。
* 字符串hash：A-Z映射为0-25,一个字符串看做26进制数。注意如果前三位字母，后一位数字，可以把各位的权值分别设置为26、26、26、10，即非标准的进制法。BCD4，可以看做前三位的731和后面的4拼接，即7314.
* 如果把进制设置为10^7级别的素数（比如10000019），mod设置为10^9的素数（比如1000000007），实践证明，很难发生冲突。
* 散列函数
* 除余法`hash(key)=key mod M`
* MAD法：除余法中0的hash值始终为0，不管hashtable多大，而且相邻关键码的散列值相同，随机性不强。改进为`hash(key)=(a*key+b) mod M`
* 冲突解决方案

无论散列函数设计多么巧妙，冲突是不可避免的。

封闭定址 开散列

1. 每一个词条的key值不变
2. 多槽位法：即在每一个桶都细分为固定更小的槽位，每一个组槽位数固定，用向量或链表实现
3. 独立连法：和多槽位的不同就是向量中存放的是列表的指针，所有冲突的词条都在该列表上
4. 公共溢出区法：将冲突的词条放入另一个存放冲突的公共缓冲区

封闭定址 闭散列

1. 每一个词条的key值可变，仅仅依靠基本的散列表结构，就地排解冲突
2. 线性试探\(linear probing\)：冲突的时候就找后面没词条的位置放。注意这里面有一个惰性删除\(即标记为之前存过元素\)，以防止其后面的冲突元素在查找的时候无法被访问
3. 平方试探\(quadratic probing\)：按照如下规则确定第j次试探的位置：`(hash(key)+j^2) mod M`
   * 有的地方说平方试探是两个方向，即`(hash(key)-j^2) mod M`，看题目是要清楚，看看是哪个方向，还是两个方向交错
   * 单向试探时，若M为质数，且装填因子小于50%，则平方试探必然可以找到空桶
   * 可以证明：如果j从0-\(M-1\)都无法找到位置，那么，就不可能找到位置，即循环节为M。此结论易证明。

### 4.3 递归

1. 全排列。其实这个更是DFS的应用，应熟记此方法。
2. **n皇后**。相比邓老师书中用试探回溯法，自己模拟栈的情况，然后不断的试探+回溯，不如类比为全排列（根据每行每列只能放一个数，用数组下标表示行，数组中的元素表示列，或者相反，即把每一个全排列和每一种n皇后的分布对应起来），然后验证该排列是否满足n皇后的对角线不相等即可。全排列的实现和DFS法一致，步进递归。当然，对于n皇后的特殊性，比如前三个元素已经选定但是冲突时，就应该避免继续递归而即使break掉。这个用函数递归系统栈实现的方法和邓老师书中自建栈实现的方法原理是一样的，但是自建栈明显要繁琐很多，也不好调试。所以，DFS回溯法解n皇后更佳。

### 4.4 贪心

1. 解题没什么套路，多花点时间思考贪心策略的正确性，如果策略错了，很难检查出来错误。如果程序运行没错，但是答案不对，很可能就是贪心策略不对
2. 区间贪心：设定左边界，按照右端点从小到大排序，右端点相同的选左端点大的（应对重叠区间）

### 4.5 二分

1. 解题套路：熟练写二分函数，`mid=(lo+hi)/2`的取值范围是`[lo,hi)`,注意此取值范围正确写上下界
2. `mid=(lo+hi)/2`，如果`lo+hi`会越界，则用`mid=(hi-lo)/2+lo`等价语句
3. 最常用的是`[lo,hi)`区间查找大于等于e的最小元素，或查找大于e的最小元素，两者的区别只是把`mid>=e`和mid&gt;e
4. 二分法的题目都可以归结为这样一个问题：寻找序列中第一个满足某条件的元素的位置
5. 求`sqrt(2)`
6. 装水问题：在半圆R里面装水，求水的高度h，使得水的面积/半圆的面积=r。显然，高度h和水的面积是单调的，这样就可以二分来做，逼近正确答案
7. 木棒切割问题：给出N根木棒，长度均已知，切割成K段长度相同的木棒（必须为整数），则每段的长度最大是多少？显然，切割后木棒越长，则能切割的根数越少，二分法去逼近木棒的长度，计算该长度下能够切割的根数，问题就变成了切割的根数&gt;=K时，木棒长度的最大值。
8. 快速幂：计算`a^b%m`，如果b达到了10^18，显然，递归相乘方法是不可取的。应采取快速幂方法。快速幂方法基于二分法，也称为二分幂。b为奇数时，`f(b)=a*f(b/2)^2`;b为偶数时，`f(b)=f(b/2)^2`.
9. 快速幂的迭代写法：将b写为二进制，那么b就可以写成若干次二次幂之和，比如b=13时，13=8+4+1.可行的方法是每次判断b的末尾是否为1，为1加上该位置对应的二次幂，然后更新下一个位置的二次幂，b右移一位
10. fib数列也可以用快速幂解法，在O\(logn\)的时间内求出F\(n\)，关键是推导出两项与两项之间的矩阵形式。

```cpp
//大于等于e最小元素
int lower_bound(vector<int>& vec,int lo,int hi,int e){
    int mid;
    while(lo<hi){
        mid=(lo+hi)/2;
        if(vec[mid]>=e)hi=mid;
        else lo=mid+1;
    }
    return lo;
}
//大于e的最小元素
int upper_bound(vector<int>& vec,int lo,int hi,int e){
    int mid;
    while(lo<hi){
        mid=(lo+hi)/2;
        if(vec[mid]>e)hi=e;
        else lo=mid+1;
    }
    return lo;
}
//伪代码
int solve(int lo,int hi){
    int mid;
    while(lo<hi){
        mid=(lo+hi)/2;
        if(条件成立)hi=mid;
        else lo=mid+1;
    }
    return lo;//这里lo==hi,所以返回值是谁是一样的。
}
//小于等于e的最大元素
//小于e的最大元素
//计算sqrt(2)
double sqrt(){
    double lo=1.0,hi=2.0,mid;
    while(hi-lo>1e-10){
        mid=(lo+hi)/2;
        if(mid*mid>2)hi=mid;
        else lo=mid;
    }
    return mid;
}
//快速幂递归写法
LL binPow(LL a,LL b,LL m){
    if(b==0)return 1;
    if(b%2)//这里可以用b&1代替
        return a*binPow(a,b-1,m)%m;
    else{
        LL tmp=binPow(a,b/2,m);
        return tmp*tmp%m;
    }
}
//快速幂迭代写法
LL binPow(LL a,LL b,LL m){
    if(b==0)return 1;
    LL ans=1,tmp=a;
    while(b>0){
        if (b % 2==1) {
            ans * = tmp;
        }
        b /= 2;
        tmp = tmp * tmp;
    }
}
```

### 4.6 双指针

1. 给定递增序列，找两个数使得其和为定值m。暴力枚举O\(n^2\)，更简单的是双指针，初始时i=0,j=n-1；如果vec\[i\]+vec\[j\]&gt;m,j--使和变小，vec\[i\]+vec\[j\]&lt;m,i++，使和变大，相等时即找到一种方案，令i++,j--继续寻找下一组方案
2. 归并排序的merge算法也是双指针问题
3. 快速排序确定轴点的算法，邓老师书中的也属于双指针版本

### 4.7 随即选择算法：第K大问题

见排序专题

## 5 入门篇：数学问题

见数学专题

## 5 STL

### 6.1 set

* set只能通过iterator访问
* 除vector和string之外的STL容器都不支持`*(it+i)`的访问方式，只能用迭代器枚举的方式
* `find(value)`返回对应值为value的迭代器
* `erase(it)`需要结合`find`函数，比如`st.erase(find(st.find());`
* `erase(value)`删除特定值
* `erase(first,last)`删除区间\[first,last\)
* `set<int,greater<int> >`默认是`less<int>`
* set中自定义元素排列顺序：待排序元素重载小于运算符
* 如果不需要对set进行排序，建议使用速度更快的unordered\_set，内部采用散列实现。

### 6.2 string

* 可用用`< <=`等各种比较符，比较的依据是字典序
* `erase(it)`
* `erase(first,last)`
* **`erase(pos,len)`**
* `insert(pos,string)`在pos位置插入字符串string
* `insert(it,it2,it3)`,it为原字符串的带插入位置，it2、it3为带插入字符串的首尾迭代器
* `substr(pos,len)`
* `string::npos`是一个常数，值为-1，但由于是unsigned类型，为unsigned的最大值
* `str.find(str2)`,如果str2是str的子串，返回其在str中第一次出现的位置，如果不是子串，返回npos
* `str.find(str2,pos)`，从str的pos位置开始匹配
* `str.replace(pos,len,str2)`把str从pos号位开始、长度为len的子串替代为str2
* `str.replace(first,last,str2)`把str的迭代器`[first,last)`范围的子串替换为str2

### 6.3 map

* 如果是字符到整形的映射，必须用string，不能用char数组
* map的第三个参数可以用`greater<int>` ,包含头文件`<functional>`
* `find(key)`返回键值key的迭代器
* `erase(it)`
* `erase(key)`
* `erase(first,last)`
* 常见用途：
  * 建立各种类型之间的映射
  * 判断大整数或者其他类是是否存在的题目，把map当bool数组用
  * 字符串和字符串的映射

### 6.4 queue

* 只能通过`front()`来访问队首元素，back\(\)来访问队尾元素
* `push()`入队
* `pop()`出队
* `empty()`检测队空

### 6.5 priority\_queue

* 不能用front\(\)和back\(\)函数，只能用top\(\)访问队首元素
* **优先级设置**
* `priority_queue<int,vector<int>,less<int> > q`;注意最后两个&gt;之间有一个空格。
* 易错点：less表示数字大的优先级高，`greater<int>`表示数字小的优先级高。**优先级队列默认的就是优先级高的放在队首，优先级队列的这个函数和sort中的cmp起到的作用是相反的**
* 结构体内部要重载小于号

```cpp
//结构体内部重载<运算符
struct fruit{
    string name;int price;
    friend bool operator<(fruit f1,fruit f2){
        return f1.price<f2.price;//这里top是价格高的
    }
};
//函数对象
struct cmp{
    bool operator()(fruit f1,fruit f2){
        return f1.price<f2.price;
    }
};
```

* friend关键字不能省，当结构体类型较大时，参数用\(const fruit& f1,const fruit& f2\)
* 优先级队列这里的第三个参数只能是函数对象，不能是函数指针。（sort支持函数对象和函数指针两者）

### 6.6 pair

* 添加map头文件最方便
* `pair<string,string> p;`
* `oair<string,int> p("haha",5);`
* `make_pair("haha",5);`
* 比较时先以first的大小为标准，first相等时采取判别second的大小

### 6.7 algorithm

* `max() min() abs() swap()`
* `reverse(it_1,it_2)`，对\[it\_1,it\_2\)的元素进行反转
* `next_permutation(it_1,it_2)`
* sort支持函数对象和函数指针两者,STL中，只有vector、string、deque可以用sort，set、map本身有序，不用sort。list有自带的sort函数
* `sort(it1,it2,cmp)`cmp为函数指针和函数对象均可
* `fill(it1,it2,e)`
* `lower_bound(first,last,val)`第一个大于等于val的元素的位置，upper\_bound第一个大于val的元素的位置

### 6.8 map set拓展

* `unordered_map`用散列代替红黑树，只处理映射而不处理键值排序，速度比map快很多
* `unordered_set`同理
* `multimap`一个键值可以对应多个值

```cpp
/*
    在multimap中，同一个键关联的元素必然相邻存放。基于这个事实，就可以将某个键对应的值一一输出。
    1、使用find和count函数。count函数求出某个键出现的次数，
    find函数返回一个迭代器，指向第一个拥有正在查找的键的实例。
    2、使用lower_bound(key)和upper_bound(key)
      lower_bound(key)返回一个迭代器，指向键不小于k的第一个元素
      upper_bound(key)返回一个迭代器，指向键不大于k的第一个元素
    3、使用equat_range(key)
      返回一个迭代器的pair对象，first成员等价于lower_bound(key)，second成员等价于upper_bound(key)
*/
int main()
{
    multimap<string,int> m_map;
    string s("中国"),s1("美国");
    m_map.insert(make_pair(s,50));
    m_map.insert(make_pair(s,55));
    m_map.insert(make_pair(s,60));
    m_map.insert(make_pair(s1,30));
    m_map.insert(make_pair(s1,20));
    m_map.insert(make_pair(s1,10));
    //方式1
    int k;
    multimap<string,int>::iterator m;
    m = m_map.find(s);
    for(k = 0;k != m_map.count(s);k++,m++)
        cout<<m->first<<"--"<<m->second<<endl;
    //方式2
    multimap<string,int>::iterator beg,end;
    beg = m_map.lower_bound(s1);
    end = m_map.upper_bound(s1);
    for(m = beg;m != end;m++)
        cout<<m->first<<"--"<<m->second<<endl;
    //方式3
    beg = m_map.equal_range(s).first;
    end = m_map.equal_range(s).second;
    for(m = beg;m != end;m++)
        cout<<m->first<<"--"<<m->second<<endl;
    return 0;
}
```

### 7.1、7.2 栈、队列

* 计算逆波兰表达式，先将中缀表达式转化为后缀表达式，然后用栈计算后缀表达式的值\(注意设置各运算符优先级\)

### 7.3 链表

* 套路：链表题目一般输入为`Addr Key Next`三元组，地址到下一个节点的映射或者用数组（优先选用，如果地址仅五位数表示的话），或者用map映射。
* 注意，题目往往要求地址是五位数，注意用%05d

## 9 树与二叉树

* 二叉树构建
* DFS递归遍历，BFS层次遍历
* 二叉树的静态实现适合于不喜欢用指针的同学。其定义、查找、插入、遍历等均可以静态实现

```cpp
struct node{
    int val;
    int lc,rc;
}Node[MAXN];//节点数组，MAXN为节点上限
```

* BST的插入操作
* 删除操作：将该节点的值与其前驱或者后继的值交换，然后再进行删除。

## 10 图算法专题

见专题总结

## 11 动态规划

见专题总结

## 12 字符串

见专题总结

## 13 树状数组

* `lowbit(x)=x&(-x)`
* 背景：给定一个整数序列，有两种操作：计算前K项的和，对某一项加。如果采用普通的数组，则计算前K项和的复杂度过高，如果采用sum数组，则给某一项加的复杂度过高。
* 采用树状数组可以使两种操作的复杂度均为log\(n\)
* 应熟记树状数组的图形记忆。数组的下标从1开始，不包括0.
* **//C\[i\]的覆盖长度是lowbit\(i\)，以i为结尾。**

```cpp
#define lowbit(i) (i&(-i))

int  A[100005];
long long C[100005];

//A[x]加上v
void updata(int x,int v){
    if(v==0)return;
    for(int i=x;i<n+1;i+=lowbit(i)){
        C[i]+=v;
    }
}

//计算A[1]-A[x]的和
long long getsum(int x){
    long long sum=0;
    for(int i=x;i>0;i-=lowbit(i)){
        sum+=C[i];
    }
    return sum;
}
```

典型应用1：单点更新，区间查询

* 给定一个有N个正整数的序列A\(A&lt;=10^5,A\[i\]&lt;=10^5\) ,对序列中的每个数，求出序列中它左边比它小的数的个数。

思路：

* 用hash\[x\]记录整数x当前出现的次数。从左到右遍历序列，对于每一个x，使hash\[x\]加一。对于序列中左侧比自身小的数，即为hash\[0\]+hash\[1\]+……+hash\[x-1\]，即单元素加操作和前k项和操作，直接用树状数组实现即可。

举一反三：

* 如果求序列中左侧比自身大的数字的个数，即求hash\[x+1\]+hash\[x+2\]+……+hash\[n\]，即getSum\(N\)-getSum\(x\)。
* 如果没有给出A\[i\]的取值范围，要采用离散化技巧。
* 先排序，设置结构体{val,pos},即把原始数据的大小和位置记录下来，后按照大小排序。即把所有可能的数字映射到1-n，然后用之前的hash数组即可。

典型应用2：区间更新，单点查询

* 设计函数getSum\(x\)，返回A\[x\]
* 设计函数update\(x,v\)，将A\[1\]-A\[x\]的每个数都加上一个数v

思路：

* 修改树状数组的定义，宽度不变，仍为lowbit\(x\)，但是C\[i\]不再表示这段宽度内的综合，而是表示这段区间的每个数当前被加了多少。

## 14 主元素问题

一个序列中有没有一个元素超过总数的50%？

方法一：当数组元素之间可以有序时，找中位数，它是主元素的唯一候选，用插入排序类似的第K大问题求解。第K大问题的时间复杂度是O\(N\)

方法二：摩尔投票算法。元素数目相同时删除前序即可，最后剩下的一个元素就是主元素。

方法一没有考虑到题目中数组的特性：数组中有个数字出现的次数超过了数组长度的一半。也就是说，有个数字出现的次数比其他所有数字出现次数的和还要多。因此我们可以考虑在遍历数组的时候保存两个值：一个是数组中的一个数字，一个是次数。当我们遍历到下一个数字的时候，如果下一个数字和我们之前保存的数字相同，则次数加1。如果下一个数字和我们之前保存的数字不同，则次数减1。如果次数为零，我们需要保存下一个数字，并把次数设为1。由于我们要找的数字出现的次数比其他所有数字出现的次数之和还要多，那么要找的数字肯定是最后一次把次数设为1时对应的数字。

不限定时间复杂度的话，很多人会先排序，再遍历的方法来做。不限定空间复杂度的话，很多人会用hash表来做。那么，有了这两个限定，就只能用摩尔投票算法了。

摩尔投票算法：时间复杂度O\(n\)，空间复杂度O\(1\)

```cpp
//leetcode169
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans=nums[0],cnt=1;
        for(int i=1;i<nums.size();i++){
            if(cnt==0){ans=nums[i];cnt++;}
            else if(nums[i]==ans)cnt++;
            else cnt--;     
        }
        return ans;
    }
};
```

扩展：问题升级为选取大于等于n/3的数，简单分析可知，大于n/3的数最多有两个。（反证法轻轻松松即可证明），采取和169一样的摩尔投票算法，只不过，这次保留两个元素出现的次数。另外一个区别是这个题目没有保证此众数一定存在，所以，在得到两个候选众数之后，需要再次遍历一遍验证。

```cpp
//LeetCode229
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        int m = 0, n = 0, cm = 0, cn = 0;
        for (auto &a : nums) {
            if (a == m) ++cm;
            else if (a ==n) ++cn;
            else if (cm == 0) {m = a, cm = 1;}
            else if (cn == 0) {n = a, cn = 1;}
            else --cm, --cn;
        }
        cm = cn = 0;
        for (auto &a : nums) {
            if (a == m) ++cm;
            else if (a == n) ++cn;
        }
        if (cm > nums.size() / 3) res.push_back(m);
        if (cn > nums.size() / 3) res.push_back(n);
        return res;
    }
};
```

## 15 全排列

* DFS解一般全排列问题

  **可重复元素的全排列问题**

  和DFS不同元素的方法是一样的，只不过怎加了判断元素个数是否用完

  * 不过，这个方法太繁琐，重复计算各个各个元素的数目，其中的`!i||P[i]!=P[i-1]`就是除去了重复元素而已，要理解P是包含重复元素的已排序序列，这个就很容易理解了，还是不如一个数组表示数目，一个数组表示元素数量。

```cpp
int n,m;//元素总的个数、不同元素的数目
vector<int> cntP,P,ans;//分别表示元素的值和数量
void permutation(int step){
    if(step==n){
        printvec(ans);
        return;
    }else{
        for(int i=0;i<P.size();i++){
            if(cntP[i]>0){
                cntP[i]--;
                ans[step]=P[i];
                permutation(step+1);
                cntP[i]++;
            }
        }
    }
}
int main() {
    freopen("d:\\input.txt","r",stdin);
    //freopen("d:\\output.txt","w",stdout);
    cin>>n>>m;
    cntP.resize(m);P.resize(m);ans.resize(n);
    _for(i,0,m)    cin>>P[i];
    _for(i,0,m)    cin>>cntP[i];
    permutation(0);
    return 0;
}
```

### 求下一个排列的字典序法

[由当前序列找到下一个序](https://blog.csdn.net/cpfeed/article/details/7376132?utm_source=blogxgwz3)

设P是1～n的一个全排列:`p=p1p2......pn=p1p2......pj-1pjpj+1......pk-1pkpk+1......pn`

* 从排列的右端开始，找出第一个比右边数字小的数字的序号j（j从左端开始计算），即 `j=max{i|pi<pi+1}`
* 在pj的右边的数字中，找出所有比pj大的数中最小的数字pk，即 `k=max{i|pi>pj}`（右边的数从右至左是递增的，因此k是所有大于pj的数字中序号最大者）
* 对换pi，pk
* 再将`pj+1......pk-1pkpk+1......pn`倒转得到排列`p'=p1p2.....pj-1pjpn.....pk+1pkpk-1.....pj+1`，这就是排列p的下一个排列。

### 康拓展开和逆康托展开

采用了康托展开的排序方法，顺序最小，逆序最大，康托展开是字符串全排列到自然数的一个双射，通常用于构建哈希表时空间压缩

* 首先从最尾端开始往前寻找两个相邻元素，令第一元素为i,第二元素为i+1,且满足v\[i\]&lt;v\[i+1\]。
* 找到这样一组相邻元素后，再从最尾端开始往前检验，找出第一个大于v\[i\]的元素，令为j，将i,j元素对调swap\(v\[i\],v\[j\]\)。
* 再将i+1\(包括\)及之后的所有元素颠倒\(reverse\)排序。

  [思路参考](https://blog.csdn.net/c18219227162/article/details/50301513)

  [康托展开](https://blog.csdn.net/wbin233/article/details/72998375)

```cpp
bool next_permutation(vector<int>& nums,int lo,int hi){
    int i=hi-2,j=hi-1;
    //step1
    while(i>=lo){
        if(nums[i]<nums[i+1])break;
        i--;
    }
    if(i<lo)return false;
    //step2
    for(j=hi-1;j>i;j--){
        if(nums[j]>nums[i])break;
    }
    swap(nums[i],nums[j]);
    //step3
    reverse(nums.begin()+i+1,nums.end());
    return true;
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> ans;
    int n=nums.size();
    if(n==0)return ans;
    sort(nums.begin(),nums.end());
    do{
        ans.push_back(nums);
    }while(next_permutation(nums,0,n));
    return ans;
}
```

## 16 并查集

```cpp
//路径优化：
int Find(int x) { return fa[x]==x?x:fa[x]=Find(fa[x]);}
//合并
void union(int x,int y){
    int fx=find(x),fy=find(y);
    fa[fx]=fy;
}
//判断是否同一子集
bool same(int x,int y){
    return find[x]==find[y];
}
```

```cpp
class DisjointSet{
    private:
        vector<int> fa;
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
    public:
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
};
```

