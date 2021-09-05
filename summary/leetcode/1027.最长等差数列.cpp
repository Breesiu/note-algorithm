class Solution {
public:
    int longestArithSeqLength(vector<int>& arr) {
        // dp[i][diff]为以第i位数为结尾且公差为diff的最长等差子序列长度。
        int ans = 0;
        int n=arr.size();
        vector<unordered_map<int,int> > dp(n);
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                int diff = arr[i]-arr[j];
                if(dp[j].count(diff)){
                    dp[i][diff] = max(dp[i][diff],dp[j][diff]+1);
                }else{
                    dp[i][diff] = 2;
                }
                ans = max(ans,dp[i][diff]);
            }
        }
        return ans;
    }
};

class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        if (A.empty()) {
            return 0;
        }

        int N = A.size();
        vector<vector<int>> dp(N, vector<int>(20010, 1));

        int res = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                auto diff = A[i] - A[j];
                int offset = 10000;
                diff += offset;
                dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
                res = max(dp[i][diff], res);
            }
        }

        return res;
    }
};
