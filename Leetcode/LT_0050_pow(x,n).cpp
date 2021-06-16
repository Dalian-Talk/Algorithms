#include <iostream>

using namespace std;

class Solution {
public:
    /*
     * 就是用幂等的规则，加快速度，从O(n)到O(logn)
     * 这是答案的规律。。我自己反正找不到。。23333
     * 但是要处理一些情况
     * x^8:
     * x * x = x^2
     * x^2 * x^2 = x^4
     * x^4 * x^4 = x^8
     *
     * x^6:
     * x * x = x^2
     * 这样子就不能继续 2 + 2 = 4， 4 + 4 = 8 了。
     * 这边就需要让2 + 1 = 3 然后  3 + 3 = 6
     * 也就是碰到奇数更新一次结果 多带一个 x
     *
     *
     *
     * x^9:
     * 1、ans = 1 * x = x
     * 2、 9 / 2 = 4 >> x * x = x^2
     * 3、 4 / 2 = 2 >> x^2 * x^2 = x^4
     * 4、 2 / 2 = 1 >> x^4 * x^4 = x^8 >> x^8 * x = x^9
     *
     *
     * 这种递归的很好理解。。。递推的就没那么好理解了。。很烦。。俩都写一下熟悉以下
     *
     */
    // 先写递归的，好理解多了
    double myPow(double x, int n) {
        long N = n;  // 因为答案用了很傻逼的 -2^31 所以如果 n = -n 就炸了。。
        if (N < 0) {
            // x^-2 = (1/x) ^ 2
            x = 1.0 / x;
            N = -N;
        }
        return dfs(x, N);
    }

    double dfs(double x, long N) {
        if (N == 0) {
            return 1.0;
        }
        double half = dfs(x, N / 2);
        if (N % 2 == 1) {
            return half * half * x;
        }
        else {
            return half * half;
        }
    }


    // 递推的理解不能。。。。但是我背会了！！233333
    double myPow(double x, int n) {
        long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        //记得是double。。。我咋开始写了个int。。。
        double res = 1;
        double cur_mul = x;
        for (long i = N; i; i /= 2) {
            if (i % 2 == 1) {
                res *= cur_mul;
            }
            cur_mul *= cur_mul;
        }
        return res;

    }
};