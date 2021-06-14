#include <iostream>
#include <vector>

using namespace std;

/*
 * 两种方法的规律总结在这里
 * 直接一圈圈换
 * 顺时针(clockwise)       (x, y) -> (y, N - 1 - x) -> (N - 1 - x, N - 1 - y) -> (N - 1 - y, x) -> (x, y)
 * 逆时针(anti-clockwise)  (x, y) <- (y, N - 1 - x) <- (N - 1 - x, N - 1 - y) <- (N - 1 - y, x) <- (x, y)
 *
 * 对称方式
 * 顺时针90度
 * 1、反对角线
 * 2、垂直翻转
 *
 * 逆时针90度
 * 1、对角线
 * 2、垂直翻转
 */


class Solution {
public:
    /* 
     * 规律题。。没啥说的。。找到规律就行。
     * size 为 N
     * 第一种直接换的规律。
     * 
     * 顺时针(clockwise)       (x, y) -> (y, N - 1 - x) -> (N - 1 - x, N - 1 - y) -> (N - 1 - y, x) -> (x, y)
     * 逆时针(anti-clockwise)  (x, y) <- (y, N - 1 - x) <- (N - 1 - x, N - 1 - y) <- (N - 1 - y, x) <- (x, y)
     * 执行逻辑，一圈一圈来。总共有 N / 2 圈
     * 每一圈执行次数为。 N  - 2 * 圈数 - 1。(次数是没错。。但是我们要用变量j去控制开始点。。所以用j控制就行)
     * 每一圈执行开始的时候 j = loop 也就是i
     * 最多执行到 (N - 2 - loop) 这里
     * 
     * 0 1 2 3 4 5
     * x x x x x    第0圈，j最多到3, 5 - 2 - 0 = 3 
     * x x x x x    第1圈，j最多到2, 5 - 2 - 1 = 2
     * x x x x x    第2圈，j开始就不用动 5 - 2 - 2 = 1 < 2 
     * x x x x x
     * x x x x x
     *
     */
    void rotate(vector<vector<int>>& matrix) {
        int N = matrix.size();
        int loop =  N / 2;
        for (int i = 0; i < loop; i++) {
            for (int j = i; j <= N - 2 - i; j++) {
                int tmp = matrix[i][j];
                //为了不用每次都记录每个位置的当前值，也就是4次tmp。我们用递归的思想。。记录当前的。。然后用最后一个倒着来。
                matrix[i][j] = matrix[N - 1 - j][i];
                matrix[N - 1 -j][i] = matrix[N - 1 - i][N - 1 - j];
                matrix[N - 1 - i][N - 1 - j] = matrix[j][N - 1 - i];
                matrix[j][N - 1 - i] = tmp;
            }
        }

    }

public:
    /*
     * 第一种的规律给人一种找对称的感觉。。。
     * 虽然我找不到是吧。。但是可以看看答案呀。。
     * 顺时针转90度，可以等效成
     * 1、先集体关于对称轴对称过去
     * 2、再集体关于垂直对称过去(水平翻转)
     * 但是吧。。这个垂直的在程序里不方便弄。。还得写个循环。。
     * 所以换个思路
     * 1、先集体关于反对称轴对称过去              (x, y) <-> (N - 1 - y, N - 1 - x)
     * 2、再集体关于水平对称过去(垂直翻转)         (x, y) <-> (N - 1 - x, y)
     * 水平的在代码里好换的一批
     * 这玩意儿只能记住规律了
     */
    void rotate(vector<vector<int>>& matrix) {
        N = matrix.size();
        symmetry(matrix);
        vertical_flip(matrix);
    }

private:
    int N;
    void symmetry(vector<vector<int>>& matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N - 1 - i; j++) {
                swap(matrix[i][j], matrix[N - 1 - j][N - 1 - i]);
            }
        }
    }

    void vertical_flip(vector<vector<int>>& matrix) {
        for (int i = 0; i < N / 2; i++) {
            swap(matrix[i], matrix[N - 1 - i]);
        }
    }


};