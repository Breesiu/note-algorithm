class Solution {
public:
    int rob(vector<int>& nums) {
        int p=nums[0],n=0;
        for(int i=1;i<nums.size();i++){
            int _n=n,_p=p;
            p = nums[i]+_n;
            n = max(_p,_n);
            //printf("%d: %d %d\n",i,p,n);
        }
        return max(p,n);
    }
};