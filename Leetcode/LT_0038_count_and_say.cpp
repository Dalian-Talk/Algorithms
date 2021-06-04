#include <iostream>

using namespace std;


class Solution {
public:
    /*
     * 难度不大，就是一个正常的处理流程。
     * 关键是领会一下中间的计算过程
     *
     * 11122333
     * 如何计算开始的3个1？？
     * j 从 0 开始 一直找。找到j + 1 和j不同 或者j + 1到头了 >> j + 1 == res.length()
     * 那么j就停下来了。。
     * j停在哪？？
     * j停在最后一个与开始j = 0 相同的字符处。
     * 这个循环的作用要搞清楚。。。。。否则很多循环的最终结果都是懵逼的。。然后写其他题都出问题了！！！！
     * while (j + 1 < res.length() && res[j] == res[j + 1])
     * 这个循环条件两种情况停下
     *
     * 1、 j + 1 == res.length()
     * 2、 res[j + 1] != res[j]
     *
     * 那么首先看1，如何能到1的条件？？是不是必须建立在上一次满足2，才能到1？也就是
     * 例如 2111
     * 跑到倒数第二个和第一个1，这次判断过了。然后下一次j到最后一个1了。j + 1 == res.length()了。
     * 那么对于1。最终j停在了最后一个1
     *
     * 再看2，每次都是看下一个是不是跟当前的相同，不相同就停下。
     * 例如 1112
     * 那么也相当于j最后停在了1上。
     *
     * 那么怎么计数？？
     * 如果我们是每次满足 过了 1 2 (也就是 j + 1 < res.length(), res[j + 1] == res[j])
     * 然后计数 +1
     * 那么最后一个数字就记录不到了。
     * 所以这个判断条件是。当我们找到下一个符合要求的相同数字时，我们的count + 1。
     * 这么一看就很明显了。count是从1开始的。从当前这个字符开始。往下找，找到一个符合的 + 1。
     *
     *
     * 写这么多主要是为了让自己理解这个循环在干嘛。。为之后的一些题目做铺垫。。23333
     *
     */
    string countAndSay(int n) {
        string res = "1";
        for (int i = 1; i < n; i++) {
            string cur;
            for (int j = 0; j < res.length(); j++) {
                int count = 1;
                while (j + 1 < res.length() && res[j] == res[j + 1]) {
                    j++;
                    count++;
                }
                cur += to_string(count) + res[j];
            }
            res = cur;
        }
        return res;
    }
};