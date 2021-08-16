class Solution {
public:
    int ans;
    int cnt[27];
    int all_step;
    string s;
    void dfs(int step){
        ans++;
        // cout << s << endl;
        for(int i=0;i<27;i++){
            if(cnt[i]==0)continue;
            cnt[i]--;
            s.push_back(char(i+'A'));
            dfs(step+1);
            cnt[i]++;
            s.pop_back();
        }
    }
    int numTilePossibilities(string tiles) {
        ans = 0;
        all_step = tiles.size();
        for(int i=0;i<27;i++)cnt[i]=0;
        for(int i=0;i<tiles.size();i++)cnt[tiles[i]-'A']++;
        dfs(0);
        return ans-1;
    }
};