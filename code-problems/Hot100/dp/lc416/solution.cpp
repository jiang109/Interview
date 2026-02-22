class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;
        if (sum % 2 != 0) return false;
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        //建表与初始化
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
            if (dp[target]) return true;
        }
        return dp[target];
    }
};
//每个数字只能用一次，所以要倒序
//时间复杂度：O(n × target)
// 空间复杂度：O(target)
//如果你正序（j = num 到 target）：你在计算 dp[j] 时，用到的 dp[j - num] 可能是刚刚更新过的。这相当于一个数字可以被无限次使用（变成了“完全背包”）。
//如果你倒序：你在计算 dp[j] 时，用到的 dp[j - num] 依然是上一轮循环留下的旧值。这保证了每个数字只被考虑了一次。