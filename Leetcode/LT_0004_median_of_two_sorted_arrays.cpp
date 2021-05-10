#include <iostream>
#include <vector>

using namespace std;

/* 记录一下自己头铁的思路。
 * 核心思想就是两个数组都从小开始找，找到需求到的中位数位置所需要的左半部分的那些数，然后根据当前位置，来判断具体应该选哪些数来计算最后的中位数。
 * 当找到足够的左半部分的数的时候，有以下几种情况。A的index是i，B的index是j。这里我们通过处理，让A的长度<=B的长度。因为反过来的结论是一样的，
 * 没有必要再为了另一半情况去单独进行更多冗余的处理。
 * 逻辑上，找到一个左半部分的数，i或者j往右移动一格。
 * 如果长度不同(因为长度相同一定是偶数),
 * 总长度为奇数，即中位数是某个数：
 *    0  1  2  3  4  5  6
 * A a0 a1 a2
 * B b0 b1 b2 b3 b4 b5
 * A
 *
 * 1) i = 0，j = 4， 那么{b0, b1, b2, b3} 都是比{a0, b4}小的，那么中位数就是{a0, b4}中小的那个了。
 * 2) i = 1(或者i = 2), 即i在中间的情况，j = 3。 那么{a0, b0, b1, b2}都是比{a1, b3}小的，那么中位数就是{a1, b3}中小的那个。
 * 3) i = 3, j = 1, 即整个A都用完了，这种情况，就很明显是{b1}就是中位数了。
 * 4) A是空的，也即是i = 0。这个类似i = 3， A用完了。
 * 综上，这种情况下，
 * 如果 i == A.size()，那么选j位置的数为中位数。
 * 如果 i != A.size()，那么选i,j位置上小的那个数作为中位数。
 *
 * 总长度为偶数:
 *    0  1  2  3  4  5  6
 * A a0 a1 a2 a3
 * B b0 b1 b2 b3 b4 b5
 * A
 *
 * 1) i = 0, j = 5, 那么{b0, b1, b2, b3, b4} 都是比{a0, b5}小的。这个时候，b4肯定是中位数的一部分，因为偶数长度下，一半的个数后最后那个数
 * 肯定是中位数的一部分。这个时候需要选择{a0, b5}中小的那个作为另一部分
 * 2) i = 1(或者i = 2, 3), j = 4那么{a0, b0, b1, b2, b3}都是比{a1, b4}小的。这样子情况中位数中小的那一部分就出在{a0,b3}中大的那个， 大的那一部分就出在{a1, b4}中小的那个。
 * 3) i = 4, j = 1，即整个A都用完了。这个情况与2)一样，{a3, b0}选大的, {a4(不存在), b1}选小的。
 * 4) A是空的，即i = 0, j = 3, 这种则是选{B[j - 1], B[j]}作为中位数， 跟1)的联系是
 * B[j - 1]依旧是一定存在的，但是B[j]需要选{a0(不存在), B[j]}中小的那个。
 * 综上，这类情况下，
 * i == 0 && i != A.size(), 选 {B[j - 1], min(A[i], B[j])}
 * i != 0 && i != A.size(), 选 {max(A[i - 1], B[j - 1]), min(A[i], B[j])}
 * i == 0 && i == A.size(), 选 {B[j - 1], B[j]}，此时A[i]不存在
 * i != 0 && i == A.size(), 选 {A[i - 1], B[j]}，此时A[i]不存在
 * 先不急着合并情况， 把长度相同一并考虑进去后再说
 * 长度相同的情况，长度相同不存在两个都为空的情况(题目已知两个数组至少有一个数)。
 *    0  1  2  3  4
 * A a0 a1 a2 a3
 * B b0 b1 b2 b3
 * A
 *
 * A不为空
 * 1) i = 0, j = 4, 选{B[j - 1], A[i]}
 * 2) i = 1(或者 2,3), j = 3, 选{max(A[i - 1], B[j - 1]), min(A[i], B[j])}
 * 3) i = 4, j = 0, 选{A[i - 1], B[j]} B[j - 1]不存在
 * A为空
 * 1) i = 0, j = 2, 选{B[j - 1], B[j]}
 *
 * 综上，这类情况下
 * i == 0 && i != A.size()，{B[j - 1], A[i]} 此时 B[j]不存在
 * i != 0 && i != A.size()，{max(A[i - 1], B[j - 1]), min(A[i], B[j])}
 * i == 0 && i == A.size(), {B[j - 1], B[j]}，此时A[i]不存在
 * i != 0 && i == A.size(), {A[i - 1], B[j]}，此时A[i]不存在
 *
 * 所以综合偶数的所有情况
 * i == 0 && i != A.size(), {B[j - 1], min(A[i], B[j] 或者 INT_MAX)}
 * i != 0 && i != A.size(), {max(A[i - 1], B[j - 1]), min(A[i], B[j])}
 * i == 0 && i == A.size(), {B[j - 1], min(A[i] 或者 INT_MAX, B[j])}
 * i != 0 && i == A.size(), {A[i - 1], B[j]}
 *
 * 再归类一下就是
 * i == 0, {B[j - 1], min(A[i] 或者 INT_MAX, B[j] 或者 INT_MAX)}
 * i != 0, {max(A[i - 1], B[j - 1] 或者 INT_MIN), min(A[i] 或者 INT_MAX, B[j])}
 */


