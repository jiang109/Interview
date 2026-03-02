class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (!head) return nullptr;
		Node* curr = head;
		while (curr) {
			Node* newNode = new Node(curr->val);
			newNode->next = curr->next;
			curr->next = newNode;
			curr = newNode->next;
		}
		curr = head;
		while (curr) {
			if (curr->random) {
				curr->next->random = curr->random->next;
			}
			curr = curr->next->next;
		}
		Node* dummy = new Node(0);
		Node* copyCurr = dummy;
		curr = head;
		while (curr) {
			copyCurr->next = curr->next;
			copyCurr = copyCurr->next;
			curr->next = curr->next->next;
			curr = curr->next;
		}
		Node* ans = dummy->next;
		delete dummy;
		return ans;
	}
};