# 第1章 蓄势待发准备篇

* 关于运行时间

假设时间限制为1s，如果 $10^6$ 游刃有余；$10^7$ 勉勉强强；$10^8$ 很悬，仅限循环体非常简单的情况


* POJ 1852 Ants

细杆上的n只蚂蚁，知道其位置但不知道其朝向，两只蚂蚁相遇，各自朝相反方向，所有蚂蚁的运行速度都是1，求所有蚂蚁落下细杆的最长时间和最短时间。

只要转变思路，蚂蚁的碰撞相当于各个蚂蚁穿过对方继续前进，那么，最短时间就是中点左侧的蚂蚁都向左走，中点右侧的蚂蚁都向右走。最长时间是最左侧的蚂蚁向右走和最右侧的蚂蚁向左走的较大者。

该题目可以说是考察想象力类型问题的经典例子。

* 抽签问题

n个数字，抽取四次\(抽完放回\)，问是否存在4个数字的和为m。

如果是四重循环，判断`K[a]+K[b]+K[c]+K[d]==m`，那么复杂度是O\(n^4\)

如果实现将元素排序O\(nlogn\)，然后三重循环后用二分法判断是否存在`K[d]==m-K[a]-K[b]-K[c]`，则复杂度是O\(n^3logn\)

实现处理K\[a\]+K\[b\]的所有结果O\(n^2\)，然后排序O\(n^2logn\)，然后对于排序后的结果用二分法查找`K[a+b]==m-K[c+d]`,复杂度为O\(n^2logn\)
