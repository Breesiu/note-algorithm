# 数学算法

## 5、数学问题

1. 套路：熟悉常见题目
2. 该部分不涉及很深的算法，却与数学息息相关，不需要特别的数学知识，只要掌握简单的数理逻辑即可。
3. 最大公约数`int gcd(int a,int b){return !b?a:gcd(b,a%b);}`这段代码十分简洁，并且实现了如果`a<b`,先互换。辗转相除法也称欧几里得算法。
4. 最小公倍数，在最大公约数的基础上计算，为`ab/gcd(a,b)`

## 5.2 常用math函数

* `fabs(double x)`
* `floor(double x)`向下取整
* `ceil(double x)`向上取整
* `pow(double r,double p)`返回`r^p`
* `sqrt(double x)`
* `log(double x)`返回double型变量的以自然对数为底的对数
* `sin(double x)`、`cos(double x)`、`tan(double x)`
* `pi=acos(-1)`
* `asin(double x)`、`acos(double x)`、`atan(double x)`
* `round(double x)`四舍五入、返回类型也是double

## 5.3 日期处理

```cpp
int mon[2][13]={0,31,28,31,30,31,30,31,31,30,31,30,31,\
                0,31,29,31,30,31,30,31,31,30,31,30,31};
#define is_p(x) ((x%400==0||(x%100!=0&&x%4==0))?1:0)
struct today{
    int year,month,day,week;
    today(int y,int m,int d,int w):year(y),month(m),day(d),week(w){}
    void operator++(){
        day++;
        week++;
        if(week==8)week=1;
        int flag=is_p(year);
        if(day==mon[flag][month]+1){
            day=1;
            month++;
            //cout<<month<<" "<<day<<endl;
            if(month==13){
                month=1;year++;
            }
        }
    }
};
```

## 5.4 分数的四则运算

1. 套路：实际做题过程中，还是套晴神模板最好，不需要单独设符号位，符号位在分子上即可，每次运算后化简。
2. 建立分数结构类，实现加减乘除运算，符号位不用单独处理，计算时先不管分母正负，处理结果时如果分母为负，令分子分母同时取相反数即可，每次运算结束需要进行约分\(注意分子不为0时除以gcd，为0时令分母为1\)

```cpp
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
struct Fraction{
    int up,down;
    Fraction(){}
    Fraction(int a,int b):up(a),down(b){}
};
Fraction reduction(Fraction result){
    if(result.down<0){result.up=-result.up;result.down=-result.down;}
    if(result.up==0)result.down=1;
    else{
        int d=gcd(abs(result.up),result.down);
        result.up/=d;
        result.down/=d;
    }
    return result;
}
Fraction add(Fraction f1,Fraction f2){
    Fraction result;
    result.up=f1.up*f2.down+f2.up*f1.down;
    result.down=f1.down*f2.down;
    return reduction(result);
}
Fraction minu(Fraction f1,Fraction f2){
    f2.up=-f2.up;
    return add(f1,f2);
}
Fraction multi(Fraction f1,Fraction f2){
    Fraction result;
    result.up=f1.up*f2.up;
    result.down=f1.down*f2.down;
    return reduction(result);
}
Fraction divide(Fraction f1,Fraction f2){
    swap(f2.up,f2.down);
    return multi(f1,f2);
}
```

## 5.5 质数、质因子分解

1. 套路：大量质数时素数筛法，少量时用is\_prime函数
2. is\_prime函数O\(n^1/2\)或者用数组记录过程结果的筛素数法O\(nloglogn\)。
3. 对于质因子分解，首先看因子分解，如果一个数存在除1和它本身之外的其他因子，那么必定是在sqrt\(n\)两侧成对出现的。对于质因子而言，可以得到，要么所有的质因子都小于sqrt\(n\)，要么只有一个质因子大于sqrt\(n\)，所以，质因子分解可以先判断2-sqrt\(n\)之间的所有质数是否是其质因子，最后再判断除去这些质因子后是否为1，否的话说明这是一个比sqrt\(n\)大的质因子。

```cpp
bool is_prime(int n){
    if(n<=1)return false;
    for(long long i=2;i*i<=n;i++){
        if(n%i==0)return false;
    }
    return true;
}
```

## 5.6 高精度

1. 套路：写的多了，问题就少了
2. 实现大整数类，包括运算：高精度加减法、高精度与低精度的乘除法。

