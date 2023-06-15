#ifndef BST_H
#define BST_H

class BST {
public:
  int data;
  BST *left, *right;

  BST() {
    data = 0;
    left = right = nullptr;
  }
  BST(int data) {
    this->data = data;
    left = right = nullptr;
  }

  void insert(int data) {
    if (this->data < data) {
			if (this->right == nullptr) { this->right = new BST(data); }
			else { this->right->insert(data); }
    }
		else {
			if (this->left == nullptr) { this->left = new BST(data); }
      else { this->left->insert(data); }
    }
  }

  int nth_node(int n) {
		int result = 0;
		nth_node_helper(this, &n, &result);
		return result;
	}
	void nth_node_helper(BST *curr, int *n, int *result) {
		if (curr == nullptr) { return; }
		nth_node_helper(curr->left, n, result);
		if (--(*n) == 0) { *result = curr->data; return; }
		nth_node_helper(curr->right, n, result);
	}
};

#endif // BST_H