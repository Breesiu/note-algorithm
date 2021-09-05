class Solution {
public:
    //马拉车manacher算法的复杂度为O(n)
    string longestPalindrome(string s) {
        if(s.size()==0)return s;
        string ss;
        ss.push_back('$');
        ss.push_back('#');
        for(int i=0;i<s.size();i++){
            ss.push_back(s[i]);ss.push_back('#');
        }
        ss.push_back('\0');
        //cout<<ss<<endl;
        int n=ss.size();
        int m=0,mid=0;//记录子串长度最大值，中心，半径
        int dp[n+1];//dp[i]表示也就是以 i 为中心的最长回文半径，原字符串中的长度为dp[i]-1
        dp[0]=1;
        int mx=1,id=0;//mx是右边界，不包含
        for(int i=1;i<n-1;i++){
            if(i<mx)
                dp[i]=min(dp[2*id-i],mx-i);
            else dp[i]=1;
            while(ss[i+dp[i]]==ss[i-dp[i]])dp[i]++;//不用考虑边界条件，因为左边有'$',右边有\0
            if(i+dp[i]>mx){
                mx=i+dp[i];
                id=i;
            }
            //当下面的判断为等号时，取最靠后的最大子串，当为大于号时，取最靠前的最大子串
            if(dp[i]-1>=m){m=dp[i]-1;mid=i;}
        }
        //求得新子串中的中心元素id和最长半径，换算到原子串
        int lo,hi;
        //注意这里substr的第一个参数是开始元素的秩，第二个元素时子串长度
        lo=(mid-dp[mid]+2)/2-1;hi=(mid+dp[mid]-3)/2;

        //printf("mid=%d dp[mid]=%d lo=%d hi=%d\n",mid,dp[mid],lo,hi);
        return s.substr(lo,dp[mid]-1);
    }
};