# 排序算法

* 基本算法模板背诵，冒泡、选择、插入、堆、快速、归并排序
* PAT考试排序基本套路：题目也许很复杂，需要用结构体存入数据，数据量较少的时候用结构体数组，但是用数组存放结构体的指针更好，成本更小。PAT考试考排序就是考复杂的排序逻辑，然后让你根据题意写cmp函数。
* 运用STL中sort函数进行排序时，要编写cmp函数。比如对学生排序，如果成绩不同，那么分数高的排在前面，否则，将姓名字典序小的排在前面。

```cpp
bool cmp(Student a,Student b){
    if(a.score != b.score)return a.score>b.score;
    else return strcmp(a.name,b.name)<0;//注意这里strcmp函数
}
```

| 排序算法性能比较 | 稳定性 | 是否就地 | 输入敏感 | 复杂度 | 备注 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 插入排序 | 稳定 | 就地 | 输入敏感 | 最小n最大n^2 |  |
| 选择排序 | 不稳定 | 就地 | 输入敏感 | 最小n最大n^2 |  |
| 堆排序 | 不稳定 | 就地 | 输入不敏感 | nlogn |  |
| 快速排序 | 不稳定 | 就地 | 输入敏感 | 最好nlogn最大n^2平均nlogn |  |
| 归并排序 | 稳定 | 非就地 | 输入不敏感 | nlogn |  |

记数排序｜不稳定｜非就地｜输入敏感｜n+k，k是输入元素的范围｜

## 基础排序:冒泡、选择、插入

冒泡、选择、插入三种基础排序算法需要明白两个概念：

* 已排序序列、待排序序列

有地方说用链表实现的插入排序是稳定的，因为并没有交换产生，将选择的元素插入到原序列，而一般而言的说的选择排序时基于向量实现的，找到最大元素和未排序序列的首元素交换位置，显然，是非稳定的。

## 计数排序

计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。当输入的元素是 n 个 0 到 k 之间的整数时，它的运行时间是 `Θ(n + k)`。计数排序不是比较排序，排序的速度快于任何比较排序算法。

是一种以空间换时间的方法。

* 记数排序动图

![](https://www.runoob.com/wp-content/uploads/2019/03/countingSort.gif)

## 快速排序

* 快速排序过程中，寻找中轴点的过程交换是非稳定的

### 第k大问题

1.仿照快排的轴点选择算法，在`[lo,hi]`插入的位置p即为数组的第`m=p-lo+1`大的数，如果`m==k`,则找到了第k大的数，如果，`m>k`，则继续在左侧区间找第k大的数，否则，在右侧区间找第`k-m`大的数。此方法的最坏时间复杂度是`O(n^2)`，期望复杂度`O(n)`

```cpp
//[lo,hi]勤于扩展、懒于交换，全部元素相同时是最坏情况
int partition(vector<int>& vec,int lo,int hi){
    swap(vec[lo],vec[rand()%(hi-lo+1)+lo]);
    int tmp=vec[lo];
    while(lo<hi){
        while(lo<hi&&vec[hi]>=tmp)hi--;
        vec[lo]=vec[hi];
        while(lo<hi&&vec[lo]<=tmp)lo++;
        vec[hi]=vec[lo];
    }
    vec[lo]=tmp;
    return lo;
}
int randSelect(vector<int>& vec,int lo,int hi,int k){
    if(lo==hi)return vec[lo];
    int p=partition(vec,lo,hi);
    //_for(i,lo,p)if(vec[i]>vec[p])printf("%derror\n",i);
    //_for(i,p,hi+1)if(vec[i]<vec[p])printf("%derror\n",i);
    int m=p-lo+1;
    if(k==m)return vec[p];
    if(k>m)
        return randSelect(vec,p+1,hi,k-m);
    else
        return randSelect(vec,lo,p-1,k);
}
```

