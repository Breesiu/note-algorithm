# 堆

重点掌握堆的api用法。

较好的题目：
* [703. 数据流中的第 K 大元素](./leetcode/703.数据流中的第K大元素.cpp)
* [347. 前 K 个高频元素](./leetcode/347.前K个高频元素.cpp)


* `priority_queue<int, vector<int>, greater<int> >`小项堆。易错点：less表示数字大的优先级高，greater<int> 表示数字小的优先级高。**优先级队列默认的就是优先级高的放在队首，优先级队列的这个函数和sort中的cmp起到的作用是相反的**
* 自定义元素比较的两种方法
* 结构体内部重载<运算符
* 使用函数对象

```cpp
//结构体内部重载<运算符
struct fruit{
	string name;int price;
	friend bool operator<(fruit f1,fruit f2){
		return f1.price<f2.price;//这里top是价格高的
	}
}; // friend关键字不能省，当结构体类型较大时，参数用(const fruit& f1,const fruit& f2)
//函数对象
struct cmp{
	bool operator()(fruit f1,fruit f2){
		return f1.price<f2.price;
	}
}; // 优先级队列这里的第三个参数只能是函数对象，不能是函数指针。（sort支持函数对象和函数指针两者）
```
