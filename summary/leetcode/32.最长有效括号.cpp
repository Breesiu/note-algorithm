class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.size(),0);// dp[i]表示以s[i]结尾的连续括号字串的长度
        int ans=0;
        for(int i=1;i<s.size();i++){
            if(s[i]=='(')continue;
            if(s[i-1]=='('){
                dp[i]=2;
                if(i-2>=0)dp[i]+=dp[i-2];
            }else{
                if(i-1-dp[i-1]>=0 && s[i-1-dp[i-1]]=='('){
                    dp[i] = 2+dp[i-1];
                    if(i-1-dp[i-1]-1>=0)dp[i]+=dp[i-1-dp[i-1]-1];
                }
            }
            // printf("%d %d\n",i,dp[i]);
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};