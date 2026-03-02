class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size();
		int n = matrix[0].size();
		//m*n
		if (target < matrix[0][0] || target > matrix[m - 1][n - 1]) return false;
		int up = 0, down = m - 1;
		// 确定 target 可能存在的最后一列
		int left = 0, right = n - 1;
		// 在第一行中寻找第一个比 target 大的数字的迭代器
		auto it_r = upper_bound(matrix[0].begin(), matrix[0].end(), target);
		// 计算该迭代器到行首的距离，减 1 得到最后一个“可能小于等于 target”的列索引
			right = distance(matrix[0].begin(), it_r) - 1;
		// 如果整个第一行都比 target 大，right 会变成 -1
		if (right < 0) return false;
		int r = 0;
		int c = right;
		while (r < m && c >= 0) {
			int val = matrix[r][c];
			if (val == target) return true;
			if (val > target) {
				// 如果当前值大于 target，向左移动
				c--;
			}
			else {
				// 如果当前值小于 target，向下移动
				// 优化：跳过不可能的行
				r++;
			}
		}
		return false;

	}
};