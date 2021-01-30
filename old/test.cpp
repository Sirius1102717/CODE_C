#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int UserNumber = 1;
typedef struct user {
    int number;
	struct user *next;
} USER;
USER *userTail = NULL;


void userInsert(USER **userTail, USER *newNode) {
    (*userTail)->next = newNode;
    *userTail = newNode;
}

USER *userCreate(USER *userHead) {
    USER *node;
    int number;
    userHead = (USER *)malloc(sizeof(USER));
    userTail = userHead;
    printf("Press EOF to end input\n");
    printf("Please input the number:");
    while (scanf("%d", &number) != EOF) {
        node = (USER *)malloc(sizeof(USER));
		node->number = number;
        printf("please input the number:");
		node->next = NULL;
        userInsert(&userTail, node);
        printf("Press the EOF to end input\n");
        printf("please input the number:");
    }
    // node = userHead->next;
	printf("%d\n",node->number);
    return userHead;
}

int main(int argc, char const *argv[]) {
    USER *head = NULL;
    head = userCreate(head);
    while (head->next) {
		printf("%d\n",head->next->number);
		head = head->next;
    }

    return 0;
}
