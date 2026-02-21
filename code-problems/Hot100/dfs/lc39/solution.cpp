class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> track;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, 0, track, res);
        return res;
    }
private:
    void backtrack(vector<int>& candidates, int target, int sum, int start, vector<int>& track, vector<vector<int>>& res) {
        if (sum == target) {
            res, push_back(track);
            return;
        }
        if (sum > target) {
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (sum + candidates[i] > target) break;
            track.push_back(candidates[i]);
            trackback(candidates, target, sum + candidates[i], i, track);
            track.pop_back();
        }
    }
};