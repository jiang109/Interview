#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return;

        k %= n;
        if (k == 0) return;

        reverse(nums.begin(), nums.end());

        reverse(nums.begin(), nums.begin() + k);

        reverse(nums.begin() + k, nums.end());
    }
};
int main() {
 
    vector<int> nums = { 1, 2, 3, 4, 5, 6, 7 };
    int k = 3;

    Solution sol;
    sol.rotate(nums, k);

    cout << "[";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;

    return 0;
}