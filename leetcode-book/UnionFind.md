# 并查集 Union Find

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