class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> track;
        backtrack(s, 0, track, res);
        return res;
    }
private:
    void backtrack(const string& s, int start, vector<string>& track, vector<vector<string>>& res) {
        if (start == s.length()) {
            res.push_back(track);
            return;
        }
        //如果是回文串就跳过这段回文串，从下一位置开始试
        //不是回文串就就继续i++尝试这个位置的start能否有回文串
        for (int i = start; i < s.length(); i++) {
            if (isPalind(s, start, i)) {
                string sub = s.substr(start, i - start + 1);
                track.push_back(sub)：
                backtrack(s, i + 1, track, res);
                track.pop_back();
            }
        }
    }
    bool isPalind(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;

        }
        return true;
    }
};