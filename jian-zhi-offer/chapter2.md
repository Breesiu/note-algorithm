# 二.面试需要的基础知识

## 3.二维数组中的查找 p38

在一个二维数组中，每一行都按照从左到右的递增顺序，每一列车都是按照从下到下的递增顺序。输入一个整数，需要判断该数组中是否包含该整数。

从左下角到右上角，或者从右上角到左下角，相当于一个二叉判定树，不断的缩小题目范围

```cpp
bool Find(int target, vector<vector<int> > array) {
    int m=array.size(),n=array[0].size();
    int i=0,j=n-1;//行、列，从右上角开始
    while(i<m&&j>=0){
        if(array[i][j]==target)return true;
        else if(array[i][j]<target)i++;
        else j--;
    }
    return false;
}
```

## 4.替换空格 p44

将字符串中所有空格替换为%20,不允许新开数组。从前往后替代会覆盖，先计算空格个数，然后从后往前替代即可。

```cpp
void replaceSpace(char *str,int length) {
    int cnt=0;
    for(int i=0;i<length;i++){
        if(str[i]==' ')cnt++;
    }
    int i=length+cnt*2-1,j=length-1;
    while(j>=0){
        if(str[j]==' '){
            str[i--]='0';
            str[i--]='2';
            str[i--]='%';
            j--;
        }else
            str[i--]=str[j--];
    }
}
```

## 5.从尾到头打印链表 p51

输入一个链表的头结点，从尾到头反过来打印每个节点的值。

存到向量中后反转即可，比网上很多人说的栈实现要简单

## 6.重建二叉树 p55

略

## 7.用两个栈实现队列 p59

push算法直接插入到stack1即可，不用将stack2倒过来，pop直接删除stack2顶部即可，stack2为空是从stack1调入元素。自己之前实现的倒来倒去是没必要的。

```cpp
class Solution{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                int t=stack1.top();stack1.pop();
                stack2.push(t);
            }
        }
        int t=stack2.top();stack2.pop();
        return t;
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};
```

## 8.旋转数组的最小元素 p66

输入一个递增数组的一个旋转，输出该数组中的最小值。

二分，判断中间元素是位于前一段递增数组还是后一段递增数组。本题难点在于特殊情况的讨论，即中间元素和前后元素相等的情况。比如{1 0 1 1 1}{1 1 1 0 1}这两种情况。

```cpp
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size == 0){
            return 0;
        }//if
        int left = 0,right = size - 1;
        int mid = 0;
        // rotateArray[left] >= rotateArray[right] 确保旋转
        while(rotateArray[left] >= rotateArray[right]){
            // 分界点
            if(right - left == 1){
                mid = right;
                break;
            }//if
            mid = left + (right - left) / 2;
            // rotateArray[left] rotateArray[right] rotateArray[mid]三者相等
            // 无法确定中间元素是属于前面还是后面的递增子数组
            // 只能顺序查找
            if(rotateArray[left] == rotateArray[right] && rotateArray[left] == rotateArray[mid]){
                return MinOrder(rotateArray,left,right);
            }//if
            // 中间元素位于前面的递增子数组
            // 此时最小元素位于中间元素的后面
            if(rotateArray[mid] >= rotateArray[left]){
                left = mid;
            }//if
            // 中间元素位于后面的递增子数组
            // 此时最小元素位于中间元素的前面
            else{
                right = mid;
            }//else
        }//while
        return rotateArray[mid];
    }
private:
    // 顺序寻找最小值
    int MinOrder(vector<int> &num,int left,int right){
        int result = num[left];
        for(int i = left + 1;i < right;++i){
            if(num[i] < result){
                result = num[i];
            }//if
        }//for
        return result;
    }
};
```


## 9.斐波那契数列
略

## 10.二进制中1的个数 p78

```cpp
//负数用补码表示，也要考虑到。所以，如果是把数右移判断最低位可能会陷入死循环。
 int  NumberOf1(int n) {
     int cnt=0,flag=1;
     while(flag!=0){
         cnt+=(flag&n)?1:0;
         flag=flag<<1;//非常坑的地方在于这里只写flag<<1居然flag的值在下次循环时并咩有改变
     }
     return cnt;
 }
//再进一步：把一个整数减去1，在和原来的数做与运算，就会把整数最右边的一个1变成0，那么，整数中有多少个1，就可以进行多少次操作。
int  NumberOf1(int n) {
    int cnt=0;
    while(n){
        cnt++;
        n=(n-1)&n;
    }
    return cnt;
}
```