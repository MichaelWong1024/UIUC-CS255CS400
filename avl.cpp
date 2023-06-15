#include "cpluspluslabs.h"

Node *new_node(int key) {
  Node *newNode = new Node();
  newNode->key = key;
  newNode->left = newNode->right = nullptr;
  newNode->height = 1;
  return newNode;
}

int height(Node *node) {
  if (node == nullptr) {
    return 0;
  } else {
    return node->height;
  }
}
int max(int a, int b) { return (a > b) ? a : b; }
Node *insertnb(Node *node, int key) {
  if (node == nullptr) {
    return new_node(key);
  }

  if (node->key < key) {
    node->right = insertnb(node->right, key);
  } else {
    node->left = insertnb(node->left, key);
  }

  node->height = 1 + max(height(node->left), height(node->right));
  return node;
}

Node *left_rotate(Node *x) {
  Node *newParent = x->right;
  Node *newRightChild = x->right->left;
  x->right = newRightChild;
  newParent->left = x;

  x->height = 1 + max(height(x->left), height(x->right));
  newParent->height =
      1 + max(height(newParent->left), height(newParent->right));

  return newParent;
}

Node *right_rotate(Node *x) {
  Node *newParent = x->left;
  Node *newLeftChild = x->left->right;
  x->left = newLeftChild;
  newParent->right = x;

  x->height = 1 + max(height(x->left), height(x->right));
  newParent->height =
      1 + max(height(newParent->left), height(newParent->right));

  return newParent;
}

int get_balance(Node *x) {
  if (x == nullptr) {
    return 0;
  }
  return height(x->left) - height(x->right);
}

Node *insert(Node *node, int key) {
  if (node == nullptr) {
    return new_node(key);
  }

  if (node->key < key) {
    node->right = insert(node->right, key);
  } else {
    node->left = insert(node->left, key);
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = get_balance(node);
  if (balance < -1) {
    if (key > node->right->key) {
      node = left_rotate(node);
    } else {
      node->right = right_rotate(node->right);
      node = left_rotate(node);
    }
  } else if (balance > 1) {
    if (key < node->left->key) {
      node = right_rotate(node);
    } else {
      node->left = left_rotate(node->left);
      node = right_rotate(node);
    }
  }
  return node;
}