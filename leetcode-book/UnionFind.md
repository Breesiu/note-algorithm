# 并查集 Union Find

* https://leetcode-cn.com/leetbook/detail/disjoint-set/

可以使用「并查集」解决的问题，一般都可以使用「深度优先搜索」和「广度优先搜索」完成。但是「深度优先搜索」和「广度优先搜索」不仅回答了连接问题，还回答了路径问题，时间复杂度高。

重点：
* 路径压缩
* 每个操作的复杂度是O（1）

```cpp
class DisjointSet{
    private:
        vector<int> fa;
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
    public:
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
};
```

## 399. 除法求值

在并查集的基础上，设计辅助的数组记录信息，灵活运用路经压缩。

```cpp
class Dict{
    private:
        map<string, int> str2int;
        vector<string> int2str;
    public:
        Dict(){}
        int push(string t){
            if(!exists(t)){
                str2int.insert(pair<string,int>(t, int2str.size()));
                int2str.push_back(t);
            }
            return str2int[t];
        }
        bool exists(string t){
            return str2int.count(t) != 0;
        }
        int const operator[](string t){
            if(exists(t))
                return str2int[t];
            else
                return -1;
        }
        string const operator[](int t){
            return int2str[t];
        } 
        int size(){
            return int2str.size();
        }   
};
class DisjointSet{
    public:
        vector<int> fa;
        vector<double> rate;
        pair<int,double> _find(int x){
            if(fa[x]==x)return pair<int,double>(x,1.0);
            else{
                int t = fa[x];
                double r = rate[x];
                pair<int,double> tmp = _find(t);
                fa[x] = tmp.first;
                rate[x] = r*tmp.second;
                return pair<int,double>(fa[x],rate[x]);
            }
        };
        DisjointSet(int size){
            for(int i=0;i<size;i++){
                fa.push_back(i);
                rate.push_back(1.0);
            }
        };
        int _union(int a, int b, double r){
            pair<int,double> fa_a = _find(a);
            pair<int,double> fa_b = _find(b);
            fa[fa_a.first] = fa_b.first;
            rate[fa_a.first] = r * fa_b.second / fa_a.second;
            return fa_b.first;
        };
        bool same(int a,int b){
            return _find(a).first == _find(b).first;
        };
        bool root(int a){
            return fa[a] == a;
        }
};
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        vector<double> ans;
        Dict dict;
        DisjointSet ds(500);
        for(int i=0;i<equations.size();i++){
            string a = equations[i][0];
            string b = equations[i][1];
            double v = values[i];
            int ia = dict.push(a);
            int ib = dict.push(b);
            ds._union(ia, ib, v);
        }
        // for(int i=0;i<dict.size();i++){
        //     cout << "#" << i << endl;
        //     cout << dict[i] << endl;
        //     cout << ds.fa[i] << endl;
        //     cout << ds.rate[i] << endl;
        // }
        for(int i=0;i<queries.size();i++){
            int ia = dict[queries[i][0]];
            int ib = dict[queries[i][1]];
            double t_ans;
            if(ia == -1 || ib == -1){
                t_ans = -1.0;
            }else{
                if(ds.same(ia,ib)){
                    double r1 = ds._find(ia).second;
                    double r2 = ds._find(ib).second;
                    t_ans = r1/r2;
                }else{
                    t_ans = -1.0;
                }
            }
            // cout << "ans:" << t_ans << endl;
            ans.push_back(t_ans);
        }
        return ans;
    }
};
```

## 959. 由斜杠划分区域

这个题目比较一般，没啥特殊的，将每个块分为四个，然后合并对应的块，最后看并查集的个数。

```cpp
class DisjointSet{
    private:
        vector<int> fa;
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
    public:
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
        int blocks(){
            int cnt = 0;
            for(int i=0;i<fa.size();i++){
                if(root(i))cnt++;
            }
            return cnt;
        }
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        DisjointSet ds(grid.size()*grid.size()*4);
        for(int i=0;i<grid.size();i++){
            int cnt_i = grid.size()*4*i;
            for(int j=0;j<grid[i].size();j++){
                if(j!=grid[i].size()-1){
                    ds._union(cnt_i+j*4+2,cnt_i+(j+1)*4+0);
                }
                if(grid[i][j]=='\\'){
                    ds._union(cnt_i+j*4+1,cnt_i+j*4+2);
                    ds._union(cnt_i+j*4+0,cnt_i+j*4+3);
                }else if(grid[i][j]=='/'){
                    ds._union(cnt_i+j*4+0,cnt_i+j*4+1);
                    ds._union(cnt_i+j*4+2,cnt_i+j*4+3);
                }else{
                    ds._union(cnt_i+j*4+0,cnt_i+j*4+1);
                    ds._union(cnt_i+j*4+1,cnt_i+j*4+2);
                    ds._union(cnt_i+j*4+2,cnt_i+j*4+3);
                }
                if(i!=grid.size()-1){
                    ds._union(cnt_i+j*4+3,cnt_i+grid.size()*4+j*4+1);
                }
            }
            
        }
        return ds.blocks();
    }
};
```

## 778. 水位上升的泳池中游泳

这个题目有三种解法
* 结合二分查找做BFS或DFS遍历 $n^2*logn$
    * 选择不同的高度，然后做遍历，看首尾是否可相连。
* 并查集
    * 从小到大将点和他的上下左右合并操作，判断起点和终点是否在并查集中。
* 图的最短路径算法
    * 动态维护从起点到各个定点的最短路径，加上


