class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        int n=matrix.size(),m=matrix[0].size();
        int ans=0x80000000;
        int x0,y0,x1,y1;
        vector<int> b(m);
        for(int i=0;i<n;i++){
            fill(b.begin(),b.end(),0);
            for(int j=i;j<n;j++){
                // [i:j]行转化为1维问题，然后用Kadane算法
                int cur=0,start=0;
                for(int k=0;k<m;k++){
                    b[k]+=matrix[j][k];
                    if(cur<0){
                        cur = 0;
                        start = k;
                    }
                    cur += b[k];
                    if(cur>ans){
                        ans = cur;
                        y0 = i;
                        y1 = j;
                        x0 = start;
                        x1 = k;
                    }
                }
            }
        }
        return vector<int>{y0,x0,y1,x1};
    }
};