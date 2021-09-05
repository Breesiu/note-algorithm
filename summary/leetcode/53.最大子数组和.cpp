class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans=nums[0],cur=nums[0];
        for(int i=1;i<nums.size();i++){
            cur = nums[i] + max(cur,0);
            ans = max(ans, cur);
        }
        return ans;
    }
};