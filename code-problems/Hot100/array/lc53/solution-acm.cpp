#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int maxSum = nums[0];
		int currentSum = 0;
		for (int x : sums) {
			currentSum = max(x, currentSum + x);
			//以x结尾的最大子数组和，关心当前这一步怎么做
			maxSum = max(maxSum, ccurrentSum);
			//全局最优
		}
		return maxSum;
	}


};

int main() {
	int m;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	Solution sol;
	cout << sol.maxSubArray(nums) << "\n";
	return 0;
}