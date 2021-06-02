#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    /*
     * sliding window的思想 >> 分析了半天貌似是two pointer。。。毕竟这个window貌似是固定的来着。。所以还是从two pointers去想吧。。2333
     * 这里的关键是。。words中每一个长度都一样。
     * 所以在对window进行增减的时候都是按照长度一次性增减的。例如words每个都是4
     * 那么window 从0 -> 4 -> 8这么一步一步动的。缩小的时候也是 8 -> 4 -> 0这样子。
     * 
     * 所以这里有个点就是。我们的起点是4次循环，我们要从0 1 2 3， 这4个地方分别开始对window进行处理。。之后的就是重复的window行为了。。
     * 如果不重复4次。。就少了中间的很多情况了。。。
     * 可以理解为sliding window一步一步处理的 弥补。。也算是学到了好吧。。
     * 用多次循环来解决了window不能一步一步动的问题。。方便解题也节省了时间。。诶嘿。。。
     *
     *
     * 还不能用set。。。。他words里面还能重复的。。干。。搞心态啊。。。
     */


    /*
     * 上面是在leetCode上写的过程的一些思考就留下来了。。
     * 设words 长度为 n 每一个长度是 in_len
     * 从brute-force出发。我们是要从s的每一个idx出发。找长度为 n * in_len的字符串，来看是否符合要求
     *
     * 那么如何进行缩减时间复杂度呢？从找的结果出发
     * 从某一个idx弄到了一个长度为 n * in_len的字符串
     * 1、不符合要求
     *      正常就是往下走下一个idx然后再来一遍。相当于是把一个固定大小为 n * in_len的窗口往右移动了一位
     *      那么这里由于每一个字符串长度都是n * in_len。一个技巧就是，我们可以一次移动in_len这么多，反正当前的不符合了，我从in_len后的位置，拿到下一个靠谱的字符串
     *      说不定能减少的我的时间复杂度呢？
     *      那么按照这种思路从某一个idx出发。一次就移动了in_len这么多，如果没找到的话。。。
     *      那么很明显，我们为了这个技巧。。漏掉了移动 1, 2 .... in_len中间的情况，那我们还得补上。
     *      那么从结果来看。。我们还是让这个窗口每一个地方都走了。。没差。。每次都要重新处理。
     *      那么既然窗口的移动次数无法避免(因为每一个n * in_len的字符串都得处理这是必然的)
     *      我们就从减少处理时间、情况上来做。
     *      回到这个不符合要求上来。假设有这么一个字符串，匹配的里面每一个都是长度为2的，总共有3个
     *      a0 a1 a2 a3 a4 a5 a6 a7 a8 a9
     *      我们不用开始直接拿一个长度为6的窗口罩住 a0----a5然后一步一步处理。。因为很有可能，从a0 a1这部分就挂了对吧？？
     *      所以逻辑上就变成这个window不是一个定长的，而是一个最长为6的可伸缩的窗口，伸缩的变化量是 2 的倍数，因为一次找到对的或者错的子串都是 2的基准(根据假设的条件)
     *      (！！！后面想了一下。。窗口一般都固定长度。。这边还是用two pointer思想会更好理解点。。23333)
     *
     *      1) a0 a1符合要求，那么继续看a2 a3
     *      2) a2 a3不符合要求，那么很显然从a0---a3这部分可以舍弃了，不需要从a2开始重新处理了。因为a2,a3是不对的
     *         所以下次就从a4，a5开始了。指针就直接跳过去了。很方便，很省时间
     *
     *      3) 如果a0---a5符合要求呢？？
     *         继续看a6 a7。如果不符合要求。就跟2一样。直接从a8开始就行
     *         如果a6 a7也符合要求呢？？(这里符合要求的意思是指，出现次数符合要求。。而不是指没出现过。。就比如words里面是 aa bb aa，那么aa可以出现两次的。。。)
     *         那么就要从a0开始找到多余的一组跟a6 a7一样的地方，然后截掉，从那个位置开始。比如a2 a3 和 a6 a7一样。那么就走到a4。相当于当前变成了a4, a5, a6, a7开始走了
     *
     *
     *      (写到这里发现。。如果把words中每个都变成长度1的不同的字符串, 就很像 Interview文件夹中的 find_k_XXX这种题目了。。然后我发现，其实也是可以用sliding window思路去做，其实时间复杂度上
     *      是一样的。。。因为当什么都是1的时候。。大家都没差。跑的都一样不是。
     *      复杂度是固定的，只是按照上面这么处理起来，平时时间上肯定更快。
     *      跟find_k_XX这种区别其实也就在于，这边words是有长度的，不是固定的1，不是character而是个string。所以不能每次只走一步。所以也就衍生出了外面多一个循环，再从不同的起点开始走words长度的步数。
     *      这么一想其实逻辑还更舒服点。。233333，开始还是被字符串这种匹配给吓到了。。没有归约成字符。。归约成字符就简单多了。。)
     *      再把leetcode第三题的longest长度改成exact长度。。不能重复改为匹配到某个字符串23333，这个题归约到长度为一的words。。其实就一样。。23333
     *
     *
     */
    vector<int> findSubstring(string s, vector<string>& words) {
        int in_len = words[0].length();
        int out_len = s.length();
        unordered_map<string, int> words_map;
        for (auto word : words) {
            words_map[word]++;
        }

        vector<int> res;
        for (int i = 0; i < in_len; i++) {
            unordered_map<string, int> cur_words_map;
            int left = i;
            int count = 0;
            for (int right = i; right <= out_len - in_len; right += in_len) {
                string cur_sub = s.substr(right, in_len);
                if (words_map[cur_sub]) {
                    if (cur_words_map[cur_sub] == words_map[cur_sub]) {
                        while (left < right) {
                            string tmp = s.substr(left, in_len);
                            left += in_len;
                            cur_words_map[tmp]--;
                            count--;
                            if (tmp == cur_sub) {
                                break;
                            }
                        }
                    }
                    cur_words_map[cur_sub]++;
                    count++;
                    if (count == words.size()) {
                        res.push_back(left);
                    }
                }
                else {
                    cur_words_map.clear();
                    left = right + in_len;
                    count = 0;
                }
            }
        }
        return res;
    }
};