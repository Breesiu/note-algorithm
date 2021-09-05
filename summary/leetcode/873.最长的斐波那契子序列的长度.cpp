class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        // dp[i][j]以i,j结尾的序列长度
        
        int ans = 0;
        int n=arr.size();
        map<int,int> val2rank;
        for(int i=0;i<n;i++)val2rank[arr[i]]=i;
        vector<vector<int> > dp(n,vector<int>(n,2));
        for(int i=1;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(arr[j]-arr[i]<arr[i] && val2rank.count(arr[j]-arr[i])){
                    int k = val2rank[arr[j]-arr[i]];
                    dp[i][j] = max(dp[i][j],dp[k][i]+1);//状态转移方程 
                }
                ans = max(dp[i][j],ans);
            }
        }
        return ans<3?0:ans;
    }
};