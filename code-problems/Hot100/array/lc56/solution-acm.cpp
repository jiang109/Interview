#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            else {
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> intervals(n, vector<int>(2));
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i][0] >> intervals[i][1];
        }
        Solution sol;
        vector<vector<int>> result = sol.merge(intervals);
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i][0] << " " << result[i][1] << "\n";
        }
    }

    return 0;
}