/* 这里记录另一个类似Sliding window的做法，用的binary search
 * 即，直接用A B的size找到所需要的左半部分的数的个数，然后通过边界的比较来移动这个window，最终让i j框起来的这个window符合要求。
 * 最终目的与头铁的思路是一样的，找到这么一组i j， 然后让所有比 i j小的数都比他俩小。
 * 只不过自己的方法是linear的比较慢，从0开始一个一个加
 * 这个可以用binary search，速度提高到了log级别。通过i来对j进行控制，直接判断window边界是否符合要求即可。
 *
 *    0  1  2  3  4  5  6
 * A a0 a1 a2
 * B b0 b1 b2 b3 b4 b5
 *
 * 这个方法暂时不管奇偶。定 left = 0, right = A.size()。
 * 找到A的中点 i = (left + right) / 2
 * 找到B的中点 j = half - i
 * 这里注意，与linear的区别，
 * linear中 half 取的是 (A + B) / 2是因为我们要找到这么多个在左边的，这个没问题。
 * log中我们需要把half 多加1 变成 (A + B + 1) / 2。这是因为我们要找的这个j是j左边的部分参与构成median左边的部分，j本身是在右边的
 * 这部分的index变化与第一个方法差别较大。
 * 第一个方法分了奇偶，
 * 奇数的时候B[j]如果比A[i]小，那么B[j]就是在左边的部分，即B[j]是中位数， 如果B[j]比A[i]大，那么A[i]是中位数, B[j]是右边的部分。
 * 偶数的时候A[i], B[j]都是右边的部分。A[i - 1], B[j - 1]中大的那个是左边的中位数部分。
 *
 * 第二个方法，也就是现在写的这个对第一个方法的情况做了整个的合并。比较巧妙的！！！
 * 不分奇偶了，我就专注的找到足够的左半部分(包括奇数下的中位数)，这样子，左半部分中最大的那个，肯定就是中位数或者是中位数的左半部分。
 * 这种判断方法就把第一种方法下的，奇数下取小的但偶数下取大的给合并了，因为奇数下的中位数也被归到了左半部分了。
 *
 * 所以为了做到第二个方法中的这种合并措施。half就需要取(A + B + 1) / 2这样子才能让奇数下的左半部分包括了中位数。
 * 然后开始找A到底提供了多少个数字在左半部分的操作，这个部分A一样是短于B的，为了处理上的方便，因为短的有可能会用完。(当两个长度相同时B也有可能用完的)
 *
 * 对这个例子，half = (3 + 6 + 1) / 2 = 5
 * i = 1
 * j = 4
 * 这样子我们就找到了左边的5个数{a0, b0, b1, b2, b3}。然后这个时候开始判断这5个数是不是我们想要的5个数。
 * 判断逻辑就是看当前的i j能否成为比这5个数都大的数。这个时候我们有
 * A[i - 1] | A[i]
 * B[j - 1] | B[j]
 * 1)如果 A[i - 1] < B[j] && B[j - 1] < A[i] 那么我们就找到了这样的 i j，所以判断逻辑上是
 *
 * 2)如果 A[i] < B[j - 1]，那么证明我们找到的这个i太小了，要换一个大的数来且当前这个A[i]肯定就在左半部分了，那么 left = i + 1
 * 3)如果 A[i - 1] > B[j]，那么证明我们找到的这个i太大了，要换一个小的数来且当前这个A[i]肯定就在右半部分了，那么 right = i - 1
 *
 * Binary search的逻辑就在于找到最终满足1)的这么一组点，所以我们专注在2,3的变化上。
 * 对于2
 * 这个判断中i是需要关注的，因为j - 1是一定存在的，由于 j是用 half - i 得到的，极限情况，即使i取0，j也只是等于B.size(), j - 1依旧存在。
 * 那么这里如果 i != A.size()， 即i < A.size()，那么就可以直接比较了。这里很巧的是，如果A是空的，那么A.size()也就是0了。i < A.size()
 * 一样无法满足。就很巧。。。
 * 对于3
 * 我们需要保证A[i - 1] 和 B[j]存在。 然后这里由于j是由 half - i 得来的。那么即使极限情况i取A.size(), j也是0，依旧存在。所以控制i - 1存在即可。
 * 也即是 i > 0。就很巧。。
 * 这个方法巧就巧在，j是由i控制的，所以我们关注点放在i就行了。
 *
 * 当这两个条件都不满足也即不满足2) 和 3)。那么我们就通过了1)
 * 进了1后
 * 我们需要找到左边最大的那个也即是 {A[i - 1], B[j - 1]} 中大的那个。 那么需要对i j做0的判断
 * 如果是偶数
 * 我们需要在{A[i], B[j]}中找到小的那个，那么需要对i j做 size的判断
 */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int i = 0, j = 0, cur = 0;
        int l1 = nums1.size();
        int l2 = nums2.size();
        int half = (l1 + l2) / 2;
        bool is_odd = (l1 + l2) % 2;


        while (true) {
            if (cur < half) {
                if (i < l1 && nums1[i] <= nums2[j]) {
                    i++;
                }
                else if (i == l1 || j < l2 && nums2[j] < nums1[i]) {
                    j++;
                }
                cur++;
            }
            else {
                if (is_odd) {
                    if (i == l1) {
                        return nums2[j];
                    }
                    else {
                        return min(nums1[i], nums2[j]);
                    }
                }
                else {
                    int left, right;
                    if (i == 0) {
                        left = nums2[j - 1];
                        right = min(i == l1? INT_MAX : nums1[i], j == l2? INT_MAX : nums2[j]);
                    }
                    else {
                        left = max(nums1[i - 1], j == 0 ? INT_MIN : nums2[j - 1]);
                        right = min(i == l1? INT_MAX : nums1[i], nums2[j]);
                    }
                    return (left + right) / 2.0;
                }
            }
        }
    }

    double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }
        int l1 = nums1.size();
        int l2 = nums2.size();
        int half = (l1 + l2 + 1) / 2; // +1很关键
        bool is_odd = (l1 + l2) % 2;

        int left = 0, right = nums1.size();
        int i, j;
        while (left <= right) {
            i = (left + right) / 2;
            j = half - i;
            if (i < l1 && nums1[i] < nums2[j - 1]) {
                left = i + 1;
            }
            else if (i > 0 && nums2[j] < nums1[i - 1]) {
                right = i - 1;
            }
            else {
                int max_left = max(i == 0? INT_MIN : nums1[i - 1], j == 0? INT_MIN : nums2[j - 1]);
                if (is_odd) return max_left;
                int min_right = min(i == l1? INT_MAX : nums1[i], j == l2? INT_MAX : nums2[j]);
                return (max_left + min_right) / 2.0;
            }
        }
        return 0;
    }
};