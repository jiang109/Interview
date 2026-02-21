class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> track;
        vector<bool> used(nums.size(), false);
        backtrack(nums, track, used, res);
        return res;
    }

private:
    void backtrack(vector<int>& nums, vector<int>& track, vector<bool>& used, vector<vector<int>>& res) {
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 2. 剪枝：如果已经使用过该元素，则跳过
            if (used[i]) continue;
            // 3. 做选择
            track.push_back(nums[i]);
            used[i] = true;
            // 4. 进入下一层决策
            backtrack(nums, track, used, res);
            // 回溯：恢复现场，尝试同层级其他可能性
            track.pop_back();
            used[i] = false;
        }
    }
};