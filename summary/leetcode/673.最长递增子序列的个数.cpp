/*
相比于最长递增子序列，这里只能在两次循环这个方法上改进，复杂度说是n*n
*/

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),1); // dp[i]表示以nums[i]结尾的最长子序列的长度
        vector<int> cnt(nums.size(),1); // cnt[i]表示以nums[i]结尾的最长子序列的个数
        dp[0] = 1;
        cnt[0] = 1;
        int max_length = 1;
        for(int i=1;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){//只考虑递增子序列
                    if(dp[i]<=dp[j]){
                        dp[i] = dp[j]+1;
                        cnt[i] = cnt[j];
                    }else if(dp[i]==1+dp[j]){
                        cnt[i] += cnt[j];
                    }
                }
            }
            max_length = max(max_length, dp[i]);
            // cout << "idx"<< i << ":" << dp[i] << " " << cnt[i] << endl;
        }
        int ans = 0;
        for(int i=0;i<nums.size();i++)
            if(max_length==dp[i])
                ans += cnt[i];
        return ans;
    }
};