```cpp
struct bign{
    int d[1000],len;
    bign():len(0){}
    bign(char* str,int n):len(n){
        for(int i=n-1;i>=0;i--)
            d[n-i-1]=str[i]-'0';
    }
};
int cmp(bign& f1,bign& f2){
    if(f1.len!=f2.len){
        if(f1.len>f2.len)return 1;
        else return -1;
    }else{
        for(int i=f1.len-1;i>=0;i--){
            if(f1[i]!=f2[i]){
                if(f1[i]>f2[2])return 1;
                else return -1;
            }
        }
        return 0;
    }
}
//加法
bign add(bign& f1,bign& f2){
    bign result;
    int carry=0;
    for(int i=0;i<a.len||i<b.len;i++){
        int tmp=a[i]+b[i]+carry;
        result[result.len++]=tmp%10;
        carry=tmp/10;
    }
    if(carry!=0)result[result.len++]=carry;
    return result;
}
//减法a-b，从低位到高位，要借位
bign sub(bign a,bign b){
    bign c;
    for(int i=0;i<a.len || i<b.len;i++){
        if(a.d[i]<b.d[i]){//如果不够减
            a.d[i+1]--;
            a.d[i]+=10;
        }
        c.d[c.len++]=a.d[i]-b.d[i];
    }
    while(c.len-1>=1&&c.d[c.len-1]==0){
        c.len--;
    }
    return c;
}
//高精度与低精度的乘法
bign multi(bign a,int b){
    bign c;
    int carry=0;
    for(int i=0;i<a.len;i++){
        int temp=a.d[i] * b+carry;
        c.d[c.len++]=temp%10;
        carry=temp/10;
    }
    while(carry!=0){
        c.d[c.len++]=carry%10;
        carry/=10;
    }
    return c;
}
//高精度与低精度的除法
bign divide(bign a,int b,int& r){//r为余数，这里为引用
    bign c;
    c.len=a.len;
    for(int i=a.len-1;i>=0;i--){
        r=r*10+a.d[i];//和上一位遗留的余数组合
        if(r<b)c.d[i]=0;//不够除，该位为0
        else{
            c.d[i]=r/b;//商
            r=r%b;//获得新的余数
        }
    }
    while(c.len-1>=1&&c.d[c.len-1]==0){
        c.len--;
    }
    return c;
}
```

## java大数

```java
//创建大数类
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;

Scanner cin=new Scanner(System.in);
BigInteger num1=new BigInteger("12345");
BigInteger num2=cin.nextBigInteger();
BigDecimal num3=new BigDecimal("123.45");
BigDecimal num4=cin.nextBigDecimal();

//BigInterger整数
import java.math.BigInteger;
public class Main {
    public static void main(String[] args) {
        BigInteger num1=new BigInteger("12345");
        BigInteger num2=new BigInteger("45"); //加法
        System.out.println(num1.add(num2)); //减法
        System.out.println(num1.subtract(num2)); //乘法
        System.out.println(num1.multiply(num2)); //除法(相除取整)
        System.out.println(num1.divide(num2)); //取余
        System.out.println(num1.mod(num2)); //最大公约数GCD
        System.out.println(num1.gcd(num2)); //取绝对值
        System.out.println(num1.abs()); //取反
        System.out.println(num1.negate()); //取最大值
        System.out.println(num1.max(num2)); //取最小值
        System.out.println(num1.min(num2)); //是否相等
        System.out.println(num1.equals(num2));
    }
}
//BigDecimal(浮点数)
import java.math.BigDecimal;
public class Main {
    public static void main(String[] args) {
        BigDecimal num1=new BigDecimal("123.45");
        BigDecimal num2=new BigDecimal("4.5"); //加法
        System.out.println(num1.add(num2)); //减法
        System.out.println(num1.subtract(num2)); //乘法
        System.out.println(num1.multiply(num2)); //除法（在divide的时候就设置好要精确的小数位数和舍入模式）
        System.out.println(num1.divide(num2,10,BigDecimal.ROUND_HALF_DOWN)); //取绝对值
        System.out.println(num1.abs()); //取反 System.out.println(num1.negate()); //取最大值
        System.out.println(num1.max(num2)); //取最小值
        System.out.println(num1.min(num2)); //是否相等
        System.out.println(num1.equals(num2)); //判断大小( > 返回1, < 返回-1)
        System.out.println(num2.compareTo(num1));
    }
}
```

## 5.7 扩展欧几里得算法

* ax+by=gcd\(a,b\).如何求得x,y。边界条件，b=0时x=1,y=0;根据辗转相除法递推可得递推公式x1=y2;y1=x2-\(a/b\) \* y2;

```cpp
int exGcd(int a,int b,int& x,int& y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    int g=exGcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-(a/b) * y;
    return g;
}
```

