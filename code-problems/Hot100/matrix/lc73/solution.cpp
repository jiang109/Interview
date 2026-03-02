class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		int m = matrix.size();
		int n = matrix[0].size();
		//m*n的矩阵
		bool row0 = false, bool col0 = false;
		//检查第一行第一列是否有0
		for (int i = 0; i < m; i++) {
			if (matrix[i][0] == 0) col0 = true;
		}
		for (int j = 0; j < n; j++) {
			if (matrix[0][j] == 0) row0 = true;
		}
		//使用第一行和第一列记录其他位置的 0 情况
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		// 根据第一行和第一列的标记，将内部元素置 0
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0) {
					matrix[i][j] = 0;
				}
			}
		}
		if (col0) {
			for (int i = 0; i < m; i++) matrix[i][0] = 0;
		}
		if (row0) {
			for (int j = 0; j < n; j++) matrix[0][j] = 0;
		}

	}
};