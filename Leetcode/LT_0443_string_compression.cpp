// 0 1 2 3 4 5
// a a a b b b
// a b 1 2

// 123
// 3 2 1

class Solution {
public:
    int compress(vector<char>& chars) {
        int left = 0;
        int i = 0;
        int length = chars.size();
        while (i < length) {
            char cur = chars[i++];
            chars[left++] = cur;
            // chars[left] = cur;
            // left++;
            int count = 1;
            while (i < length && chars[i] == cur) {
                i++;
                count++;
            }
            if (count > 1) {
                string num = to_string(count); // 这边主要注意to_string的使用，很方便
                for (auto n: num) {
                    chars[left++] = n;
                }
            }
        }
        return left;
    }
};