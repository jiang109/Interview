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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0); // 哑节点简化操作
        ListNode* curr = dummy;
        int carry = 0; // 进位

        // 只要 l1, l2 没走完，或者还有进位没处理完，就继续
        while (l1 || l2 || carry) {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;

            int sum = val1 + val2 + carry;
            carry = sum / 10;          // 计算新的进位
            curr->next = new ListNode(sum % 10); // 创建当前位结果

            curr = curr->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};

ListNode* buildList(const vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
   //注意哑节点
    ListNode* curr = dummy;
    for (int x : nums) {
        curr->next = new ListNode(x);
        curr = curr->next;
    }
    return dummy->next;
}

void printList(ListNode* head) {
    if (!head) cout << "[]";
    while (head) {
        cout << head->val << (head->next ? " " : "");
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n1, n2;
    while (cin >> n1) {
        vector<int> v1(n1);
        for (int i = 0; i < n1; ++i) cin >> v1[i];

        cin >> n2;
        vector<int> v2(n2);
        for (int i = 0; i < n2; ++i) cin >> v2[i];

        ListNode* l1 = buildList(v1);
        ListNode* l2 = buildList(v2);

        Solution sol;
        ListNode* result = sol.addTwoNumbers(l1, l2);

        printList(result);
    }
    return 0;
}