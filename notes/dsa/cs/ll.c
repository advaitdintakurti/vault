#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int value) {
    Node* new = (Node*)malloc(sizeof(Node));
    if (!new) return NULL;  // Check if malloc failed
    new->data = value;
    new->next = NULL;
    return new;
}

// Insert at beginning - O(1)
Node* insertFront(Node* head, int value) {
    Node* new = createNode(value);
    new->next = head;
    return new;
}

// Insert at end - O(n)
Node* insertEnd(Node* head, int value) {
    Node* new = createNode(value);
    if (!head) return new;

    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new;
    return head;
}

// Insert at position - O(n)
Node* insertAt(Node* head, int value, int position) {
    if (position == 0) return insertFront(head, value);

    Node* current = head;
    for (int i = 0; i < position - 1 && current; i++) {
        current = current->next;
    }
    if (!current) return head;

    Node* new = createNode(value);
    new->next = current->next;
    current->next = new;
    return head;
}

// Delete first occurrence of value - O(n)
Node* deleteValue(Node* head, int value) {
    if (!head) return NULL;

    if (head->data == value) {
        Node* temp = head->next;
        free(head);
        return temp;
    }

    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return head;
}

// Reverse list - O(n)
Node* reverse(Node* head) {
    Node *prev = NULL, *current = head, *next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Find middle node (Floyd's algorithm) - O(n)
Node* findMiddle(Node* head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Detect cycle (Floyd's cycle detection) - O(n)
bool hasCycle(Node* head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Merge two sorted lists - O(n+m)
Node* mergeSorted(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data <= l2->data) {
        l1->next = mergeSorted(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSorted(l1, l2->next);
        return l2;
    }
}

// Check if palindrome - O(n)
bool isPalindrome(Node* head) {
    Node *slow = head, *fast = head, *prev = NULL;

    while (fast && fast->next) {
        fast = fast->next->next;
        Node* temp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = temp;
    }

    if (fast) slow = slow->next;

    while (prev && slow) {
        if (prev->data != slow->data) return false;
        prev = prev->next;
        slow = slow->next;
    }
    return true;
}

// Reverse in groups of K - O(n)
Node* reverseK(Node* head, int k) {
    if (!head || k == 1) return head;

    Node *current = head, *next = NULL, *prev = NULL;
    int count = 0;

    while (current && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    if (next) head->next = reverseK(next, k);
    return prev;
}

// Remove duplicates from sorted list - O(n)
Node* removeDuplicates(Node* head) {
    Node* current = head;
    while (current && current->next) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

// Get nth node from end - O(n)
Node* getNthFromEnd(Node* head, int n) {
    Node *main = head, *ref = head;

    // Move ref n nodes ahead
    for (int i = 0; i < n; i++) {
        if (!ref) return NULL;
        ref = ref->next;
    }

    // Move both pointers until ref reaches end
    while (ref) {
        main = main->next;
        ref = ref->next;
    }
    return main;
}

// Utility functions
void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int getLength(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Free entire list - O(n)
void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Rotate list by k positions - O(n)
Node* rotateList(Node* head, int k) {
    if (!head || !head->next || k == 0) return head;

    // Get length and make circular
    Node* current = head;
    int length = 1;
    while (current->next) {
        length++;
        current = current->next;
    }
    current->next = head;

    // Normalize k
    k = k % length;
    if (k < 0) k += length;

    // Find new head and break circle
    k = length - k;
    while (k--) current = current->next;

    head = current->next;
    current->next = NULL;
    return head;
}

// Swap nodes in pairs - O(n)
Node* swapPairs(Node* head) {
    if (!head || !head->next) return head;

    Node* temp = head->next;
    head->next = swapPairs(temp->next);
    temp->next = head;
    return temp;
}

// Sort list using merge sort - O(n log n)
Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    // Find middle
    Node *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split list
    Node* right = slow->next;
    slow->next = NULL;

    // Recursively sort and merge
    return mergeSorted(mergeSort(head), mergeSort(right));
}

// Add two numbers represented by linked lists - O(n)
Node* addTwoNumbers(Node* l1, Node* l2) {
    Node dummy = {0, NULL};
    Node* current = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = createNode(sum % 10);
        current = current->next;
    }

    return dummy.next;
}

// Remove all elements with given value - O(n)
Node* removeElements(Node* head, int val) {
    Node dummy = {0, head};
    Node* current = &dummy;

    while (current->next) {
        if (current->next->data == val) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return dummy.next;
}

// Partition list around value x - O(n)
Node* partition(Node* head, int x) {
    Node beforeDummy = {0, NULL};
    Node afterDummy = {0, NULL};
    Node *before = &beforeDummy, *after = &afterDummy;

    while (head) {
        if (head->data < x) {
            before->next = head;
            before = head;
        } else {
            after->next = head;
            after = head;
        }
        head = head->next;
    }

    after->next = NULL;
    before->next = afterDummy.next;
    return beforeDummy.next;
}

// Reorder list: L0→Ln→L1→Ln-1→L2→Ln-2→... - O(n)
void reorderList(Node* head) {
    if (!head || !head->next) return;

    // Find middle
    Node *slow = head, *fast = head;
    Node *prev = NULL;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    prev->next = NULL;

    // Reverse second half
    Node *l2 = NULL;
    while (slow) {
        Node* next = slow->next;
        slow->next = l2;
        l2 = slow;
        slow = next;
    }

    // Merge lists
    Node* l1 = head;
    while (l1 && l2) {
        Node *l1_next = l1->next;
        Node *l2_next = l2->next;

        l1->next = l2;
        l2->next = l1_next;

        l1 = l1_next;
        l2 = l2_next;
    }
}

// Find intersection point of two lists - O(n)
Node* getIntersectionNode(Node* headA, Node* headB) {
    if (!headA || !headB) return NULL;

    Node *a = headA, *b = headB;
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

// Get decimal value of binary linked list - O(n)
int getDecimalValue(Node* head) {
    int result = 0;
    while (head) {
        result = (result << 1) | head->data;
        head = head->next;
    }
    return result;
}

// Get intersection point of Y-shaped linked lists - O(n)
Node* getIntersectionPoint(Node* list1, Node* list2) {
    if (!list1 || !list2) return NULL;

    // Get lengths
    int len1 = getLength(list1);
    int len2 = getLength(list2);

    // Move longer list ahead
    while (len1 > len2) {
        list1 = list1->next;
        len1--;
    }
    while (len2 > len1) {
        list2 = list2->next;
        len2--;
    }

    // Move both lists until intersection found
    while (list1 && list2) {
        if (list1 == list2) return list1;
        list1 = list1->next;
        list2 = list2->next;
    }
    return NULL;
}

// Detect and remove cycle - O(n)
Node* detectAndRemoveCycle(Node* head) {
    if (!head || !head->next) return head;

    Node *slow = head, *fast = head;

    // Detect cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (!fast || !fast->next) return head;  // No cycle

    // Find cycle start
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // Remove cycle
    Node* start = slow;
    while (fast->next != start) {
        fast = fast->next;
    }
    fast->next = NULL;

    return head;
}

// Quick Sort for linked list - O(n log n)
Node* getTail(Node* head) {
    while (head && head->next) head = head->next;
    return head;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node *prev = NULL, *curr = head, *tail = pivot;

    while (curr != pivot) {
        if (curr->data <= pivot->data) {
            if (!*newHead) *newHead = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Node* temp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (!*newHead) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node *newHead = NULL, *newEnd = NULL;
    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

Node* quickSort(Node* head) {
    return quickSortRecur(head, getTail(head));
}

// Utility: Print list with cycle (safe) - O(n)
void printListSafe(Node* head) {
    Node* visited[1000] = {NULL};  // Adjust size as needed
    int i = 0;

    while (head) {
        // Check if node already visited
        for (int j = 0; j < i; j++) {
            if (visited[j] == head) {
                printf(" -> [CYCLE]\n");
                return;
            }
        }

        visited[i++] = head;
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}