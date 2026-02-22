class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n);
        //最坏情况都是1相加，长度为n+1，数值均为n
        //初始化dp
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp = min(dp[i], dp[i - j * j] + 1);//状态转移
            }
        }
        return dp[n];
    }
};
//时间复杂度O(n^3/2)
//空间复杂度O(n)
//根据拉格朗日四平方和定理：任意正整数都可以表示为不超过 4 个完全平方数的和。结果只可能是 1, 2, 3, 4。如果满足公式 $n = 4^k(8m + 7)$，答案必为 4。
class Solution {
public:
    bool isSquare(int n) {
        int temp = (int)sqrt(n);
        return temp * temp == n;
    }
    int numSquares(int n) {
        if (isSquare(n)) return 1;

        // 判断是否为 4 (利用定理：n = 4^k * (8m + 7))
        int temp = n;
        while (temp % 4 == 0) {
            temp /= 4;
        }
        if (temp % 8 == 7) return 4;

        // 判断是否为 2 (枚举 i，看 n - i*i 是否也是完全平方数)
        for (int i = 1; i * i <= n; ++i) {
            if (isSquare(n - i * i)) {
                return 2;
            }
        }

        // 排除掉 1, 2, 4，剩下的只能是 3
        return 3;
    }
};