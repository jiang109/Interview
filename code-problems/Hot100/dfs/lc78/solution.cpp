class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> track;
        backtrack(nums, 0, track, res);
        return res;
    }

private:
    void backtrack(vector<int>& nums, int start, vector<int>& track, vector<vector<int>>& res) {
        res.push_back(track);
        for (int i = start; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(nums, i + 1, track, res);
            track.pop_back();
        }
    }
};