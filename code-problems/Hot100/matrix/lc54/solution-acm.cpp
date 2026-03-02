#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.empty()) return {};
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> res;
		int top = 0, bottom = m - 1;
		int left = 0, right = n - 1;
		while (true) {
			for (int i = left; i <= right; i++) {
				res.push_back(matrix[i][top]);
			}
			if (++top > bottom) {
				break;
			}
			for (int i = top; i <= bottom; i++) {
				res.push_back(matrix[i][right]);
			}
			if (--right < left) {
				break;
			}
			for (int i = right; i >= left; i--) {
				res.push_back(matrix[i][bottom]);
			}
			if (--bottom < top) {
				break;
			}
			for (int i = bottom; i >= top; i--) {
				res.push_back(matrix[i][left]);

			}
			if (++left > right) {
				break;
			}
	
		}
		return res;
	}
};

int main() {
	
	int m, n;
	while (cin >> m >> n) {
		vector<vector<int>> matrix(m, vector<int>(n));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> matrix[i][j];
			}
		}

		Solution sol;
		vector<int> result = sol.spiralOrder(matrix);

		for (int i = 0; i < result.size(); ++i) {
			cout << result[i] << (i == result.size() - 1 ? "" : " ");
		}
		cout << endl;
	}

	return 0;
}