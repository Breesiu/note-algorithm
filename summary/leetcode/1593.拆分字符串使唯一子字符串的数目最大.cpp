/*
时间复杂度：O(2^n×n)，其中 n 是字符串的长度。
回溯过程会遍历所有可能的拆分方案，长度为 n 的字符串有 n−1 个拆分点，每个拆分点都可以选择拆分或者不拆分，因此共有 2 ^ n−1 种拆分方案。
对于每种拆分方案，都需要判断拆分出的非空子字符串是否有重复，时间复杂度是 O(n)。
因此总时间复杂度是 O(2^n×n)

*/

class Solution {
public:
    int ans = 1;
    unordered_set<string> hash_table;
    void dfs(int lo,int step,string& s){
        if(lo == s.size()){
            ans = max(ans, step);
            return;
        }
        string tmp;
        for(int i=lo;i<s.size();i++){
            tmp.push_back(s[i]);
            if(hash_table.count(tmp)==0){
                hash_table.insert(tmp);
                dfs(i+1,step+1,s);
                hash_table.erase(tmp);
            }
        }
    }
    int maxUniqueSplit(string s) {
        dfs(0,0,s);
        return ans;
    }
};