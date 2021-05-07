#include <iostream>
#include <vector>



using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 简单的 brute-force。。。一点都不简单。子串要一个一个检查。。。不想写这个方法
        return 0;
    }

    int lengthOfLongestSubstring1(string s) {
        // 滑动窗口。。右边一直动，找到重复的，看左边的窗口应该放到哪里。
        // 如果遇到出现过的，看看之前出现的在左边界的外还是内，取两者中大的那个。
        vector<int> char_pos(128, -1);
        int longest = 0;
        int left = 0;

        for (int i = 0; i < s.length(); i++) {
            if (char_pos[s[i]] != -1) {
                left = max(left, char_pos[s[i]] + 1);
            }
            char_pos[s[i]] = i;
            longest = max(longest, i - left + 1);
        }
        return longest;
    }
};