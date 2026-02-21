class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> cnt;
		//key:前缀和的值，value：该值出现的次数
		cnt[0] = 1;//涵盖了从头开始
		for (int x : nums) {
			sum += x;//更新目前的前缀和
			//寻找之前是否有符合条件的前缀和y，使得当前前缀和sum-y = k,需要find的是sum-k
			auto it = cnt.find(sum - k);
			if (it != cnt.end())
				ans += it->second;//找到了看看前缀和出现了几次
			cnt[sum]++;//将当前前缀和加入哈希表
		}
		return (int)ans;
	}
};