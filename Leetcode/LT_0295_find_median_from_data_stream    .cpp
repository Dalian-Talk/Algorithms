#include <iostream>
#include <queue>


class MedianFinder {
public:
    /*
     * 经典题目了。因为是datastream。所以不可能每次都find median。
     * 所以用一个大顶堆和一个小顶堆来维护中位数的两边。
     * 这样子就可以用logn的时间拿到中位数了(因为堆的整理需要logn)
     *
     *
     * 或者每次进来一个数就用插入排序一次。这就是O(n)级别了。
     *
     *
     * 捋一下 两个heap的操作。
     * small_half 小的那一边 是个大顶堆
     * big_half 大的那一边 是个小顶堆
     * 1、每次进来一个数先给small_half，整理一遍
     * 2、然后把small_half的top给big_half
     * 3、做12的目的是，每次来一个数，
     *      如果这个数小，那么就是small_half原有的top应该去big那边
     *      如果这个数大，那么整理完这个数就会在top的位置，也应该去big那边
     *      所以12其实就是把small这边重新整理一下，找到最大的那个给到big那边去。之前想着。。为啥要给来给去。。就是漏了这个数很大，要给big这个问题。。
     * 4、然后big那边接收到数之后也会整理堆。
     * 5、这个时候需要看两边的size差距，如果big > small。(这里我们是始终想要small的size >= big的size，反之一样可以的。。)
     * 那么就把big的top，也就是big那边最小的，给到small这边，就ok了。
     *
     * 6、之后就是small.size >= big.size
     * 如果是单数，就是small的顶
     * 如果是偶数，就是两个顶的平均数。
     *
     * 
     */
    MedianFinder() {

    }

    void addNum(int num) {
        small_half.push(num);
        big_half.push(small_half.top());
        small_half.pop();
        if (big_half.size() > small_half.size()) {
            small_half.push(big_half.top());
            big_half.pop();
        }
    }

    double findMedian() {
        if ((small_half.size() + big_half.size()) % 2 == 0) {
            return (small_half.top() + big_half.top()) / 2.0;
        }
        else {
            return small_half.top();
        }
    }
private:
    priority_queue<int> small_half;
    priority_queue<int, vector<int>, greater<>> big_half;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */