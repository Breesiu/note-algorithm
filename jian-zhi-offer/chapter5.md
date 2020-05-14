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

