/*

用一个hash_table或者排序来计数，这样在dfs的过程中避免重复。

*/

class node{
public:
    int key,cnt;
    node(int k,int c){key=k;cnt=c;}
};
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> tmp;
    vector<node> vs;
    void dfs(int lo,int target){
        // printf("%d %d %d\n",vs[lo].key,vs[lo].cnt,target);
        if(target == 0){ // success
            ans.push_back(tmp);
            return;
        }
        if(lo==vs.size())return;
        for(int i=0;i<=vs[lo].cnt;i++){
            if(target < vs[lo].key * i)break;
            for(int j=0;j<i;j++)tmp.push_back(vs[lo].key);
            dfs(lo+1,target-vs[lo].key * i);
            for(int j=0;j<i;j++)tmp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        unordered_map<int,int> hash_table;
        for(int i=0;i<candidates.size();i++){
            if(hash_table.count(candidates[i])==0)hash_table[candidates[i]]=0;
            hash_table[candidates[i]]+=1;
        }
        for(auto it=hash_table.begin();it!=hash_table.end();it++)vs.push_back(node(it->first,it->second));
        dfs(0,target);
        return ans;
    }
};