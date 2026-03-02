class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> ans;
        //m*n
        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;
        while (true) {
            // 1. 从左向右走在 top 行
            for (int i = left; i <= right; ++i) ans.push_back(matrix[top][i]);
            if (++top > bottom) break;
            // 2. 从上向下走在 right 列
            for (int i = top; i <= bottom; ++i) ans.push_back(matrix[i][right]);
            if (--right < left) break; 
            // 3. 从右向左走在 bottom 行
            for (int i = right; i >= left; --i) ans.push_back(matrix[bottom][i]);
            if (--bottom < top) break; 
            // 4. 从下向上走在 left 列
            for (int i = bottom; i >= top; --i) res.push_back(matrix[i][left]);
            if (++left > right) break; // 走完一列，左边界右移
        }
        return ans;

    }
};