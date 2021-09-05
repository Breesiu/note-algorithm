class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // 答案一定是个等比数列
        sort(nums.begin(),nums.end());
        vector<int> dp(nums.size(),1); //dp[i]以 nums[i] 为最大整数的「整除子集」
        int max_size = 1,max_val = nums[0];
        for(int i=1;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0){
                    if(dp[i] < dp[j]+1){
                        dp[i] =  dp[j]+1;
                    }
                }
            }
            if(dp[i]>max_size){
                max_size = dp[i];
                max_val = nums[i];
            }
            //printf("%d:%d\n",i,dp[i]);
        }
        //printf("%d %d\n",max_size,max_val);

        vector<int> ans;
        for(int i=nums.size()-1;i>=0;i--){
            if(dp[i]==max_size && max_val%nums[i]==0){
                ans.push_back(nums[i]);
                max_val = nums[i];
                max_size--;
            }
        }
        
        return ans;
    }
};