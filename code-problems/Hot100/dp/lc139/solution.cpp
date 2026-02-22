class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //用哈希，将字典转为集合，方便快速查找
        unordered_map<string> wordset(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordset.find(s.substr(j, i - j)) != wordset.end()) {
                    dp[i] = true;
                    break;//只需要有一种就是true
                }
            }
        }
        return dp[n];
    }
};