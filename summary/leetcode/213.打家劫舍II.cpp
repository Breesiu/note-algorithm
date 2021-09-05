class Solution {
public:
    int _rob(vector<int>& nums,int lo,int hi){
        int p=nums[lo],n=0;
        for(int i=lo+1;i<hi;i++){
            int _n=n,_p=p;
            p = nums[i]+_n;
            n = max(_p,_n);
            //printf("%d: %d %d\n",i,p,n);
        }
        return max(p,n);
    }
    int rob(vector<int>& nums) {
        if(nums.size()==1)return nums[0];
        return max(_rob(nums,0,nums.size()-1),_rob(nums,1,nums.size()));
    }
};