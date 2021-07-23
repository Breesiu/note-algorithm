# C++STL

## algorithm

https://www.cplusplus.com/reference/algorithm/

### 二分检索 

* 找到大于等于某值的第一次出现 `ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val)`;
* 找到大于某值的第一次出现 `ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)`;

二分查找的实现，这里注意用的区间都是左闭右开。

`lower_upper`的原理：
* 整个数组分为三个区间，`[0,lo)<val``[lo,hi) unknown``val<=[hi,n)`
* `lo==hi`时，说明数组已经被划分完毕。
* 返回lo-1

`upper_upper`的原理：
* 整个数组分为三个区间，`[0,lo)<=val``[lo,hi) unknown``val<[hi,n)`
* `lo==hi`时，说明数组已经被划分完毕。
* 返回lo-1

```cpp
int lower_bound(vector<int>& v, int lo, int hi, int val){
    int mi = (lo+hi)/2;
    while(lo<hi){
        if(v[mi]<val)lo=mi+1;
        else hi = mi;
    }
    return hi;
}
upper_bound(vector<int>& v, int lo, int hi, int val){
    int mi = (lo+hi)/2;
    while(lo<hi){
        if(v[mi]<=val)lo=mi+1;
        else hi = mi;
    }
    return hi;
}
```

### 无需序列查找find

`InputIterator find (InputIterator first, InputIterator last, const T& val);`

采用暴力算法实现，用==运算符将 val 和 [first, last) 区域内的元素逐个进行比对，[first, last) 区域内的元素必须支持==运算符。

### 序列匹配

方法1: 暴力算法。比较子序列在主序列中的匹配位置，采用不断改变两个序列的头部对齐位置，然后从头到尾比较两个序列是否相同。

`find_end`输出子序列在主序列最后一次出现的位置，`search`正好相反，输出第一次出现的位置。

`ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1,ForwardIterator2 first2, ForwardIterator2 last2);`

`ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1,ForwardIterator2 first2, ForwardIterator2 last2);`

方法2: KMP匹配

