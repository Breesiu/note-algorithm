# 第三章 数组和字符串

1. 数组用全局变量，容量选大点，`#define maxn 105`，浪费了5，但是更保险
2. int a[maxn],b[maxn];将数组a赋值k个元素到数组b可用`memset(b,a,sizeof(int)*k)`，全部复制可以写的简单些，改为sizeof(a)即可
3. 例3-3蛇形填数：代码值得学习，非常，判断也很明了

```cpp
#define manx 20
int a[maxn][maxn]
int main(){
    int n,x,y,tot=0;//total缩写
    scanf("%d",&n);
    memset(a,0,sizeof(a));
    tot=a[x=0][y=n-1]=1;//注意这里连续赋值的写法，非常简洁
    while(tot<n*n){
        while(x+1<n&&!a[x+1][y])a[++x][y]=++tot;//向下
        while(y-1>=0&&!a[x][y-1])a[x][--y]=++tot;//左
        while(x-1>=0&&!a[x-1][y])a[--x][y]=+=tot;//上
        while(y+1<n&&!a[x][y+1])a[x][++y]=++tot;//右
    }
}
```

4. cctype中定义的isalpha\isdigit\isprint可以判断字符的属性，toupper\tolower可以转换大小写
5. 不同操作系统的回车换行符是不一致的，用fgets、getchar应避免写和操作系统相关的程序。
6. C语言并不进制程序读写非法内存，例如声明char s[100]，完全可以赋值s[1000]='a'，甚至-Wall也不会警告。
7. fgets(buf,maxn,fin)，从文件中读取不超过maxn个字符，其中buf的大小是maxn。而gets并没有指明读取的字符数，引发的潜在的问题就是gets不停的往s中存储数据，而不管是不是存的下。正因如此，C++11已经废除了gets函数