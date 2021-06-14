#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
    /* 经典的dp了。pattern的后续比较都是建立在之前的比较上，然后根据多个选择决定结果。
     * 感觉比之前那个简单。。之前那个还得带上 *之前的字母。。。
     *
     * 有一堆相同的子事件，有一个base事件，每到一个事件都得多次选择。。。 >>> dp 或者memo的dfs也行
     *
     *
     * .....s[j]
     * .....p[i]
     * 相比于之前那个题，这里就简单多了。。
     * 1、如果p[i] != '?' && p[i] != s[j]，那么dp[i][j]自然是false
     * 2、如果p[i] == '?' || p[i] == s[j]，自然是这俩匹配了，看前面的 dp[i - 1][j - 1]
     * 3、如果p[i] == '*'
     * 类似前面的
     * p[i] 可以充当0个，1个，2个，3个(3个及其以上就和2个是一样的了，都相当于往前面考虑了一步，然后只要从0开始每个都往前考虑一步。就都往前考虑了。。)
     *      p[i] 充当0个 dp[i - 1][j]
     *      p[i] 充当1个 dp[i - 1][j - 1]
     *      p[i] 充当2个(或者更多) dp[i][j - 1]。这个从这边不好理解，用例子就行了。。跟之前一样
     *
     *      ....ba
     *         ..*
     *      这么看，*可以代表a,或者ba。那么字符串可以写成
     *      ....(ba)
     *        ..(*a)
     *      *还是*因为它可以继续变更多的子序列。。
     *      也就是说当*代表了更多的时候。对于S这个串。当前的s[j]也就被表示出来了，也就不够用了，往前找找2333。。然后把*在之前对着b的那个状态拿过来一起参与比较就行了。
     *      这么一列出来就看着很舒服了。。一下就知道了往s的前一个看一下状态了。
     *
     *
     */
    bool isMatch(string s, string p) {
        int len1 = s.length();
        int len2 = p.length();
        vector<vector<bool>> dp(len2 + 1, vector<bool>(len1 + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= len2; i++) {
            if (p[i - 1] == '*') {
                dp[i] = dp[i - 1];
            }
        }

        for (int i = 1; i <= len2; i++) {
            for (int j = 1; j <= len1; j++) {
                if (p[i - 1] == '?' || p[i - 1] == s[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[i - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - 1] || dp[i][j - 1];
                }
            }
        }
        return dp[len2][len1];

    }

    /*
     * 先把一般递归版本的backtracking写出来，然后分析为什么会TLE(time limit exceeded)
     * 不会TLE的版本，其实是用了Greedy的思想来剪枝，让判断情况大大减少。这里先分析这边为什么多做了很多操作。
     *
     * 例如我们有这么一个s 和p
     * s: asdqweqgqweqwebbbbbbbba
     * p: a************************b
     *
     * 首先一眼看过去就知道p不能匹配s。原因就是。p结尾是b，s结尾是a。两边不存在最终匹配的问题。
     * 但是如果在一般的backtracking中，问题就来了。
     * 当我们处理完最后一个*后，我们发现不能匹配。然后倒数第二个*就会for循环多一点，也就是这个*多匹配一点上面的s
     * 然后发现还是不行，最后回溯到倒数第三个*，再来做一遍所有的。
     * 这。。就是。。真。。。穷举。。算是把每个*从匹配s中0个到能多长就多长。。都试过了。。。
     * 但是实际上，我们只要看最后一个*就行了。。前面的*如果能匹配，早就匹配了 不耽误后面的*。
     * 前面的如果不行，也到不了后面的*
     * 分析个流程来说明心中的疑惑吧。(反正说给自己听。。也方便不是)
     *
     * 1、首先，我们所有的*都是从 匹配空串开始的。也就是所有的*都是从一个字符都不匹配开始，然后慢慢变多的。
     *    这个道理很明显。。。我们不能让*一次匹配太多。。这样子会让不是*的字符错过正确的匹配位置。
     * 2、当我们遇到第二个*的时候，第一个*要怎么处理？
     *    两个情况
     *       s: abababababb
     *    a) p: a**b
     *    b) p: a*b*b
     *    两种p的方式，都能符合最终匹配的要求。并且有两个不同类型的*区别
     *    对于a)很明显，，第一个*没啥用了。。第二个*可以做到第一个*做到的所有事情
     *    对于b)就不是那么直观了。但是我们可以分析。
     *      如果我们不能到第二个*，也就是在第一个* 和 b就卡死了，举例如：
     *      s: acccccddddd
     *      p: a*b*b
     *      那么很明显，第一个b都过不去，谈何到第二个*呢？
     *      所以如果不能到第二个*，那么就是false
     *      如果能到第二个*呢？(忽略上面错误的情况)
     *      那就意味着a*b可以在s中匹配一段，那么第一个*的作用也就到此为止了。为什么不用担心第一个*匹配太少而导致结果不对呢？
     *      1、我们是让*从最少开始的，所以当我们能匹配到的那一刻开始，就意味着这段ok了。后续所有剩余的可以交给第二个*
     *      2、如果第二个*都无法让后面的那一段保证匹配成功，那我们把第二个*置为空，然后从第一个*往后可劲的加匹配数量，也没用。
     *      从b)的例子中就是
     *      结果上，我们让a*b成为 ab，或者是 abab都是一样的。
     *      但是我们选择让a*b成为ab就行了。因为ab的后续 ab可以被第二个*代替，
     *
     *
     * 写这么多只是分析。。为啥不这么做会TLE。。开始的我肯定想不到。。所以对我来说没差。。23333
     * 这个greedy真的挺巧妙的。。
     * 1、每次都让*匹配最少的。就不会出问题了
     * 2、遇到匹配不够的。找最近的*就行了，找更前面的也没用，。。最近的*就能做到前面的*所有能做到的事情了。
     *
     *
     */

    bool isMatch(string s, string p) {
        return backtracking(s, p, 0, 0);
    }


    bool backtracking(string& s, string& p, int s_idx, int p_idx) {
        if (p_idx == p.length()) {
            if (s_idx == s.length()) {
                return true;
            }
            else {
                return false;
            }
        }
        if (p[p_idx] == '?' || p[p_idx] == s[s_idx]) {
            return backtracking(s, p, s_idx + 1, p_idx + 1);
        }
        else if (p[p_idx] == '*') {
            for (int i = s_idx; i <= s.length(); i++) {
                if (backtracking(s, p, i, p_idx + 1)) {
                    return true;
                }
            }
        }
        return false;
    }
    /*
     * 下面是不会TLE的版本。是根据上面扯犊子半天得到的结果。。就是记录最近出现的*，当回溯到以前的时候。。发现当前的*已经不是最新的了。。就可以滚粗了，不用继续重复做无意义的尝试了。。
     *
     */

    bool isMatch(string s, string p) {
        int last_star = -1;
        return backtracking(s, p, 0, 0, last_star);
    }


    bool backtracking(string& s, string& p, int s_idx, int p_idx, int& last_star) {
        if (p_idx == p.length()) {
            if (s_idx == s.length()) {
                return true;
            }
            else {
                return false;
            }
        }
        if (p[p_idx] == '?' || p[p_idx] == s[s_idx]) {
            return backtracking(s, p, s_idx + 1, p_idx + 1, last_star);
        }
        else if (p[p_idx] == '*') {
            last_star = p_idx;
            for (int i = s_idx; i <= s.length(); i++) {
                if (p_idx < last_star) return false;
                if (backtracking(s, p, i, p_idx + 1, last_star)) {
                    return true;
                }
            }
        }
        return false;
    }
    /*
     * 所以出了个递推的，backtracking + greedy版本
     * 有一些注意的点写在注释里
     */

    bool isMatch(string s, string p) {
        int last_star = -1;
        int last_star_not_match = -1; //最近一个*不匹配的字符。因为我们让*从匹配0个开始
        int s_idx = 0;
        int p_idx = 0;
        int len_s = s.length();
        int len_p = p.length();
        //这里条件是s的结束，而不是p的。。因为p的那边*都是从0个匹配开始，所以很大概率p会提前结束。。但是s没结束
        //所以要让p回到最近的*那边才对，而不是break或者return之类的
        while (s_idx < len_s) {
            //这里加p_idx < len_p就是因为p会提前结束。。所以要加个限制条件才行
            if (p_idx < len_p && p[p_idx] == '?' || p[p_idx] == s[s_idx]) {
                s_idx++;
                p_idx++;
            }
            else if (p_idx < len_p && p[p_idx] == '*') {
                last_star = p_idx;
                last_star_not_match = s_idx;
                p_idx++;
            }
            else {
                //这个就是没碰到任何*的时候。又不匹配了。。就只能炸了。。
                if (last_star == -1) {
                    return false;
                }
                p_idx = last_star + 1;  //这个 + 1的原因是因为，我们需要让p_idx从*的下一步开始，，而不是从*开始。。
                                        //否则无限循环上面的last_star_not_match = s_idx。。。。
                                        //程序就死在这里了。。
                                        //我们是想靠这里下面一行代码把s_idx前进一步的。。
                s_idx = last_star_not_match;
                last_star_not_match++;
            }
        }
        //
        while (p_idx < len_p && p[p_idx] == '*') {
            p_idx++;
        }
        return p_idx == len_p;
    }
};