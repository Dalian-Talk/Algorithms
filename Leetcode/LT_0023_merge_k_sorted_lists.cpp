#include <iostream>
#include <vector>
#include <queue>

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
    /*
     * 这里的基础思路：把所有的List的头拿出来，比较出最小的，然后放到dummy的后面，一个一个接着。
     * 然后当前最小的放进去后，把下一个拿进来。然后继续找最小的。
     *
     * 所以引申到用堆(heap)就是因为，逻辑上是。
     * 一组数 >> 找最小的 >> 找到最小的后 >> 放进下一个数 >> 再找最小的。
     * 即变成了每次往数组中加一个数后，返回最小的那个数。。所以用堆就很方便了。。。
     *
     * 我TM开始看了这个题相关的topic一下子就想到之前做这个题的答案了。。干。。相当于略过了思考流程。。要死要死阿。。。
     *
     *
     * 注意注释中对于nullptr的处理
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
        for (auto l : lists) {
            // 因为有[[]]这种情况，所以会有空的ListNode*，这种就不需要处理了。。因为没有必要。
            // 所以可以在这里去处理掉空的。保存有数的去比较就行
            if (l) {
                pq.push(l);
            }
        }
        ListNode *dummy = new ListNode();
        ListNode *p = dummy;

        while (!pq.empty()) {
            ListNode *cur = pq.top();
            pq.pop();
            /*
             * 这里本来用了 cur && cur->next
             * 来使得cur保证非空才取next。。但是在 [[],[]]多个空的情况下。。往priority queue里放的时候
             * 直接就得比较了。。那么两个空的在cmp中就没有->val这样的成员调用了。也就炸了。。
             * 所以这里加cur 来判断不行。要在进入pq前就得进行处理，也就是上面那个注释的内容了。
             */
            if (cur->next) {
                pq.push(cur->next);
            }
            p->next = cur;
            p = p->next;
        }
        return dummy->next;

    }
private:
    struct cmp {
        bool operator() (const ListNode *node1, const ListNode* node2) {
            return node1->val > node2->val;
        }
    };
};