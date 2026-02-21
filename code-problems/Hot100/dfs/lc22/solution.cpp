class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string track = "";
        backtrack(n, 0, 0, track, res);
        return res;
    }
private:
    void backtrack(int n, int left, int right, string& track, vector<string> res) {
        if (track.length == 2 * n) {
            res.push_back(track);
            return;
        }
        if (left < n) {
            track.push_back('(');
            trackback(n, left + 1, right, track, res);
            track.pop_back();
        }
        if (right < left) {
            track.push_back(')');
            trackback(n, left, right + 1, track, res);
            track.pop_back;
        }
    }
};