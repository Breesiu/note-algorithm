class Solution {
public:
    int _rob(vector<int>& nums,int lo,int hi,int n){
        vector<int> pos(n+1,0),neg(n+1,0);
        for(int i=lo;i<hi;i++){//[lo,i]个元素中
            for(int j=n;j>0;j--){//包含j个元素
                int _p = pos[j];
                pos[j] = nums[i]+neg[j-1];
                neg[j] = max(neg[j],_p);
            }
            // printf("###%d\n",i);
            // for(int j=1;j<n;j++)printf("%d ",pos[j]);printf("\n");
            // for(int j=1;j<n;j++)printf("%d ",neg[j]);printf("\n");
        }
        return max(pos[n],neg[n]);
    }
    int maxSizeSlices(vector<int>& slices) {
        int n=slices.size()/3;
        return max(_rob(slices,0,3*n-1,n),_rob(slices,1,3*n,n));
    }
};