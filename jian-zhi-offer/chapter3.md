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

