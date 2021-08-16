/*

两种方法都需要提前计算每个元素出现的次数，用hash表，复杂度是O(n)

方法一：堆

知道了每个元素出现的次数之后，维护一个k个元素的小项堆即可。

复杂度是O（nlogk）

方法二：

用快排的partition算法，因为递归只需要进入其中一个分支，复杂度分析如下：

时间复杂度：O(N*N)，其中N为数组的长度。

设处理长度为N的数组的时间复杂度为f(N)。由于处理的过程包括一次遍历和一次子分支的递归，最好情况下，有 f(N)=O(N)+f(N/2)，根据主定理，能够得到 f(N)=O(N)。 最坏情况下，每次取的中枢数组的元素都位于数组的两端，时间复杂度退化为 O(N*N)。但由于我们在每次递归的开始会先随机选取中枢元素，故出现最坏情况的概率很低。 平均情况下，时间复杂度为 O(N)。 

空间复杂度： O(N)。哈希表的大小为 O(N)，用于排序的数组的大小也为 O(N)，快速排序的空间复杂度最好情况为 O(logN)，最坏情况为 O(N)。
*/

struct node{
public:
    int key,value;
    node(int k,int v){
        key = k;value = v;
    }
};
class Solution {
public:
    int partition(vector<node>& v, int lo,int hi){ // [lo,hi]
        node tmp = v[lo];
        int _lo=lo,_hi=hi;
        // printf("start:%d %d\n",lo,hi);
        // for(int i=_lo;i<=_hi;i++)printf("%d\t",v[i].key);printf("\n");
        // for(int i=_lo;i<=_hi;i++)printf("%d\t",v[i].value);printf("\n");
        while(lo<hi){
            while(lo<hi && v[hi].value <= tmp.value)hi--;
            v[lo] = v[hi];
            while(lo<hi && v[lo].value >= tmp.value)lo++;
            v[hi] = v[lo];
        }
        v[lo] = tmp;
        // printf("%d %d\n",lo,hi);
        // for(int i=_lo;i<=_hi;i++)printf("%d\t",v[i].key);printf("\n");
        // for(int i=_lo;i<=_hi;i++)printf("%d\t",v[i].value);printf("\n");
        return lo;
        
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> hash_table;
        vector<node> tmp;
        vector<int> ans;
        for(int i:nums){
            if(hash_table.count(i)==0)hash_table[i]=0;
            hash_table[i]++;
        }
        for(auto it = hash_table.begin();it!=hash_table.end();it++){
            tmp.push_back(node(it->first,it->second));
            // printf("# %d %d\n",it->first,it->second);
        }
        int lo=0,hi=tmp.size()-1;
        while(lo<hi){
            int t = partition(tmp,lo,hi);
            // printf("return:%d\n",t);
            if(k-1==t)break;
            else if(k-1>t) lo=t+1;
            else hi=t-1;
        }
        for(int i=0;i<k;i++)ans.push_back(tmp[i].key);
        return ans;
    }
};