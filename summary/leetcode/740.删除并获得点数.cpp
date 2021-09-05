class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int p=-1,n;
        int lo=0,hi=0,last;
        while(lo<nums.size()){
            while(hi<nums.size()&&nums[hi]==nums[lo])hi++;
            if(p==-1){
                p = nums[lo]*(hi-lo);
                n = 0;
                last = nums[lo];
            }else{
                int _n=n,_p=p;
                if(last+1==nums[lo])p = nums[lo]*(hi-lo)+_n;
                else p = nums[lo]*(hi-lo)+max(_p,_n);
                n = max(_p,_n);
                last = nums[lo];
            }
            lo = hi;
        }
        return max(p,n);
    }
};