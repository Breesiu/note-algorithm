# 如何写伪代码

* > 伪代码没有统一的规范，但是按照某种约定写出的伪代码更具有可读性。
* > 本文总结了《算法导论》第三版中的伪代码格式[p11、p12]

## 格式约定

* 缩进表示块结构，而不是用begin和end语句，这样的好处是提高代码的清晰性
* 语句结尾不需要加冒号`:`或者分号`;`
* 选择用`if-else`语句
* 循环用关键字`while`/`for i=2 to A.length by 1`/`repeat-until`语句，注意for循环中，循环结束的条件是`i=A.length+1`，默认参数递进是1（可省略），其他参数如递进为2需写为`by 2`
* `//`后是注释
* 多重赋值和编程语言中一致
* 变量不需要声明类型
* 无特殊说明，不适用全局变量
* 数组用`数组名[下标]`访问，《算法笔记》中建议`A[i]`表示第i个元素，大小为n的数组元素分别为`A[1],A[2],...,A[n]`，子数组表示为`A[1..j]`，包含从`A[1]`到`A[j]`
* 逻辑运算用`and`、`or`、`not`，其中前两者是短路的，和大多数程序语言保持一致
* 复合数据被组织为对象，对象由属性组成，属性的访问用`.`，和c++一致
* 参数传递的过程和python类似，复杂对象(如数组)采用引用传递，简单数据类型采用值传递
* 空指针用特殊值`NIL`表示
* 允许return语句返回多个值，和python保持一致

* > **建议不采用《算法导论》中的这种数组表示，下标还是从0开始**
* > 《算法导论》中未指定通过指针访问对象属性的约定，建议和C++保持一致，用`->`
* > 循环时也建议采用`for in `语句，可代替属于符号

## 伪代码举例


* 插入排序[p10]

对数组`A[0..n-1]`进行插入排序
```
INSERT-SORT(A)
    for j=1 to A.length-1
        key=A[j]
        // Insert A[j] into the sorted sequence A[1..j-1].
        i = j-1;
      while i>0 and A[i]>key
          A[i+1]=A[j]
          i = i-1
      A[i+1]=key
```

* 快速排序[p95]

```
QUICK-SORT(A, p, r) // 对A[p..r]进行快排
    if p < r
        q = PARTITION(A, p, r)
        QUICK-SORT(A, p, q-1)
        QUICK-SORT(A, p+1, r)

PARTITION(A, p, r)
    x = A[r]
    i = p - 1
    for j = p to r-1
        if A[j] <= x
            i = i + 1
            exchange A[i] with A[j]
    exchange A[i+1] with A[r]
    return i + 1
```
