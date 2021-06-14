#include <iostream>

using namespace std;

/*
 *          a0 a1 a2
 *          b0 b1 b2
 *
 * c0 c1 c2 c3 c4 c5
 */


class Solution {
public:
    /*
     * 利用 a * b 结果最长也就是 a.length() + b.length()来构造结果然后一步一步算就行了
     * 写的过程注意 数字 和 字符之间的转化。。。
     *
     */
    string multiply(string num1, string num2) {
        int len1 = num1.length();
        int len2 = num2.length();
        string res(len1 + len2, '0');

        // 从个位开始
        for (int i = len1 - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = len2 - 1; j >= 0; j--) {
                int cur = (res[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
                carry = cur / 10;
                cur %= 10;
                res[i + j + 1] = cur + '0';
            }
            // 算完对应位置后，的最前一位，如果carry有数就要放过去。
            // 刚好是res[i]就是这个位置。。所以也不用单独去判断了。
            res[i] += carry;
        }
        int start_idx = res.find_first_not_of('0');
        if (start_idx == string::npos) return "0";
        return res.substr(start_idx);
    }
};