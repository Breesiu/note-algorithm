class Solution {
public:
    int countSubstrings(string s) {
        int n=s.size();
        int sum=0;
        for(int i=0;i<n;i++){
            sum++;
            int j=1;
            while(i-j>=0 && i+j<n){
                if(s[i-j]==s[i+j])sum++;
                else break;
                j++;
            }
            j=0;
            while(i-j>=0 && i+1+j<n){
                if(s[i-j]==s[i+1+j])sum++;
                else break;
                j++;
            }
        }
        return sum;
    }
};