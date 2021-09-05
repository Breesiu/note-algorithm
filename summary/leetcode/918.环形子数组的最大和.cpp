class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int ans1 = Kadane(nums,0,nums.size(),1);
        int sum=0,max_num=nums[0];
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            max_num = max(max_num,nums[i]);
        }
        if(max_num<0)return max_num;
        int ans2 = Kadane(nums,0,nums.size(),-1);
        printf("%d %d %d\n",ans1,ans2,sum+ans2);
        return max(ans1,sum+ans2);
    }
    int Kadane(vector<int>& nums,int lo,int len,int sign){
        int ans=sign*nums[lo],cur=sign*nums[lo];
        for(int i=lo+1;i<lo+len;i++){
            cur = sign*nums[i] + max(cur,0);
            ans = max(ans, cur);
        }
        return ans;
    }
};