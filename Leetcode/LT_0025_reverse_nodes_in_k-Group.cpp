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

/*
 * 这个题给下面折腾了那么多只是多了一些重新的思考而已。。。
 * 就正常第一次写也写的是对的。。正序处理也没啥。。挺对的。。233333。。注意指针要存几个。。。处理顺序啥的。。别存错了。。
 * 方法2的正序处理，那个把p3 往 p1 p1->next中间塞的这个思路要记住。。还蛮重要的。。开始自己的那种交换指针就给弄错了。呆呀。。23333
 * 方法4那种蠢的不行的代码。。知道就行了。懒得去研究了。。2333还不如submission第一次的
 */


class Solution {
public:
    // 先写个正向的。。
    //其实跟24题那个k =2情况类似，只不过多存点指针。
    /*
     * [dummy] 1 2 3 4 5
     * k = 3
     * 当我们把 1 2 3 变成 3 2 1时，有几种方法
     * 1、两个指针顺序处理(方法2就是这么写的)。逻辑上顺序是:
     *      []  1   2   3   4 5
     *      p1  p2  p3
     *      []  2   1   3   4 5
     *      p1  p3  p2
     *      p1      p2  p3
     *      []  3   2   1   4 5
     *      p1  p3      p2
     *
     *   代码逻辑就是
     *   p1 = &[]
     *   p2 = &1
     *   p3 = &2
     *
     *   a. [] 1 2 3  >> [] 2 1 3
     *      p1->next = p3
     *      p2->next = p3->next
     *      p3->next = p2
     *      ！！！这个逻辑是错误的。。因为用两个指针将整个链表一步一步翻转的过程中。
     *      其中一个指针，这里是p3，一直是用来指向下一个要成为头的节点
     *      另一个指针，这里是p2，一直是用来指当前处理好的尾巴节点。
     *      因为我们多了上一个链表的尾节点，这里是p1。我们就不需要再维护一个当前处理好的部分的头节点了。省了一个指针。
     *
     *      如果按照这里这个逻辑，从 [] 2 1 3 -> [] 3 2 1 的时候。这个2就没了。。p3->next = p2直接把这个2给弄没了。。原因就在于
     *      这个交换逻辑只是给两个指针的互相交换而已。。23333不是多个节点的链表翻转。。。。
     *      (这个错误之前就犯过一次了。。诶西。又忘记了。。干。。。)
     *      所以逻辑应该改为
     *      (下面这个b才是对的！！！)
     *   b. [] 1 2 3  >> [] 2 1 3
     *      每一次找到一个p3，就把p3放到p1后面。因为翻转链表。遇到下一个翻转的节点一定是下一次翻转后的头节点。即。将 p3 塞进 p1 和 p1->next中间
     *      然后把p3->next作为p2->next就成功把p3移动到当前的最前端了。 代码逻辑就是
     *      p2->next = p3->next  // 先把p3的next给了。要不然p3塞过去后这部分就没了
     *      p3->next = p1->next  // 先把p1的next给了，要不然p3进去后这部分就丢了
     *      p1->next = p3        // 到这步为止，成功的把p3塞进去了
     *      p3 = p2->next        // p2->next就是下一次要处理的点了
     *
     * 顺序处理的好处是。。。我们换了k次后。把当前长度为k的链表翻转完后，可以直接p1 = p2这样子就是下一次的开始了，因为p2永远维护的是当前处理链表的尾端
     * 也就是下一个需要处理的链表的头的上一个节点。。即例子中的这个1 是下一次要处理的 4 的上一个节点。
     *
     * 顺序处理的问题在于。我们不能无脑的每次都去换。例如 1 2 3 4 5
     * 当我们换完第一轮后，变成 3 2 1 4 5
     * 此时p1 在1(上一个的尾端), p2 在4(当前尾端), p3 在5(下一个头端)
     * 我们不能把 4 5换过来再发现，诶不对阿。。不能继续换了。。。。那就完了。。
     *
     * 所以
     * 要么在处理之前找一个指针从p1出发，看往下能不能走完k步，能走完，代表有k个节点，不能走完就不处理了。相当于就是找一个指针走到下一个要处理的链表的最终头那里了。
     * 要么就是提前走一遍整个链表。算一下总节点个数，看一下要处理几轮。
     *
     * 方法2是用了走一遍链表，算个数然后算次数的。。两个终止逻辑是类似的。走的次数都一样。。没差。
     *
     *
     * 2、然后看一下倒着来的顺序，也就是用递归翻转部分链表，逻辑上顺序是：
     *      [] 1 2 3 4 5
     *      [] 1 3 2 4 5
     *      [] 3 2 1 4 5
     *   很明显，递归和递推顺序不一样。
     *   在递归上，我们先处理 2 3 的问题。然后返回后 再处理1 3 2的问题。
     *   那么很显然了。第一步 我们从 1 2 3 变成 1 3 2，我们返回什么？？
     *   返回的是这个2，因为下一次我们要把1接在2后面变成 3 2 1。那么很明显了。我们漏了一个3。这个3我们找不到了。
     *   所以在处理中间部分的时候我们需要把这个提前存住。。为的就是之后能重新连过来。。。
     *
     *   代码逻辑上就是(方法1还未改进)
     *   未改进的递归dfs代码中。我们是找不到这个4的，所以在找到3后，提前把4也存下来。
     *   p1 = &[]
     *   p2 = &3  // 提前找到
     *   p3 = &4  // 提前找到
     *   p4 = &1 >> 这个是递归最后返回的，因为递归返回的是当前处理链表部分的最终尾巴。其实也就是 p1->next但是因为后续p1->next也要修改。所以这里存下来也没啥
     *
     *   处理逻辑就是。跑完dfs后，会返回一个指针，这里是p4
     *   p4 = dfs(p1->next, k);  >> 返回的也就是p1->next 只不过是处理好翻转后的尾节点
     *   p1->next = p2  // 上一个的尾节点的next是当前的最终头节点，提前找到了
     *   p4->next = p3  // 当前的尾节点的next是下一个开始处理的节点，提前也找到了
     *   这样子就处理完了当前部分的链表。然后
     *   p1 = p4
     *   就把p1移动到了当前处理完的尾节点，用于下一次的开始。
     *
     *
     *   方法3中把这个递归逻辑做了丰富，可以让代码少点
     *   实际上在我们递归的时候。对于2，我们返回了节点3。 我们需要把 2 3 变成3 2。
     *   那么实际上我们是把 2 3 4变成了 3 2 4。
     *   所以我们可以做 2->next = 3->next来把4这个节点带上。
     *   那么下一次处理 1 3 2 4的时候。
     *   我们在把这个变成 3 2 1 4的同时。就可以做到 1->next = 2->next(也就是4了)
     *   这样子最终返回这个1后。我们已经把4带在了1的后面，也就是说。我们省去了上面的找p3以及p4->next = p3两步，在递归中就完成了。
     *
     *   再方便点可以像submission中的第一次提交的答案那样。在递归判断中，当k == 1的时候，其实我们就已经找到了当前要处理的链表的头节点了，可以在
     *   这里用一个成员变量，或者是参数指针存下来，就不用循环找了。
     *
     *   但是问题在于。如果这里不去像代码中那样循环找，然后提前break的话。就会出现提前换的行为，dfs的终止逻辑也得做改变，因为当最后节点个数不够的时候就有nullptr出现了。
     *
     *   那么要么跟方法2一样，提前算loop。要么把递归的代码逻辑丰富的更多一点。。反正总有一个地方要判断的就是了。。
     *
     *   方法4中是不用循环的递归判断。。。就是把各种判断都扔在了递归里了相当于。。。
     *
     *
     *
     */



    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *p1 = dummy;
        while (true) {
            ListNode *p2 = p1;
            int step = k;
            while (p2 && step) {
                p2 = p2->next;
                step--;
            }
            if (!p2) break;
            ListNode *p3 = p2->next;
            ListNode *p4 = dfs(p1->next, k);

            p1->next = p2;
            p4->next = p3;
            p1 = p4;
        }
        return dummy->next;

    }

    ListNode* dfs(ListNode* node, int k) {
        if (k == 1) {
            return node;
        }
        else {
            ListNode *p = dfs(node->next, k - 1);
            p->next = node;
            return node;
        }
    }



    ListNode* reverseKGroup1(ListNode* head, int k) {
        if(!head || k == 1) return head;
        int len = 0;
        ListNode *pre_tail  = head;
        while(pre_tail){
            len++;
            pre_tail = pre_tail->next;
        }
        int loops = len / k;
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        pre_tail = dummy;
        ListNode *cur_tail, *next_head;
        while(loops--){
            cur_tail = pre_tail->next;
            next_head = cur_tail->next;
            for(int i = 1; i < k; i++){
                cur_tail->next = next_head->next;
                next_head->next = pre_tail->next;
                pre_tail->next = next_head;
                next_head = cur_tail->next;
            }
            pre_tail = cur_tail;
        }
        return dummy->next;
    }


    ListNode* reverseKGroup2(ListNode* head, int k) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *p1 = dummy;
        while (true) {
            ListNode *p2 = p1;
            int step = k;
            while (p2 && step) {
                p2 = p2->next;
                step--;
            }
            if (!p2) break;
            ListNode *p4 = dfs2(p1->next, k);
            p1->next = p2;
            p1 = p4;
        }
        return dummy->next;

    }

    ListNode* dfs2(ListNode* node, int k) {
        if (k == 1) {
            return node;
        }
        else {
            ListNode *p = dfs2(node->next, k - 1);
            node->next = p->next;
            p->next = node;
            return node;
        }
    }

    /*
     * 方法4。。。把各种while循环去掉了。。单纯在递归里面去写。。。怎么说呢。。代码也挺丑的。。而且还难懂的一批。。
     * 所以最简单的还是。提前跑一遍的正向方法2
     * 或者是中间加一个while循环的方法1、3都行。。
     * 或者是。。方法4配一个提前跑一遍算个数的也行。。submission中的第一次提交就是这样。。省去了很多没必要的终止条件判断。。也不至于这么丑 23333。
     */

    ListNode* reverseKGroup3(ListNode* head, int k) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *p1 = dummy;
        while (true) {
            ListNode *p2 = dfs3(p1->next, k);
            if (!next_head) {
                break;
            }
            p1->next = next_head;
            p1 = p2;
        }
        return dummy->next;

    }
    ListNode* next_head;
    ListNode* dfs3(ListNode* node, int k) {
        if (!node) {
            next_head = nullptr;
            return next_head;
        }
        if (k == 1) {
            next_head = node;
            return next_head;
        }
        else {
            ListNode *p = dfs3(node->next, k - 1);
            if (p) {
                node->next = p->next;
                p->next = node;
                return node;
            }
            else {
                // 如果返回的就是nullptr就意味着，这边节点不够了。。那么这边都不能做任何处理了。。返回的都是nullptr，告诉之前的节点啥都不用做。。
                // 如果不写这个else。。除了最后一个节点知道。。其他节点返回的还是正常的node。。就翻转了。。就出问题了。。
                return nullptr;
            }

        }
    }
};
