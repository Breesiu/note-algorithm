# C++STL

STL 的组件共分为六类：

* Container（容器）——各种基本数据结构
* Adapter（适配器）——可改变 containers、Iterators 或 Function object 接口的一种组件
* Algorithm（算法）——各种基本算法如 sort、search…等
* Iterator（迭代器）——连接 containers 和 algorithms
* Function object（函数对象）
* Allocator（分配器）

## Container（容器）

顺序容器
* [vector](./codes/vector_test.cpp)
  * 动态空间管理
* [deque](./codes/deque_test.cpp)，double ended queue，即双端队列
  * deque由一段一段的定量连续空间构成，包括一个中控（即一个指针数组，每个指针指向一段连续线性空间）
  * 连续存储或分段连续存储，具体依赖于实现（分段连续存储更常见），**随机访问每个元素，所需要的时间为 O(1)**
  * 在开头和结尾增加元素所需时间为 O(1)，在中间增加或删除元素所需时间为 O(n)（连续存储时）或 O(1)（分段连续存储时）
  * 增加任何元素都将使 deque 的迭代器失效。在 deque 的中间删除元素将使迭代器失效。在 deque 的头或尾删除元素时，只有指向该元素的迭代器失效。
* [list](codes/list_test.cpp),双向环状链表
  * 调用`pop_front`/`pop_back`/`erase(iterator)`在开头、末尾和中间任何地方增加或删除元素所需时间都为 O(1)
  * 调用`insert(it,value)`在it之前插入value元素，返回插入元素的指针，可以用这个结合map来保存所有元素的指针，方便插入和删除。
  * 增加任何元素都不会使迭代器失效。删除元素时，除了指向当前被删除元素的迭代器外，其他迭代器都不会失效。
  * LRU可以用list结合map来做[146.LRU缓存机制](leetcode/146.LRU缓存机制.cpp)
* slist
  * 尽量不用好了


关联容器
* set
  * insert 和 erase 方法
  * 红黑树实现
  * 元素默认按升序排列
* multiset
  * 红黑树（一般红黑树以及其他的搜索二叉树是不允许重复键的，但这里在插入相同的 key 的时候，实现成了将 key 放在相等的 key 的右边，之后不管怎么进行插入或删除操作，后加入的 key 始终被认为比之前的大。这样就实现了一个 multiset，但根据 key 搜索的时候对于相同 key 的处理要我们自己来做）
  * 键可以重复。其他特点与 set 相同。
* unordered_set
  * 哈希表（数组 + 链表）
  * 与 set 相比较，它里面的元素不一定是经过排序的，而是按照所用的 hash 函数分派的，它能提供更快的搜索速度（当然跟 hash 函数有关）
* hash_multiset
  * 哈希表（数组 + 链表）
  * 键可以不唯一。其他特点与hash_set相同。
* map
  * insert 和 erase 方法
  * 红黑树
  * 键唯一，元素默认按键的升序排列。
* multimap
  * 红黑树
  * 键不唯一
* unordered_map
  * 哈希表（数组 + 链表）
  * 与 map 相比较，它里面的元素不一定是按键值排序的，而是按照所用的 hash 函数分派的，它能提供更快的搜索速度（当然也与 hash 函数有关）

## Adapter（适配器）

C++ 中定义了 3 种容器适配器，它们让容器提供的接口变成了我们常用的的 3 种数据结构：栈、队列和优先级队列。

* stack
  * 它可以将任意类型的序列容器转换为一个堆栈，一般使用 deque 或 list 作为支持的序列容器。
  * 元素只能后进先出。
  * 不支持遍历操作。
* queue
  * 它可以将任意类型的序列容器转换为一个队列，一般使用 deque 或 list 作为支持的序列容器。
  * 元素只能先进先出。
  * 不支持遍历操作。
* priority_queue
  * 它可以将任意类型的序列容器转换为一个优先队列，一般使用 vector 作为底层存储结构。
  * 只能访问第一个元素，不支持遍历操作。
  * 第一个元素始终是优先级最高的元素。


## Algorithm（算法）

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




## Container（容器）
