class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for (char c : t) need[c]++;
        int left = 0, right = 0;
        int valid = 0;
        int start = 0, minLen = INT_MAX;
        while (right < s.size()) {
            //维护一个窗口看符不符合要求
            char c = s[right];
            right++;
            //处理新加入的c
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c])
                    valid++:
                //valid+1表示其中一个char完成要求了
                //一共需要的、不同的char为need.size()
            }
            //valid=need.size()时表示每个char需要的已经凑齐，此时开始寻找最小
            while (valid == need.size()) {
                if（right - left < minLen){
                    start = left;
                    minLen = right - left;

                }
                //从最左边的试能不能挪出窗口
                char d = s[left];
                left++;
                //如果确实被need需要，则说明不可以溢出，我们通过valid来标记
                if (need.count(d)) {
                    if (window[d] == need[d])
                        valid--;
                    window[d]--;
                }
            }
        }
        return minLen == INT_MAX ? "" : s.substr(start, minLen);

    }
};
//时间复杂度是两个指针各扫一遍+初始化need字典的n，一共O(m+n)
//unordered_map在O(1)时间内查找字符