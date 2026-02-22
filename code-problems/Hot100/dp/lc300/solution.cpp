class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, 1);
        int maxLen = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);

        }
        return maxLen;
    }
};
//所有以i为最大的升序子序列都试一遍取max 
// 空间复杂度O(n^2)

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);
            }
            else {
                *it = x;
            }
        }
        return tails.size();
    }
};
//核心：同样长度的子序列，我们只保留结尾最小的那一个，更有潜力增长
//维护一个 tails 数组，tails[i] 存储的是：所有长度为 i + 1 的递增子序列中，最小的结尾数值。
//假设数组是[10, 9, 2, 5, 3, 7]：遇到 10：tails = [10]（长度为 1 的序列，结尾最小是 10）
// 遇到 9：9 比 10 小，更新长度为 1 的序列结尾。tails = [9]（因为 9 比 10 更好接人）
// 遇到 2：2 比 9 小，更新。tails = [2]
// 遇到 5：5 比 2 大，接在后面。tails = [2, 5]（说明现在最长能凑出长度为 2 的序列）
// 遇到 3：3 比 2 大，但比 5 小。它不能增加长度，但它能把长度为 2 的序列结尾从 5 降到 3。
// tails = [2, 3]
// 遇到 7：7 比 3 大，接在后面。
// tails = [2, 3, 7]最后 tails 的长度就是答案
// tails 是有序的，当我们拿一个新数字 x 进来时：如果 x 比 tails 最后一个数都大，直接 push_back。
// 否则，用二分查找找到第一个大于等于x的数，把它替换掉