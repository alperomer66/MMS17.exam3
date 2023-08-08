#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// free memo
void freeList(struct Node *cll) {
    struct Node *current = cll;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}


struct Node* insertAfter(struct Node *cll, int skipCount, int newElem) {
    struct Node *newNode = createNode(newElem);
    if (cll == NULL) {
        newNode->next = newNode;  // ako spisukut e prazen noviya el she skochi kum sebe si 
        return newNode;
    }

    struct Node *current = cll;
    for (int i = 0; i < skipCount; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    
    return newNode;
}

void print(struct Node *cll) {
    if (cll == NULL) {
        return;
    }

    struct Node *current = cll;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != cll);
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);

    if (N <= 0) {
        printf("N should be greater than 0.\n");
        return 1;
    }

    struct Node *cll = NULL;

    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        struct Node *newNode = createNode(num);
        
        if (cll == NULL) {
            cll = newNode;
            cll->next = cll;
        } else {
            newNode->next = cll->next;
            cll->next = newNode;
            cll = newNode;
        }
    }

    printf(" Linked List elements: ");
    print(cll);

    int skipCount, newElem;
    printf("Enter skipCount and new element: ");
    scanf("%d %d", &skipCount, &newElem);

    struct Node *newNode = insertAfter(cll, skipCount, newElem);

    printf("UpdatedLinked List elements: ");
    print(cll);

    freeList(cll);  // free memo from list 
    return 0;
}//end of main 