* 方程ax+by=c的整数解，直接用扩展欧几里得算法，因为ax+by=gcd已知
* 同余式ax=c\(mod m\)求解，即ax+my=c求解，有解的条件是c%gcd\(x,m\)==0
* 逆元的求解。a,b,m&gt;0,且ab=1\(mod m\)，则称a,b互为模m的逆元
* 常用取模1e9+7
  * 1. 1000000007是一个质数
  * int32位的最大值为2147483647，所以对于int32位来说1000000007足够大
  * int64位的最大值为2^63-1，对于1000000007来说它的平方不会在int64中溢出
  * 所以在大数相乘的时候，因为\(a∗b\)%c=\(\(a%c\)∗\(b%c\)\)%c，所以相乘时两边都对1000000007取模，再保存在int64里面不会溢出

## 5.8 组合数

* 第一个问题：**求n!有多少个质因子P**
* 比如10！中有2的质因子个数可表示为：有因子2的个数为10/2，有因子2^2的个数为10/2^2，有因子2^3的个数为10/2^3

  可以递归求解，也可迭代求解。

* 即n!中有 $\frac{n}{p}+\frac{n}{p^2}+\frac{n}{p^3}+……$ 个质因子p,其中除法均为向下取整

```cpp
//迭代
int cal(int n,int p){
    int ans=0;
    while(n>0){
        ans+=n/p;
        n/=p;
    }
    return ans;
}
//递归
int cal(int n,int p){
    if(n<p)return 0;
    else return n/p+cal(n/p,p);
}
```

* 第二个问题：**组合数的计算**

  $C\_m^n=\frac{m!}{n!\(m-n\)!}$

* 方法一就是通过定义直接计算，但是因为阶乘相当庞大，此种方法计算组合数能接受的数据范围很小。
* 方法二通过递归公式计算 $C_m^n=C_{m-1}^n+C\_{m-1}^{n-1}$
* 方法三通过定义变形来计算$C\_m^n=\frac{\(m-n+1\)\(m-n+2\)……\(m-n+n\)}{n!}$，应注意到分子分母均为n项，先计算\(m-n+1\)/1，乘以\(m-b+2\)/2，不断乘以\(m-n+i\).
* 第三个问题：**如何计算$C\_n^m\%P$**
* 掌握第一种方法即可，在组合数的计算的递归公式法上改进

```cpp
int res[1010][1010]={0};
//递归方法
int C(int n,int m,int p){
    if(m==0||m==n)return 1;//C(n,0)=C(n,n)=1
    if(res[n][m]!=0)return return res[n][m];
    return res[n][m]=(C(n-1,m)+C(n-1,m-1))%p;
}
//递推方法
void CalC(){
    for(int i=0;i<=n;i++){
        res[i][0]=res[i][i]=1;//初始化边界条件
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=i/2;j++){
            res[i][j]=(res[i-1][j]+res[i-1][j-1])%p;
            res[i][i-j]=res[i][j];
        }
    }
}
```

## 5.9 错误重排问题

用A、B、C、D………表示写着n位友人名字的信封，a、b、c、d………表示n份相应的信，把n份信装错的总数记为D\(n\)，那么n-1份信封装错的总数就是D\(n-1\)。 现在，假设这样一种情况，把a错装进B中，那么对于信b有以下两种分法： 1. b装入A中，这样剩下的（n-2）份信和信封A、B，和信a、b就没有任何关系了，所以这时候装错的可能性总共有D\(n-2\)。 2. b不一定装入A中，那么就有可能装入A、C、D等其余除B之外的信封了，这时总共就是\(n-1\)种装错的可能性了。 所以对于信b来说，总共有D\(n-2\)+D\(n-1\)种装错的可能性。所以最后除a之外还有（n-1）封信，所以最终的关系式如下： `D(n)＝(n－1)*[D(n－1)＋D(n－2)]`

## 5.10 斐波那契数列

想出递推公式最重要

## 5.11 约瑟夫问题

n个人围成一个圈，每个人分别标注为1、2、...、n，要求从1号从1开始报数，报到k的人出圈，接着下一个人又从1开始报数，如此循环，直到只剩最后一个人时，该人即为胜利者。例如当n=10,k=4时，依次出列的人分别为4、8、2、7、3、10，9、1、6、5，则5号位置的人为胜利者。给定n个人，请你编程计算出最后胜利者标号数。

约瑟夫问题，创新解法虽然分析复杂，但是代码却十分简洁明了，时间O\(n\)，空间O\(1\)，这就是数学的魅力。

主要思想：n个人第一个删除的人的秩为`(k-1)%n`，假如我们已经知道了n-1个人时，最后胜利者的编号为x，利用映射关系逆推，就可以得出n个人时，胜利者的编号为\(x+k\)%n（要注意的是这里是按照映射后的序号进行的）。可以总结为： $$f(n,k)= ( f(n-1,k)+k )\%n$$

```cpp
int LastRemaining_Solution(int n, int m){
    if(n<1||m<1)return -1;
    int last=0;
    for(int i=2;i<=n;i++)
        last=(last+m)%i;
    return last;
}
```

