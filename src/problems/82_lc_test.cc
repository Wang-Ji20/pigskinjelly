#include "lc_common.hh"

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        return deleteDuplicates_rec(head).first;
    }
private:
    pair<ListNode*, int>
    deleteDuplicates_rec(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return make_pair(head, 200);
        }
        auto [next, repeated_val] = deleteDuplicates_rec(head->next);
        if (next == nullptr) {
            head->next = nullptr;
            return make_pair(head, repeated_val);
        }
        if (next->val == head->val) {
            repeated_val = next->val;
        }
        if (next->val == repeated_val) {
            next = next->next;
        }
        head->next = next;
        if (head->val == repeated_val) {
            head = next;
        }
        return make_pair(head, repeated_val);
    }
};
