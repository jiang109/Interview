class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dpMax(n);
        vector<int> dpMin(n);
        dpMax[0] = nums[0];
        dpMin[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            long long cur = num[i];
            long long prevMax = dpMax[i - 1];
            long long prevMin = dpMin[i - 1];
            dpMax[i] = max({ cur,prevMax * cur,prevMin * cur });
            dpMin[i] = min({ cur,prevMax * cur,prevMin * cur });
            ans = max(ans, dpMax[i]);
        }
        return ans;
    }
};

//空间优化
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        int max_prev = nums[0];
        int min_prev = nums[0];
        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int x = nums[i];
            if (x < 0) {
                swap(max_prev, min_prev);
            }
            max_prev = max(x, max_prev * x);
            min_prev = min(x, min_prev * x);
            ans = max(ans, max_prev);
        }
        return ans;
    }
};
//两个时间复杂度都是O（n），前者空间复杂度O（n）,后者空间复杂度是O（1）