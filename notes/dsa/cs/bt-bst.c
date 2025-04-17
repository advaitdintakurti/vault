#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *p;
    struct Node *left;
    struct Node *right;
} Node;

// Creates a new node with the given key
// Complexity: O(1)
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

/*
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->p = NULL;
    return node;
}
*/

// Inserts a key into the BST
// Average Complexity: O(log n), Worst-case: O(n)
Node* insert(Node* root, int key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

/*
Node* insert(Node* root, int key) {
    Node **cur = &root, *parent = NULL;
    while (*cur) {
        parent = *cur;
        if (key < (*cur)->key)
            cur = &((*cur)->left);
        else if (key > (*cur)->key)
            cur = &((*cur)->right);
        else
            return root;
    }
    *cur = newNode(key);
    (*cur)->p = parent;
    return root;
}
*/

// Insert a node into binary tree (Level Order)
// Complexity: O(n)
Node* insertLevelOrder(Node* root, int key) {
    Node* new_node = newNode(key);
    if (!root)
        return new_node;

    int total = countNodes(root);
    Node** queue = malloc(total * sizeof(Node*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        if (!current->left) {
            current->left = new_node;
            free(queue);
            return root;
        } else {
            queue[rear++] = current->left;
        }
        if (!current->right) {
            current->right = new_node;
            free(queue);
            return root;
        } else {
            queue[rear++] = current->right;
        }
    }
    free(queue);
    return root;
}

// Delete from a binary tree (Level Order)
// Complexity: O(n)
Node* deleteNodeLevelOrder(Node* root, int key) {
    if (!root) return root;
    if (!root->left && !root->right) {
        if (root->key == key) {
            free(root);
            return NULL;
        }
        return root;
    }
    int total = countNodes(root);
    Node** queue = malloc(total * sizeof(Node*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    Node* key_node = NULL;
    while (front < rear) {
        Node* current = queue[front++];
        if (current->key == key)
            key_node = current;
        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }

    if (key_node) {
        Node* last_node = queue[--rear];
        key_node->key = last_node->key;
        free(last_node);
    }
    free(queue);
    return root;
}

// Searches for a key in the BST
// Average Complexity: O(log n), Worst-case: O(n)
Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    return (key < root->key) ? search(root->left, key) : search(root->right, key);
}

// Finds the minimum node in the BST (leftmost node)
// Complexity: O(h)
Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

// Finds the maximum node in the BST (rightmost node)
// Complexity: O(h)
Node* findMax(Node* root) {
    while (root && root->right) root = root->right;
    return root;
}

// Deletes a node with the given key from the BST
// Average Complexity: O(log n), Worst-case: O(n)
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

/*
Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        Node* tmp = root->left ? root->left : root->right;
        if (tmp) tmp->p = root->p;
        if (!root->left || !root->right) {
            free(root);
            return tmp;
        }
        Node* minRight = findMin(root->right);
        root->key = minRight->key;
        root->right = deleteNode(root->right, minRight->key);
    }
    return root;
}
*/

// Find Size of Binary Tree
// Complexity: O(n)
int size(Node* root) {
    if (!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

// Traverses the BST in inorder
// Complexity: O(n)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// Traverses the BST in preorder
// Complexity: O(n)
void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

// Traverses the BST in postorder
// Complexity: O(n)
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

// BST to Inorder Array
// Complexity: O(n)
void inorderToArray(Node* root, int* arr, int* index) {
    if (!root) return;
    inorderToArray(root->left, arr, index);
    arr[(*index)++] = root->key;
    inorderToArray(root->right, arr, index);
}

// Counts the total number of nodes in the tree
// Complexity: O(n)
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Counts the number of leaves in the tree
// Complexity: O(n)
int countLeaves(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Count the number of nodes in a complete binary tree
// Complexity: O(h)
int countCompleteNodes(Node* root) {
    int lh = 0, rh = 0;
    Node* current = root;
    while (current) {
        lh++;
        current = current->left;
    }
    current = root;
    while (current) {
        rh++;
        current = current->right;
    }
    return lh == rh ? (1 << lh) - 1 : 1 + countCompleteNodes(root->left) + countCompleteNodes(root->right);
}

// Finds the lowest common ancestor of two nodes in the BST
// Complexity: O(h)
Node* LCA(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (n1 < root->key && n2 < root->key) return LCA(root->left, n1, n2);
    if (n1 > root->key && n2 > root->key) return LCA(root->right, n1, n2);
    return root;
}

// Finds the lowest common ancestor of two nodes in a binary tree
// Complexity: O(n)
Node* lcaBT(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (root->key == n1 || root->key == n2) return root;
    Node* left = lcaBT(root->left, n1, n2);
    Node* right = lcaBT(root->right, n1, n2);
    if (left && right)
        return root;
    return (left) ? left : right;
}

// Finds the height of the binary tree
// Complexity: O(n)
int height(Node* root) {
    if (!root) return -1;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

// Find minimum depth of the binary tree
// Complexity: O(n)
int minDepth(Node* root) {
    if (!root) return 0;
    if (!root->left) return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    int l = minDepth(root->left);
    int r = minDepth(root->right);
    return 1 + (l < r ? l : r);
}

// Verify if the given binary tree is a BST (Check Validity of BST)
// Complexity: O(n)
int isBST(Node* root, int min, int max) {
    if (!root) return 1;
    if (root->key < min || root->key > max) return 0;
    return isBST(root->left, min, root->key - 1) && isBST(root->right, root->key + 1, max);
}

// Checks if the binary tree is a BST using inorder traversal
// Complexity: O(n)
int isBSTInorderHelper(Node* root, Node** prev) {
    if (!root)
        return 1;
    if (!isBSTInorderHelper(root->left, prev))
        return 0;
    if (*prev && root->key <= (*prev)->key)
        return 0;
    *prev = root;
    return isBSTInorderHelper(root->right, prev);
}

int isBSTInorder(Node* root) {
    Node* prev = NULL;
    return isBSTInorderHelper(root, &prev);
}

// Find the kth smallest element in the BST
// Complexity: O(h)
int count(Node* root) {
    return root ? 1 + count(root->left) + count(root->right) : 0;
}

int kthSmallest(Node* root, int k) {
    int left_size = count(root->left); 
    return k == left_size + 1 ? root->key : 
           k <= left_size ? kthSmallest(root->left, k) : 
                            kthSmallest(root->right, k - left_size - 1);
}

Node* kthSmallestNode(Node* root, int k) {
    int left_size = count(root->left);
    return k == left_size + 1 ? root : 
           k <= left_size ? kthSmallestNode(root->left, k) : 
                            kthSmallestNode(root->right, k - left_size - 1);
}

// Find the kth largest element in the BST
// Complexity: O(h)
int kthLargest(Node* root, int k) {
    int right_size = count(root->right);
    return k == right_size + 1 ? root->key : 
           k <= right_size ? kthLargest(root->right, k) : 
                            kthLargest(root->left, k - right_size - 1);
}

Node* kthLargestNode(Node* root, int k) {
    int right_size = count(root->right);
    return k == right_size + 1 ? root : 
           k <= right_size ? kthLargestNode(root->right, k) : 
                            kthLargestNode(root->left, k - right_size - 1);
}

// Check if the given binary tree is balanced
// Complexity: O(n)
int checkBalance(Node* root) {
    if (!root) return 0;
    int lh = checkBalance(root->left);
    if (lh == -1) return -1;
    int rh = checkBalance(root->right);
    if (rh == -1 || abs(lh - rh) > 1) return -1;
    return 1 + (lh > rh ? lh : rh);
}

int isBalanced(Node* root) {
    return checkBalance(root) != -1;
}


// Helper for checking if the tree is complete
// Complexity: O(n)
int isCompleteUtil(Node* root, int index, int number_nodes) {
    if (!root)
        return 1;
    if (index >= number_nodes)
        return 0;
    return isCompleteUtil(root->left, 2 * index + 1, number_nodes) &&
           isCompleteUtil(root->right, 2 * index + 2, number_nodes);
}

// Verifies if the binary tree is complete
// Complexity: O(n)
int isComplete(Node* root) {
    int node_count = countNodes(root);
    return isCompleteUtil(root, 0, node_count);
}

// Find the inorder successor of a node in the BST
// Complexity: O(h)
Node* inorderSuccessor(Node* root, Node* node) {
    if (!node) return NULL;
    if (node->right) {
        Node* current = node->right;
        while (current && current->left)
            current = current->left;
        return current;
    }
    Node* succ = NULL;
    while (root) {
        if (node->key < root->key) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}

// Find the inorder predecessor of a node in the BST
// Complexity: O(h)
Node* inorderPredecessor(Node* root, Node* node) {
    if (!node) return NULL;
    if (node->left) {
        Node* current = node->left;
        while (current && current->right)
            current = current->right;
        return current;
    }
    Node* pred = NULL;
    while (root) {
        if (node->key > root->key) {
            pred = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}


// Find the diameter of a binary tree
// Complexity: O(n)
int findDiameter(struct Node* root, int* diameter) {
    if (!root)
        return 0;
    
    int ld = findDiameter(root->left, diameter);
    int rd = findDiameter(root->right, diameter);
    
    *diameter = (*diameter > ld + rd) ? *diameter : ld + rd;
    return 1 + (ld > rd ? ld : rd);
}

// Prints the BST nodes in level order (Breadth First Search)
// Complexity: O(n)
void levelOrder(Node* root) {
    if (!root) return;
    Node** queue = malloc(countNodes(root) * sizeof(Node*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* curr = queue[front++];
        printf("%d ", curr->key);
        if (curr->left) queue[rear++] = curr->left;
        if (curr->right) queue[rear++] = curr->right;
    }
    free(queue);
}


// Level Order Traversal into an Array
// Complexity: O(n)
int** levelOrderArray(Node* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int total = countNodes(root);
    Node** q = malloc(total * sizeof(Node*));
    int front = 0, rear = 0;
    q[rear++] = root;
    
    int **res = malloc(total * sizeof(int*));
    int *cols = malloc(total * sizeof(int));
    int levels = 0;
    
    while (front < rear) {
        int count = rear - front;
        int *levelArr = malloc(count * sizeof(int));
        for (int i = 0; i < count; i++) {
            Node* cur = q[front++];
            levelArr[i] = cur->key;
            if (cur->left)  q[rear++] = cur->left;
            if (cur->right) q[rear++] = cur->right;
        }
        res[levels] = levelArr;
        cols[levels++] = count;
    }
    
    free(q);
    *returnSize = levels;
    *returnColumnSizes = cols;
    return res;
}

// Level Order Traversal into an Array (from Bottom)
// Complexity: O(n)
int** levelOrderBottom(Node* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int total = countNodes(root), front = 0, rear = 0, lvl = 0;
    Node** q = malloc(total * sizeof(Node*));
    q[rear++] = root;
    int **res = malloc(total * sizeof(int*));
    int *cols = malloc(total * sizeof(int));
    while (front < rear) {
        int cnt = rear - front;
        int *arr = malloc(cnt * sizeof(int));
        for (int i = 0; i < cnt; i++) {
            Node *n = q[front++];
            arr[i] = n->key;
            if (n->left)  q[rear++] = n->left;
            if (n->right) q[rear++] = n->right;
        }
        res[lvl] = arr;
        cols[lvl++] = cnt;
    }
    free(q);
    for (int i = 0; i < lvl/2; i++) {
        int *tmp = res[i];
        res[i] = res[lvl - i - 1];
        res[lvl - i - 1] = tmp;
        int t = cols[i];
        cols[i] = cols[lvl - i - 1];
        cols[lvl - i - 1] = t;
    }
    *returnSize = lvl;
    *returnColumnSizes = cols;
    return res;
}

// Print Right View of a Binary Tree
// Complexity: O(n)
int height(Node* root) {
    if (!root) return -1;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

void rightViewUtil(Node* root, int level, int *maxLevel, int *arr) {
    if (!root)
        return;
    if (level > *maxLevel) {
        arr[level] = root->key;
        *maxLevel = level;
    }
    // Process right subtree first to capture the right view
    rightViewUtil(root->right, level + 1, maxLevel, arr);
    rightViewUtil(root->left, level + 1, maxLevel, arr);
}

int* getRightView(Node* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    int h = height(root);
    int size = h + 1; // number of levels
    int* arr = malloc(size * sizeof(int));
    int maxLevel = -1;
    rightViewUtil(root, 0, &maxLevel, arr);
    *returnSize = maxLevel + 1;
    return arr;
}

// Creates a mirror image of the BST (swaps left and right subtrees)
// Complexity: O(n)
Node* mirror(Node* root) {
    if (!root)
        return NULL;
    Node* temp = root->left;
    root->left = mirror(root->right);
    root->right = mirror(temp);
    return root;
}

// Builds a BST from the given input
// Complexity: O(n)
Node* buildTreeFromInput() {
    int n;
    scanf("%d", &n);
    int *parentArr = malloc(n * sizeof(int));
    Node **nodes = malloc(n * sizeof(Node*));
    Node *root = NULL;

    for (int i = 0; i < n; i++) {
        scanf("%d", &parentArr[i]);
        nodes[i] = newNode(i);
    }
    for (int i = 0; i < n; i++) {
        if (parentArr[i] == -1)
            root = nodes[i];
        else {
            int pid = parentArr[i];
            nodes[i]->p = nodes[pid];
            if (!nodes[pid]->left)
                nodes[pid]->left = nodes[i];
            else
                nodes[pid]->right = nodes[i];
        }
    }
    free(parentArr);
    free(nodes);
    return root;
}

// Iterative DFS (Preorder) for the binary tree
// Complexity: O(n)
void dfs(Node* root) {
    if (!root)
        return;
    
    int capacity = 100;
    int top = -1;
    Node** stack = malloc(capacity * sizeof(Node*));
    stack[++top] = root;
    
    while (top >= 0) {
        Node* current = stack[top--];
        printf("%d ", current->key);
        
        // Push right child first so that left is processed first
        if (current->right)
            stack[++top] = current->right;
        if (current->left)
            stack[++top] = current->left;
        
        // Resize the stack if needed
        if (top + 1 >= capacity) {
            capacity *= 2;
            stack = realloc(stack, capacity * sizeof(Node*));
        }
    }
    free(stack);
}

// Check if two binary trees are the same
// Complexity: O(n)
int isSameTree(Node* p, Node* q) {
    if (!p && !q) return 1;
    if (!p || !q) return 0;
    return (p->key == q->key) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// Helper to check if two subtrees are mirror images
// Complexity: O(n)
int isMirror(Node* a, Node* b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return (a->key == b->key) && isMirror(a->left, b->right) && isMirror(a->right, b->left);
}

// Checks if the tree is symmetric around its center
// Complexity: O(n)
int isSymmetric(Node* root) {
    return (root == NULL) || isMirror(root->left, root->right);
}

// Helper function to print root-to-leaf paths
// path[] stores the current path and pathLen is its length
// Complexity: O(n)
void printPathsUtil(Node* root, int path[], int pathLen) {
    if (!root)
        return;

    path[pathLen++] = root->key;

    // If it's a leaf, print the path
    if (!root->left && !root->right) {
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printPathsUtil(root->left, path, pathLen);
        printPathsUtil(root->right, path, pathLen);
    }
}

// Prints all root-to-leaf paths 
// Complexity: O(n) average, worst-case O(n^2) for skewed trees
void printRootToLeafPaths(Node* root) {
    int path[1000];  // Assumes maximum path length is less than 1000
    printPathsUtil(root, path, 0);
}

// Find number of structurally unique BSTs that store values 1 to n
// Complexity: O(n^2)
int numTrees(int n) {
    int *arr = calloc(n + 1, sizeof(int));
    arr[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            arr[i] += arr[j] * arr[i - 1 - j];
        }
    }
    int result = arr[n];
    free(arr);
    return result;
}

// Recover the BST by swapping two nodes
// Complexity: O(n)
void recoverTreeUtil(Node* root, Node** first, Node** second, Node** prev) {
    if (!root)
        return;
    recoverTreeUtil(root->left, first, second, prev);
    if (*prev && root->key < (*prev)->key) {
        if (!*first)
            *first = *prev;
        *second = root;
    }
    *prev = root;
    recoverTreeUtil(root->right, first, second, prev);
}

void recoverTree(Node* root) {
    Node *first = NULL, *second = NULL, *prev = NULL;
    recoverTreeUtil(root, &first, &second, &prev);
    if (first && second) {
        int temp = first->key;
        first->key = second->key;
        second->key = temp;
    }
}

// Constructs the binary tree from preorder and inorder traversal arrays
Node* buildTreeHelper(int preorder[], int preStart, int preEnd, int inorder[], int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd)
        return NULL;
    
    int rootVal = preorder[preStart];
    Node* root = newNode(rootVal);
    
    int inRootIndex;
    for (inRootIndex = inStart; inRootIndex <= inEnd; inRootIndex++) {
        if (inorder[inRootIndex] == rootVal)
            break;
    }
    
    int leftSize = inRootIndex - inStart;
    root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSize, inorder, inStart, inRootIndex - 1);
    root->right = buildTreeHelper(preorder, preStart + leftSize + 1, preEnd, inorder, inRootIndex + 1, inEnd);
    return root;
}

Node* buildTree(int preorder[], int preSize, int inorder[], int inSize) {
    return buildTreeHelper(preorder, 0, preSize - 1, inorder, 0, inSize - 1);
}

// Constructs the binary tree from postorder and inorder traversal arrays
Node* buildTreePostorderHelper(int postorder[], int postStart, int postEnd, int inorder[], int inStart, int inEnd) {
    if (postStart > postEnd || inStart > inEnd)
        return NULL;
    
    int rootVal = postorder[postEnd];
    Node* root = newNode(rootVal);
    
    int inRootIndex;
    for (inRootIndex = inStart; inRootIndex <= inEnd; inRootIndex++) {
        if (inorder[inRootIndex] == rootVal)
            break;
    }
    
    int rightSize = inEnd - inRootIndex;
    root->left = buildTreePostorderHelper(postorder, postStart, postEnd - rightSize - 1, inorder, inStart, inRootIndex - 1);
    root->right = buildTreePostorderHelper(postorder, postEnd - rightSize, postEnd - 1, inorder, inRootIndex + 1, inEnd);
    return root;
}

Node* buildTreePostorder(int postorder[], int postSize, int inorder[], int inSize) {
    return buildTreePostorderHelper(postorder, 0, postSize - 1, inorder, 0, inSize - 1);
}

// Invert/Reverse BST
// Complexity: O(n)
Node* invertTree(Node* root) {
    if (!root)
        return NULL;
    Node* left = invertTree(root->left);
    Node* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

// Convert Sorted Array to BST
// Complexity: O(n)
Node* sortedArrayToBST(int* nums, int numsSize) {
    if (numsSize == 0) return NULL;
    int mid = numsSize / 2;
    Node* root = newNode(nums[mid]);
    root->left = sortedArrayToBST(nums, mid);
    root->right = sortedArrayToBST(nums + mid + 1, numsSize - mid - 1);
    return root;
}

// Convert Sorted List to BST
// Complexity: O(n)

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

Node* sortedListToBST(ListNode* head) {
    if (!head) return NULL;
    if (!head->next) return newNode(head->val);
    ListNode *prev = NULL, *slow = head, *fast = head;
    for (; fast && fast->next; fast = fast->next->next) {
        prev = slow;
        slow = slow->next;
    }
    Node *root = newNode(slow->val);
    prev->next = NULL;
    root->left  = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
    return root;
}

// Check if binary tree has a path that adds up to given sum
// Complexity: O(n)
int hasPathSum(Node* root, int sum) {
    if (!root) return 0;
    if (!root->left && !root->right) return sum == root->key;
    return hasPathSum(root->left, sum - root->key) || hasPathSum(root->right, sum - root->key);
}

// Print all paths that add up to a given sum
// Complexity: O(n)
void pathSumUtil(Node* root, int sum, int path[], int pathLen) {
    if (!root) return;
    path[pathLen++] = root->key;
    sum -= root->key;
    if (!root->left && !root->right && sum == 0) {
        for (int i = 0; i < pathLen; i++)
            printf("%d ", path[i]);
        printf("\n");
    } else {
        pathSumUtil(root->left, sum, path, pathLen);
        pathSumUtil(root->right, sum, path, pathLen);
    }
}

void pathSum(Node* root, int sum) {
    int path[1000];
    pathSumUtil(root, sum, path, 0);
}

// Print all root to leaf paths
// Complexity: O(n)
void printPaths(Node* root, int path[], int pathLen) {
    if (!root) return;
    path[pathLen++] = root->key;
    if (!root->left && !root->right) {
        for (int i = 0; i < pathLen; i++)
            printf("%d ", path[i]);
        printf("\n");
    } else {
        printPaths(root->left, path, pathLen);
        printPaths(root->right, path, pathLen);
    }
}

// Construct a Maximum Binary Tree from two given Binary Trees
// Complexity: O(n)
Node* mergeTrees(Node* t1, Node* t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    t1->key += t2->key;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
}

// Flatten Binary Tree to Linked List
// Complexity: O(n)
void flatten(Node* root) {
    if (!root) return;
    flatten(root->left);
    flatten(root->right);
    Node* right = root->right;
    root->right = root->left;
    root->left = NULL;
    while (root->right) root = root->right;
    root->right = right;
}

// Find the sum of all left leaves in a binary tree
// Complexity: O(n)
int sumOfLeftLeaves(Node* root) {
    if (!root) return 0;
    if (root->left && !root->left->left && !root->left->right)
        return root->left->key + sumOfLeftLeaves(root->right);
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}