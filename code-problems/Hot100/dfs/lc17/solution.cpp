class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return{};
        vector<string> phonemap = {
            "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"
        };
        vector<string> res;
        string track = "";
        backtrack(digits, 0, phonemap, track, res);
        return res;
    }
private:
    void backtrack(const string& digits, int index, const vector<string>& phonemap, string& track, vector<string>& res) {
        if (index == digits.length()) {
            res.push_back(track);
            return;
        }
        int digit = digits[index] - '0';
        string letters = phonemap[digit];
        for (char c : letters) {
            track.push_back(c);
            backtrack(digits, index + 1, phonemap, track, res);
            track.pop_back();
        }
    }

};