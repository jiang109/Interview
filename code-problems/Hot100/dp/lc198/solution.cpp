class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        int prev2 = 0;//dp[i-2]
        int prev1 = 0;//dp[i-1]
        int current = 0;//dp[i]
        for (int x : nums) {
            current = max(prev1, prev2 + x);//状态转移
            prev2 = prev1;
            prev1 = current;//用来省空间

        }
        return current;
    }
};
//注意思路，不能单独求奇数位和与偶数位和比较
//反例[2,1,1,2]