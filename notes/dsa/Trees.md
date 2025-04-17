A tree is a hierarchical data structure consisting of nodes. Each node stores a value and may have links to child nodes. The topmost node is called the root, and nodes without children are called leaves.

**Structure for a General Tree Node**:

```c
#include <stdio.h>
#include <stdlib.h>

// General tree node structure
struct Node {
    int data;
    struct Node** children; // Array of child pointers for general trees
    int child_count;       // Number of children
};

// Function to create a tree node
struct Node* create_node(int value, int max_children) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->child_count = 0;
    node->children = (struct Node**)malloc(max_children * sizeof(struct Node*));
    return node;
}
```

**Basic Operations on General Trees**:

#### Insertion

Insertion involves dynamically allocating memory for a new node and attaching it to its parent. General trees allow each node to have a variable number of children, managed through dynamic arrays or linked lists.

```c
void add_child(struct Node* parent, struct Node* child) {
    parent->children[parent->child_count++] = child;
}
```

#### Traversal

Traversal algorithms navigate the tree structure to visit all nodes in a specific order. Common traversal methods include:

**Inorder Traversal (Left-Root-Right)**

```c
void inOrder(struct Node* root) {
    if (root == NULL) return;
    inOrder(root->left);      // Left subtree
    printf("%d ", root->data); // Root
    inOrder(root->right);     // Right subtree
}
```

**Preorder Traversal (Root-Left-Right)**:

```c
void preOrder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data); // Root
    preOrder(root->left);      // Left subtree
    preOrder(root->right);     // Right subtree
}
```

**Postorder Traversal (Left-Right-Root)**:

```c
void postOrder(struct Node* root) {
    if (root == NULL) return;
    postOrder(root->left);     // Left subtree
    postOrder(root->right);    // Right subtree
    printf("%d ", root->data); // Root
}
```

#### Deletion

Deletion involves recursively freeing memory for a node and all its descendants.

```c
void delete_tree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < root->child_count; i++) {
        delete_tree(root->children[i]);
    }
    free(root->children);
    free(root);
}
```

### Find LCA (Binary Tree)
```c
Node* lcaBT(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (root->data == n1 || root->data == n2) return root;
    Node* left = lcaBT(root->left, n1, n2);
    Node* right = lcaBT(root->right, n1, n2);
    if (left && right)
        return root;
    return (left) ? left : right;
}
```

#### Binary Search Trees (BST) and Their Implementation

A binary search tree (BST) is a binary tree with an additional constraint: the left subtree of any node contains values less than the node’s value, and the right subtree contains values greater than the node’s value. This property enables efficient searching, insertion, and deletion operations.

**Structure for a BST Node**:

```c
#include <stdio.h>
#include <stdlib.h>

// BST node structure
struct Node {
    int data;
    struct Node* p; // pointer to parent, used when needed
    struct Node* left;
    struct Node* right;
};

// Function to create a new BST node
struct Node* create_bst_node(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->p = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}
```

### Operations on Binary Search Trees

#### Insertion

Inserting a new node into a BST requires maintaining the BST property. Recursive functions are commonly used to traverse the tree and find the correct location for the new node.

```c
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return create_bst_node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}
```

#### Search

Searching for a node involves traversing the tree and comparing each node’s value with the target.

```c
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}
```

#### Find Minimum and Maximum

These operations locate the smallest or largest value in the BST, respectively.

**Find Minimum**:

```c
struct Node* find_min(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
```

**Find Maximum**:

```c
struct Node* find_max(struct Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}
```

#### Deletion

Deleting a node from a BST involves three cases:
- The node has no children: Simply remove the node.
- The node has one child: Replace the node with its child.
- The node has two children: Replace the node with its inorder successor (the smallest node in its right subtree).

```c
struct Node* delete(struct Node* root, int key) {
    // nothing to delete
    if (root == NULL) return root;

    // search for node
    if (key < root->data) {
        root->left = delete(root->left, key);
    } else if (key > root->data) {
        root->right = delete(root->right, key);
    // found the node
    } else {
        // if no left subtree, replace with right subtree
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        // if no right subtree, replace with left subtree
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // if both subtrees exist, replace with successor
        struct Node* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
```

#### Traversal

Traversal methods include:

**Inorder Traversal (Left-Root-Right)**:

This traversal visits nodes in sorted order for a BST.

```c
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
```

**Preorder Traversal (Root-Left-Right)**:

```c
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
```

**Postorder Traversal (Left-Right-Root)**:

```c
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
```

**Example Usage**:

```c
int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);

    root = delete(root, 50);
    printf("\nInorder traversal after deletion: ");
    inorder(root);

    return 0;
}
```

## Specialized Trees

[[Binary Search Trees (BST)]]
[[Fenwick Trees]]
[[AVL Trees]]