```cpp
class DisjointSet{
    private:
        vector<int> fa;
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
    public:
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
};
class Solution {
public:
    int dires[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
    bool vaild(int x,int y,int N){
        return (x>=0)&&(y>=0)&&(x<N)&&(y<N);
    }
    void deal(int i,vector<vector<int>>& grid,DisjointSet& ds){
        int N = grid.size();
        int x=i/N;
        int y=i%N;
        for(int j=0;j<4;j++){
            int nx = x + dires[j][0];
            int ny = y + dires[j][1];
            if(vaild(nx,ny,N)){
                if(grid[nx][ny]<=grid[x][y]){
                    ds._union(i,nx*N+ny);
                }
            }
        }
    }
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        DisjointSet ds(N*N);
        map<int, vector<int> > m;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                int r = i*N+j;
                int v = grid[i][j];
                if(m.count(v)==0){
                    m.insert(pair<int,vector<int> >(v,vector<int>()));
                }
                m[v].push_back(r);
            }
        }
        for(auto iter=m.begin();iter!=m.end();iter++){
            for(int j=0;j<iter->second.size();j++){
                deal(iter->second[j],grid,ds);
            }
            if(ds.same(0,N*N-1)){
                return iter->first;
            }
        }
        return 0;
    }
};
```

图算法
```cpp
#define inf 0x7fffffff
class node{
    public:
        int x;
        int y;
        int v;
        node(int x,int y,int v):x(x),y(y),v(v){}
        bool operator<(const node& b) const {
            return v > b.v;
        }
};
class Solution {
public:
    int dires[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
    bool vaild(int x,int y,int N){
        return (x>=0)&&(y>=0)&&(x<N)&&(y<N);
    }
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        vector<vector<bool>> vis(N,vector<bool>(N,false));
        priority_queue<node> dist;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i==0&&j==0)dist.push(node(i,j,grid[i][j]));
                else dist.push(node(i,j,inf));
            }
        }
        while(true){
            auto t = dist.top();
            dist.pop();
            if(t.x == N-1 && t.y == N-1){
                return t.v;
            }
            vis[t.x][t.y]=true;
            for(int i=0;i<4;i++){
                int nx = t.x + dires[i][0];
                int ny = t.y + dires[i][1];
                if(vaild(nx,ny,N)&&!vis[nx][ny]){
                    dist.push(node(nx,ny,max(t.v,grid[nx][ny])));
                }
            }
        }
        return 0;
    }
};
```

## 1202. 交换字符串中的元素

可以推导出：**交换关系可以传递**

需要注意：
* 需要建立并查表的倒排，否则会超时间

```cpp
class DisjointSet{
    private:
        vector<int> fa;
    public:
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
};
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        DisjointSet ds(s.length());
        for(int i=0;i<pairs.size();i++){
            ds._union(pairs[i][0],pairs[i][1]);
        }
        map<int, vector<int> > m;
        for(int i=0;i<s.length();i++){
            int r = ds._find(i);
            if(m.count(r)==0){
                m.insert(pair<int,vector<int> >(r,vector<int>()));
            }
            m[r].push_back(i);
        }
        for(auto iter=m.begin();iter!=m.end();iter++){
            vector<int> nums(27,0);
            int root = iter->first;
            vector<int> rs = iter->second;
            for(int j=0;j<rs.size();j++){
                nums[s[rs[j]]-'a']++;
            }
            int t=0;
            for(int j=0;j<rs.size();j++){
                while(nums[t]==0)t++;
                s[rs[j]] = 'a'+t;
                nums[t]--;
            }
        }
        return s;
    }
};
```

## 947. 移除最多的同行或同列石头

首先需要明确的是：同行同列的都属于一个并查集，然后按照规则每个并查集只会留下一颗石头。

```cpp
class DisjointSet{
    private:
        vector<int> fa;
        int _find(int x){
            if(fa[x]==x)return x;
            else{
                int t = fa[x];
                fa[x] = _find(t);
                return fa[x];
            }
        };
    public:
        DisjointSet(int size){
            for(int i=0;i<size;i++)fa.push_back(i);
        };
        int _union(int a, int b){
            int fa_a = _find(a);
            int fa_b = _find(b);
            fa[fa_a] = fa_b;
            return fa_b;
        };
        bool same(int a,int b){
            return _find(a) == _find(b);
        };
        bool root(int a){
            return fa[a] == a;
        }
        int count(){
            int cnt=0;
            for(int i=0;i<fa.size();i++)
                if(root(i))cnt++;
            return cnt;
        }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int cnt = 0;
        DisjointSet ds(stones.size());
        map<int,vector<int>> m0,m1;
        map<pair<int,int>, int> pos2rank;
        for(int i=0;i<stones.size();i++){
            pos2rank.insert(pair<pair<int,int>, int>(pair<int,int>(stones[i][0],stones[i][1]),i));
            if(m0.count(stones[i][0])==0){
                m0.insert(pair<int,vector<int>>(stones[i][0],vector<int>()));
            }
            m0[stones[i][0]].push_back(stones[i][1]);
            if(m1.count(stones[i][1])==0){
                m1.insert(pair<int,vector<int>>(stones[i][1],vector<int>()));
            }
            m1[stones[i][1]].push_back(stones[i][0]);
        }
        for(auto iter=m0.begin();iter!=m0.end();iter++){
            int x = iter->first;
            vector<int>& ys = iter->second;
            for(int j=0;j<ys.size()-1;j++){
                ds._union(pos2rank[pair<int,int>(x,ys[j])],pos2rank[pair<int,int>(x,ys[j+1])]);
            }
        }
        for(auto iter=m1.begin();iter!=m1.end();iter++){
            int y = iter->first;
            vector<int>& xs = iter->second;
            for(int j=0;j<xs.size()-1;j++){
                ds._union(pos2rank[pair<int,int>(xs[j],y)],pos2rank[pair<int,int>(xs[j+1],y)]);
            }
        }
        return stones.size()-ds.count();
    }
};
```

## 803. 打砖块

