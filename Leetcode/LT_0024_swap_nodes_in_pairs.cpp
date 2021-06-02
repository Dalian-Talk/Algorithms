#include <iostream>

using namespace std;



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    // 先试试正向换 3个指针搞定
    // []  1   2   3
    // p1  p2  p3

    // []  2   1   3
    // p1  p3  p2
    ListNode* swapPairs(ListNode* head) {
        if (!head) return nullptr;

        ListNode *dummy = new ListNode(0, head);
        ListNode *p1 = dummy, *p2 = p1->next, *p3 = p2->next;
        while (p1 && p2 && p3) {
            p1->next = p3;
            p2->next = p3->next;
            p3->next = p2;

            p1 = p2;
            p3 = p2->next? p2->next->next : nullptr;
            p2 = p2->next;
        }
        p1->next = p2;
        return dummy->next;
    }


    // 再试试从尾巴换
    /* 递归思想就是：
     * 1 2 3 4
     * 当处理到3的时候，只专注于3 和 3->next 也就是4把这俩换一下就行。然后返回4这个指针就ok
     * 那么在处理1的时候，1->next 变为 2->next的时候，就要先等2->next 也就是3做完了才能行。
     * 也就是代码中的 cur->next = dfs1(p->next);
     * 先去处理后面的，处理完回来就是换好了的，然后再换当前的。
     *
     * 然后每次递归的入口是 p->next是因为假如我们有
     * 1 2 3 4 5
     * 我们处理的是 12 34 5
     * 而不是1 23 45
     * 所以在处理3这个点的时候，我们下一次dfs传的是 3->next->next 也就是5。 也就是一次跳俩点。这样就不会出问题啦。
     * (开始想成，倒着来。。到 ->next->next == nullptr， 这种就成1 23 45了就错了。稍微想了一下还是扭回来了。。23333)
     *
     */
    ListNode* swapPairs1(ListNode* head) {
        return dfs1(head);
    }

    ListNode* dfs1(ListNode *cur) {
        if (!cur) return nullptr;
        if (!cur->next) return cur;

        ListNode *p = cur->next;
        cur->next = dfs1(p->next);
        p->next = cur;

        return p;
    }
};