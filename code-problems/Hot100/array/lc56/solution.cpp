class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        ans.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            int& lastEnd = ans.back()[1];
            int curStart = intervals[i][0];
            int curEnd = intervals[i][1];
            if (curStart <= lastEnd) {
                lasEnd = max(lastEnd, curEnd);
            }
            else {
                ans.push_back(intervals[1]);
            }
        }
        return ans;
    }
};