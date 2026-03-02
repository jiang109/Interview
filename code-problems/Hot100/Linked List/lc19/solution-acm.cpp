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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        //slow->next是要删去的节点
        slow->next = slow->next->next;
        return dummy->next;
    }
};

ListNode* buildList(const vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    for (int x : nums) {
        curr->next = new ListNode(x);
        curr = curr->next;
    }
    return dummy->next;
}

void printList(ListNode* head) {
    if (!head) {
        cout << "[]" << endl;
        return;
    }
    while (head) {
        cout << head->val << (head->next ? " " : "");
        head = head->next;
    }
    cout << endl;
}

int main() {
    int sz, n;
    // 假设输入格式：节点总数 sz，要删除的倒数位置 n，然后是 sz 个节点的值
    while (cin >> sz >> n) {
        vector<int> nums(sz);
        for (int i = 0; i < sz; ++i) cin >> nums[i];

        ListNode* head = buildList(nums);
        Solution sol;
        head = sol.removeNthFromEnd(head, n);

        printList(head);
    return 0;
}