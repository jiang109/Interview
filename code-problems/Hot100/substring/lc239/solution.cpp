class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> dq;
		//存储数组下标，且这些下标对应的数值从大到小排列
		vector<int> ans;
		int n = (int)nums.size();
		ans.reserve(n - k + 1);
		//会产生n-k+1个窗口
		for (int i = 0; i < n; i++) {
			while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
			//窗口向右滑动中
			//如果滑动前的最大值（即队列的最左边）下标已经不在窗口范围内了，需要踢出滑动窗口
			while (!dq.empty() && nums[dq.back() ]<= num[i]]) dq.pop_back();
			//向右滑动遇到的第一个元素，要把所有目前在队列里且比该元素小的全部踢出队列，因为它们不再可能是最大值（之前保留下来的原因在于，当窗口向右滑动时，还有可能把max项扔掉后成为最大值）
			dp.push_back(i);
			if (i >= k - 1) ans.push_back(nums[dq.front()]);
			//每次滑动结束后的front()即为该窗口的max值
		}
		return ans;
	}
};