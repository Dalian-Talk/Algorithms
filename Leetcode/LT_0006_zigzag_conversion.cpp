#include <iostream>

using namespace std;

/*
 * 这题说是算法。。倒不如说是数学计算规律。。。
 *
 *
 * 0      8        16
 * 1    7 9     15 17
 * 2   6 10   14   18
 * 3 5   11 13     19
 * 4     12        20
 *
 * n行
 * n 不能为1。。。。好蠢啊。。。总结规律的时候没注意到这个2n-2 = 0就懵逼了。。
 * 第一行
 * 0                                            0+(2n-2)                                                        0+(2n-2)*2
 * 1                            1+(2n-2)-2*1    1+(2n-2)                                    1+(2n-2)*2-2*1      1+(2n-2)*2
 * 2                2+(2n-2)-2*2                2+(2n-2)                    2+(2n-2)*2-2*2                      2+(2n-2)*2
 * 3    3+(2n-2)-2*3                            3+(2n-2)    3+(2n-2)*2-2*3                                      3+(2n-2)*2
 * 4                                            4+(2n-2)
 * 这就是规律了。。。
 */

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        int length = s.length();
        string res(length, ' ');
        int n = numRows;
        int idx = 0;
        int interval_big = 2 * n - 2;
        int interval_small = 2;
        for (int i = 0; i < n; i++) {
            res[idx++] = s[i];
            int loop = 1;
            while (true) {
                if (i != 0 && i != n - 1) {
                    int mid = interval_big * loop - i;
                    if (mid < length) {
                        res[idx++] = s[mid];
                    }
                }
                int col = interval_big * loop + i;
                if (col < length) {
                    res[idx++] = s[col];
                }
                else {
                    break;
                }
                loop++;
            }
        }
        return res;
    }
};


int main() {
    string s;
    s.push_back('a');
    cout << s;
}