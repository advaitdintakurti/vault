
A **Binary Search Tree (BST)** is a binary tree with the following properties:

- Each node contains a key, and all keys in the **left subtree** are smaller.
- All keys in the **right subtree** are greater.
- No duplicate keys (in standard BSTs).

BSTs allow efficient **O(log n)** insertion, search, and deletion, making them ideal for dynamic sorted data storage.

### BST Node Structure

```c
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;
```

### Creating a New Node

```c
#include <stdlib.h>

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}
```

### Insertion in BST

We recursively compare the key with the current node and insert it into the left or right subtree accordingly.

```c
Node* insert(Node* root, int key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}
```

---

### Searching

```c
Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    return (key < root->key) ? search(root->left, key) : search(root->right);
}
```

---

### Finding Minimum and Maximum

- **Minimum:** Leftmost node
- **Maximum:** Rightmost node

```c
Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* findMax(Node* root) {
    while (root && root->right) root = root->right;
    return root;
}
```

---

## **Deleting a Node in BST**

1. **Leaf Node:** Delete it directly.
2. **One Child:** Replace with the child.
3. **Two Children:** Replace with **inorder successor** and delete successor.

```c
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    // search part
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    // deletion part
    else {
        // if no left subtree, replace with right subtree
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // if no right subtree, replace with left subtree
        if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // if both subtrees exist, replace with successor
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
```

---

## Tree Traversals

4. **Inorder (Left, Root, Right)** → Sorted Order
5. **Preorder (Root, Left, Right)**
6. **Postorder (Left, Right, Root)**

```c
#include <stdio.h>

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}
```

---

### Finding Lowest Common Ancestor (LCA)

LCA of two nodes is the deepest node that has both in its subtrees.

```c
Node* LCA(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (n1 < root->key && n2 < root->key) return LCA(root->left, n1, n2);
    if (n1 > root->key && n2 > root->key) return LCA(root->right, n1, n2);
    return root;
}
```

### **Example**

```c
Node* ancestor = LCA(root, 5, 15);  // Returns node with key 10
```

---

### Find Height of BST
```c
int height(Node* root) {
    if (!root) return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
```

---

### Checking if a Tree is a BST

A valid BST must satisfy `min < root < max` at every node.

```c
#include <limits.h>
#include <stdbool.h>

bool isBSTUtil(Node* node, int min, int max) {
    if (node == NULL)
        return true;
    if (node->data <= min || node->data >= max)
        return false;
    return isBSTUtil(node->left, min, node->data) &&
           isBSTUtil(node->right, node->data, max);
}

bool isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}
```

---

### Find the kth smallest element
```c
void kthSmallestUtil(Node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k)
        return;
    kthSmallestUtil(root->left, k, count, result);
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(Node* root, int k) {
    int count = 0, result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}
```

---

### Check if the tree is balanced
```c
int height(Node* node) {
    if (node == NULL)
        return 0;
    int lh = height(node->left);
    int rh = height(node->right);
    return (lh > rh ? lh : rh) + 1;
}

bool isBalanced(Node* root) {
    if (root == NULL)
        return true;
    int lh = height(root->left);
    int rh = height(root->right);
    if (abs(lh - rh) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}
```