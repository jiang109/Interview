#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                curr->next = list1;
                list1 = list1->next;
            }
            else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }
        curr->next = (list1 != nullptr) ? list1 : list2;
        ListNode* head = dummy->next;
        delete dummy; 
        return head;
    }
};

ListNode* buildList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;
    ListNode* head = new ListNode(nums[0]);
    ListNode* curr = head;
    for (size_t i = 1; i < nums.size(); ++i) {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << (head->next ? " " : "");
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n1, n2;
    // 假设输入：先输入 l1 的长度，再输入 l1 的元素；然后是 l2
    while (cin >> n1) {
        vector<int> v1(n1);
        for (int i = 0; i < n1; ++i) cin >> v1[i];

        cin >> n2;
        vector<int> v2(n2);
        for (int i = 0; i < n2; ++i) cin >> v2[i];

        ListNode* l1 = buildList(v1);
        ListNode* l2 = buildList(v2);

        Solution sol;
        ListNode* result = sol.mergeTwoLists(l1, l2);

        printList(result);
    }
    return 0;
}