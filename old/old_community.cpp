#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int MemberNumber = 1;
int UserNumber = 1;
int HouseNumber = 1;
int FacilityNumber = 1;

typedef struct member {
    int number;
    char name[20];
    int age;
    struct member *next;
} MEMBER;
MEMBER *memTail = NULL;

typedef struct house {
    int number;
    char name[20];
    float area;
    int purchase; // 1:be purchased 2: has not been purchased
    int live;     // 1:living 0:no living 2:idle
    struct house *next;
} HOUSE;
HOUSE *houseTail = NULL;

typedef struct user {
    int number;
    char name[20];
    char serName[20];
    struct user *next;
} USER;
USER *userTail = NULL;

typedef struct facility {
    char name[20];
    int condition; // 1.using 0.unusing
    struct facility *next;
} FACILITY;
FACILITY *facTail = NULL;

void memInsert(MEMBER **memTail, MEMBER *newNode) {
    (*memTail)->next = newNode;
    *memTail = newNode;
}

MEMBER *memLoad(MEMBER *memHead) {
    FILE *fp = fopen("member.txt", "r");
    MEMBER *node = NULL;
    int number, age;
    char name[20] = {0};
    memHead = (MEMBER *)malloc(sizeof(MEMBER));
    memTail = memHead;
    while (fscanf(fp, "%d%s%d", &number, name, &age) != EOF) {
        node = (MEMBER *)malloc(sizeof(MEMBER));
        node->number = number;
        node->age = age;
        strcpy(node->name, name);
        printf("%d %s %d\n", node->number, node->name, node->age);
        node->next = NULL;
        memInsert(&memTail, node);
        memset(name, 0, sizeof(char));
        MemberNumber++;
    }
    node = memHead->next;
    // memHead->next = node;
    fclose(fp);
    return memHead;
}

MEMBER *memCreate(MEMBER *memHead) {
    MEMBER *node;
    char name[20] = {0};
    FILE *fp = fopen("member.txt", "a+");
    if (MemberNumber == 1) {
        memHead = (MEMBER *)malloc(sizeof(MEMBER));
        memTail = memHead;
    }
    printf("Press EOF to end input\n");
    printf("Please input the name:");
    while (scanf("%s", name) != EOF) {
        node = (MEMBER *)malloc(sizeof(MEMBER));
        strcpy(node->name, name);
        printf("Please input the age:");
        scanf("%d", &node->age);
        node->number = MemberNumber;
        printf("%d %s %d\n", node->number, node->name, node->age);
        fprintf(fp, "%-10d%-10s%-10d\n", node->number, node->name, node->age);
        MemberNumber++;
        node->next = NULL;
        memInsert(&memTail, node);
        memset(name, 0, sizeof(char) * 20);
        printf("Press EOF to end input\n");
        printf("Please input the name:");
    }
    fclose(fp);
    return memHead;
}

MEMBER *memNumSearch(int number, MEMBER *memHead) {
    MEMBER *p;
    p = memHead;
    while (p->next && p->next->number != number) {
        p = p->next;
    }
    if (p->next->number == number)
        return p;
    else
        perror("error search\n");
}

MEMBER *memNameSearch(char name[], MEMBER *memHead) {
    MEMBER *p;
    p = memHead;
    while (p->next && strcmp(name, p->next->name) != 0) {
        p = p->next;
    }
    if (strcmp(name, p->next->name) == 0)
        return p;
    else
        perror("error search\n");
}

void memSearch(MEMBER *memHead) {
    printf("Please choose the way:\n1.name\n2.number\n");
    int choose;
    char name[20] = {0};
    int number;
    MEMBER *prePosition, *curPosition;
    scanf("%d", &choose);
    if (choose == 1) {
        printf("Please input the name:");
        scanf("%s", name);
        prePosition = memNameSearch(name, memHead);
        curPosition = prePosition->next;
    } else {
        printf("Please input the number:");
        scanf("%d", &number);
        prePosition = memNumSearch(number, memHead);
        curPosition = prePosition->next;
    }
    printf("%d %s %d\n", curPosition->number, curPosition->name,
           curPosition->age);
}

void memNodeDelete(MEMBER *pre) {
    MEMBER *cur = pre->next;
    pre->next = cur->next;
    free(cur);
}

void memNameFileDel(FILE *fp, FILE *rp, MEMBER *pre) {
    MEMBER *chan, *cur = pre->next;
    chan = (MEMBER *)malloc(sizeof(MEMBER));
    while (fscanf(fp, "%d%s%d", &chan->number, chan->name, &chan->age) != EOF) {
        if (strcmp(chan->name, cur->name) == 0)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10d\n", chan->number, chan->name,
                    chan->age);
    }
}

void memNumFileDel(FILE *fp, FILE *rp, MEMBER *pre) {
    MEMBER *chan, *cur = pre->next;
    chan = (MEMBER *)malloc(sizeof(MEMBER));
    while (fscanf(fp, "%d%s%d", &chan->number, chan->name, &chan->age) != EOF) {
        if (chan->number == cur->number)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10d\n", chan->number, chan->name,
                    chan->age);
    }
}

void memFileDelete(MEMBER *memHead, char name[], int number, int choose) {
    FILE *fp = fopen("member.txt", "r");
    FILE *rp = fopen("temp.txt", "w");
    MEMBER *position;
    int err;
    if (choose == 1) {
        position = memNameSearch(name, memHead);
        memNameFileDel(fp, rp, position);
    } else {
        position = memNumSearch(number, memHead);
        memNumFileDel(fp, rp, position);
    }
    memNodeDelete(position);
    fclose(fp);
    fclose(rp);
    err = remove("member.txt");
    if (err == 0)
        printf("Delete successfully\n");
    else
        perror("error delete\n");
    rename("temp.txt", "member.txt");
}

void memDelete(MEMBER *memHead) {
    int choose;
    char name[20] = {0};
    int number = 0;
    printf("Please choose the way:\n1.name\n2.number\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the name:");
        scanf("%s", name);
        break;
    default:
        printf("Please input the number:");
        scanf("%d", &number);
    }
    memFileDelete(memHead, name, number, choose);
    printf("The delete had been finished\n");
}

void memNumModify(int number, MEMBER **memHead) {
    MEMBER *position = memNumSearch(number, *memHead)->next;
    MEMBER chan;
    FILE *fp = fopen("member.txt", "r+");
    int newnum;
    printf("Please input the new number:");
    scanf("%d", &newnum);
    while (fscanf(fp, "%d%s%d", &chan.number, chan.name, &chan.age) != EOF) {
        if (chan.number == position->number) {
            fseek(fp, 22, SEEK_CUR);
            fprintf(fp, "%d", newnum);
            break;
        }
    }
    position->number = newnum;
    printf("%d %s %d\n", position->number, position->name, position->age);
    fclose(fp);
}

void memNameModify(char name[], MEMBER **memHead) {
    MEMBER *position = memNameSearch(name, *memHead)->next;
    MEMBER chan;
    FILE *fp = fopen("member.txt", "r+");
    char newName[20] = {0};
    printf("Please input the newname:");
    scanf("%s", newName);
    while (fscanf(fp, "%d%s%d", &chan.number, chan.name, &chan.age) != EOF) {
        if (strcmp(position->name, chan.name) == 0) {
            fseek(fp, -12, SEEK_CUR);
            fprintf(fp, "%s", newName);
            break;
        }
    }
    strcpy(position->name, newName);
    printf("%d %s %d\n", position->number, position->name, position->age);
    fclose(fp);
}

MEMBER *memModify(MEMBER *memHead) {
    int choose;
    char name[20] = {0};
    int number;
    printf("Please choose the way:\n1.name\n2.number\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the name:");
        scanf("%s", name);
        memNameModify(name, &memHead);
        break;
    default:
        printf("Please input the number:");
        scanf("%d", &number);
        memNumModify(number, &memHead);
    }
    return memHead;
}

MEMBER *memberManage(MEMBER *memHead) {
    int choose;
    memHead = memLoad(memHead);
    printf("Please input your "
           "choice:\n1:Create\n2:Delete\n3.Search\n4.Modify\n5.Exit to main "
           "menu\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        memHead = memCreate(memHead);
        memHead = memberManage(memHead);
        break;
    case 2:
        memDelete(memHead);
        memHead = memberManage(memHead);
        break;
    case 3:
        memSearch(memHead);
        memHead = memberManage(memHead);
        break;
    case 4:
        memHead = memModify(memHead);
        memHead = memberManage(memHead);
        break;
    default:
        system("cls");
    }
    return memHead;
}

void houseInsert(HOUSE **houseTail, HOUSE *newNode) {
    (*houseTail)->next = newNode;
    *houseTail = newNode;
}

HOUSE *houseLoad(HOUSE *houseHead) {
    FILE *fp = fopen("house.txt", "r");
    HOUSE *node = NULL;
    int number, purchase, live;
    float area;
    char name[20] = {0};
    houseHead = (HOUSE *)malloc(sizeof(HOUSE));
    houseTail = houseHead;
    while (fscanf(fp, "%d%s%f%d%d", &number, name, &area, &purchase, &live) !=
           EOF) {
        node = (HOUSE *)malloc(sizeof(HOUSE));
        node->area = area;
        strcpy(node->name, name);
        node->number = number;
        node->purchase = purchase;
        node->live = live;
        printf("%d %s %f %d %d\n", node->number, node->name, node->area,
               node->purchase, node->live);
        node->next = NULL;
        houseInsert(&houseTail, node);
        memset(name, 0, sizeof(char) * 20);
        HouseNumber++;
    }
    node = houseHead->next;
    fclose(fp);
    return houseHead;
}

HOUSE *houseCreate(HOUSE *houseHead) {
    HOUSE *node;
    char name[20] = {0};
    FILE *fp = fopen("user.txt", "a+");
    if (HouseNumber == 1) {
        houseHead = (HOUSE *)malloc(sizeof(HOUSE));
        houseTail = houseHead;
    }
    printf("Press EOF to end input\n");
    printf("Please input the name:");
    while (scanf("%s", name) != EOF) {
        node = (HOUSE *)malloc(sizeof(HOUSE));
        strcpy(node->name, name);
        printf("Please input the area:");
        scanf("%f", &node->area);
        printf("Please input the purchase condition\n1:purchased\n2:not "
               "purchased\n");
        scanf("%d", &node->purchase);
        while (1) {
            if (node->purchase == 1 || node->purchase == 2)
                break;
            else {
                printf("Your input is error,Please input again:");
                scanf("%d", &node->purchase);
            }
        }
        printf(
            "Please input the live condition\n1:living\n2:no living\n3:idle");
        scanf("%d", &node->live);
        while (1) {
            if (node->live == 1 || node->live == 2 || node->live == 3)
                break;
            else {
                printf("Your input is error,Please input again:");
                scanf("%d", &node->live);
            }
        }
        node->number = HouseNumber;
        HouseNumber++;
        printf("%d %s %f %d %d\n", node->number, node->name, node->area,
               node->purchase, node->live);
        fprintf(fp, "%-10d%-10s%-10f%-10d%-10d\n", node->number, node->name,
                node->area, node->purchase, node->live);
        node->next = NULL;
        houseInsert(&houseTail, node);
        memset(name, 0, sizeof(char) * 20);
        printf("Press the EOF to end input\n");
        printf("please input the name:");
    }
    fclose(fp);
    return houseHead;
}

HOUSE *houseNumSearch(HOUSE *houseHead, int number) {
    HOUSE *p;
    p = houseHead;
    while (p->next && p->next->number != number) {
        p = p->next;
    }
    if (p->next->number == number)
        return p;
    else
        perror("error search\n");
}

HOUSE *houseNameSearch(HOUSE *houseHead, char name[]) {
    HOUSE *p = houseHead;
    while (p->next && strcmp(p->next->name, name) != 0) {
        p = p->next;
    }
    if (strcmp(p->next->name, name) == 0)
        return p;
    else
        perror("error search\n");
}

void houseSearch(HOUSE *houseHead) {
    printf("Please choose the way:\n1.name\n2.number\n");
    int choose;
    char name[20] = {0};
    int number;
    HOUSE *prePosition, *curPosition;
    scanf("%d", &choose);
    if (choose == 1) {
        printf("Please input the name:");
        scanf("%s", name);
        prePosition = houseNameSearch(houseHead, name);
        curPosition = prePosition->next;
    } else {
        printf("Please input the number:");
        scanf("%d", &number);
        prePosition = houseNumSearch(houseHead, number);
        curPosition = prePosition->next;
    }
    printf("%d %s %f %d %d\n", curPosition->number, curPosition->name,
           curPosition->area, curPosition->number, curPosition->live);
}

void houseNodeDelete(HOUSE *pre) {
    HOUSE *cur = pre->next;
    pre->next = cur->next;
    free(cur);
}

void houseNameFileDel(FILE *fp, FILE *rp, HOUSE *pre) {
    HOUSE *chan, *cur = pre->next;
    chan = (HOUSE *)malloc(sizeof(HOUSE));
    while (fscanf(fp, "%d%s%f%d%d", &chan->number, chan->name, &chan->area,
                  &chan->purchase, &chan->live) != EOF) {
        if (strcmp(cur->name, chan->name) == 0)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10f%-10d%-10d\n", chan->number, chan->name,
                    chan->area, chan->purchase, chan->live);
    }
}

void houseNumFileDel(FILE *fp, FILE *rp, HOUSE *pre) {
    HOUSE *chan, *cur = pre->next;
    chan = (HOUSE *)malloc(sizeof(HOUSE));
    while (fscanf(fp, "%d%s%f%d%d", &chan->number, chan->name, &chan->area,
                  &chan->purchase, &chan->live) != EOF) {
        if (cur->number == chan->number)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10f%-10d%-10d\n", chan->number, chan->name,
                    chan->area, chan->purchase, chan->live);
    }
}

void houseFileDelete(HOUSE *houseHead, char name[], int number, int choose) {
    FILE *fp = fopen("house.txt", "r");
    FILE *rp = fopen("temp.txt", "w");
    HOUSE *position;
    int err;
    switch (choose) {
    case 1:
        position = houseNameSearch(houseHead, name);
        houseNameFileDel(fp, rp, position);
        break;
    default:
        position = houseNumSearch(houseHead, number);
        houseNumFileDel(fp, rp, position);
    }
    houseNodeDelete(position);
    fclose(fp);
    fclose(rp);
    err = remove("house.txt");
    if (err == 0)
        printf("Delete successfully\n");
    else
        perror("error delete\n");
    rename("temp.txt", "house.txt");
}

void houseDelete(HOUSE *houseHead) {
    int choose;
    char name[20];
    int number;
    printf("Please choose the way:\n1.name\n2.number\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the name to delete:");
        scanf("%s", name);
        break;
    default:
        printf("Please input the number to delete:");
        scanf("%d", &number);
    }
    houseFileDelete(houseHead, name, number, choose);
    printf("The delete had been finished\n");
}

void houseNumModify(int number, HOUSE **houseHead) {
    HOUSE *position = houseNumSearch(*houseHead, number)->next;
    HOUSE chan;
    FILE *fp = fopen("user.txt", "r+");
    int newNum;
    printf("Please input the new number:");
    scanf("%d", &newNum);
    while (fscanf(fp, "%d%s%f%d%d", &chan.number, chan.name, &chan.area,
                  &chan.purchase, &chan.live) != EOF) {
        if (position->number == chan.number) {
            fseek(fp, -41, SEEK_CUR);
            fprintf(fp, "%d", newNum);
            break;
        }
    }
    position->number = newNum;
    printf("%d %s %f %d %d", position->number, position->name, position->area,
           position->purchase, position->live);
    fclose(fp);
}

void houseNameModify(char name[], HOUSE **houseHead) {
    HOUSE *position = houseNameSearch(*houseHead, name)->next;
    HOUSE chan;
    FILE *fp = fopen("user.txt", "r+");
    char newName[20] = {0};
    printf("Please input the new name:");
    scanf("%s", newName);
    while (fscanf(fp, "%d%s%f%d%d", &chan.number, chan.name, &chan.area,
                  &chan.purchase, &chan.live) != EOF) {
        if (strcmp(position->name, chan.name) == 0) {
            fseek(fp, -31, SEEK_CUR);
            fprintf(fp, "%s", newName);
            break;
        }
    }
    strcpy(position->name, newName);
    printf("%d %s %f %d %d", position->number, position->name, position->area,
           position->purchase, position->live);
    fclose(fp);
}

HOUSE *houseModify(HOUSE *houseHead) {
    int choose;
    char name[20] = {0};
    int number;
    printf("Please choose the way:\n1.number\n2.name\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the number:");
        scanf("%d", &number);
        houseNumModify(number, &houseHead);
        break;
    default:
        printf("Please input the name:");
        scanf("%s", name);
        houseNameModify(name, &houseHead);
    }
    return houseHead;
}

HOUSE *houseManage(HOUSE *houseHead) {
    int choose;
    houseHead = houseLoad(houseHead);
    printf("Please input your "
           "choice:\n1:Create\n2:Delete\n3.Search\n4.Modify\n5.Exit to main "
           "menu\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        houseHead = houseCreate(houseHead);
        houseHead = houseManage(houseHead);
        break;
    case 2:
        houseDelete(houseHead);
        houseHead = houseManage(houseHead);
        break;
    case 3:
        houseSearch(houseHead);
        houseHead = houseManage(houseHead);
        break;
    case 4:
        houseHead = houseModify(houseHead);
        houseHead = houseManage(houseHead);
        break;
    default:
        system("cls");
    }
    return houseHead;
}

void facInsert(FACILITY **facTail, FACILITY *newNode) {
    (*facTail)->next = newNode;
    *facTail = newNode;
}

FACILITY *facLoad(FACILITY *facHead) {
    FILE *fp = fopen("facility.txt", "r");
    FACILITY *node = NULL;
    int condition;
    char name[20] = {0};
    facTail = facHead;
    while (fscanf(fp, "%d%s", &condition, name) != EOF) {
        node = (FACILITY *)malloc(sizeof(FACILITY));
        node->condition = condition;
        strcpy(node->name, name);
        printf("%s %d\n", node->name, node->condition);
        node->next = NULL;
        facInsert(&facTail, node);
        memset(name, 0, sizeof(char) * 20);
        FacilityNumber++;
    }
    node = facTail->next;
    fclose(fp);
    return facHead;
}

FACILITY *facCreate(FACILITY *facHead) {
    FACILITY *node;
    char name[20] = {0};
    FILE *fp = fopen("user.txt", "a+");
    if (FacilityNumber == 1) {
        facHead = (FACILITY *)malloc(sizeof(FACILITY));
        facTail = facHead;
    }
    printf("Press EOF to end input\n");
    printf("Please input the name:");
    while (scanf("%s", name) != EOF) {
        node = (FACILITY *)malloc(sizeof(FACILITY));
        strcpy(node->name, name);
        printf("Please input the condition:\n1:using\n2:unusing\n");
        printf("%s %d\n", node->name, node->condition);
        fprintf(fp, "%-10s%-10d", node->name, node->condition);
        FacilityNumber++;
        node->next = NULL;
        facInsert(&facTail, node);
        memset(name, 0, sizeof(char) * 20);
        printf("Press the EOF to end input\n");
        printf("please input the name:");
    }
    fclose(fp);
    return facHead;
}

FACILITY *facNameSearch(FACILITY *facHead, char name[]) {
    FACILITY *position = facHead;
    while (position->next && strcmp(position->next->name, name) != 0) {
        position = position->next;
    }
    if (strcmp(position->next->name, name) == 0)
        return position;
    else
        perror("error search\n");
}

void facSearch(FACILITY *facHead) {
    char name[20] = {0};
    FACILITY *prePosition, *curPosition;
    printf("Please input the name:");
    scanf("%s", name);
    prePosition = facNameSearch(facHead, name);
    curPosition = prePosition->next;
    printf("%s %d\n", curPosition->name, curPosition->condition);
}

void facNodeDelete(FACILITY *pre) {
    FACILITY *cur = pre->next;
    pre->next = cur->next;
    free(cur);
}

void facFileNameDel(FILE *fp, FILE *rp, FACILITY *pre) {
    FACILITY *chan, *cur = pre->next;
    chan = (FACILITY *)malloc(sizeof(FACILITY));
    while (fscanf(fp, "%s%d", chan->name, &chan->condition) != EOF) {
        if (strcmp(cur->name, chan->name) == 0)
            continue;
        else
            fprintf(rp, "%-10s%-10d", chan->name, chan->condition);
    }
}

void facFileDelete(FACILITY *facHead, char name[]) {
    FILE *fp = fopen("user.txt", "r");
    FILE *rp = fopen("temp.txt", "w");
    FACILITY *position;
    int err;
    position = facNameSearch(facHead, name);
    facFileNameDel(fp, rp, position);
    facNodeDelete(position);
    fclose(fp);
    fclose(rp);
    err = remove("facility.txt");
    if (err == 0)
        printf("Delete successfully\n");
    else
        perror("error delete\n");
    rename("temp.txt", "facility.txt");
}

void facDelete(FACILITY *facHead) {
    char name[20];
    printf("Please input the name to delete:");
    scanf("%s", name);
    facFileDelete(facHead, name);
    printf("The delete had been finished\n");
}

void facNameModify(char name[], FACILITY **facHead) {
    FACILITY *position = facNameSearch(*facHead, name)->next;
    FACILITY chan;
    FILE *fp = fopen("facility.txt", "r+");
    char newName[20] = {0};
    printf("Please input the new name:");
    scanf("%s", newName);
    while (fscanf(fp, "%s%d", chan.name, &chan.condition) != EOF) {
        if (strcmp(position->name, chan.name) == 0) {
            fseek(fp, -11, SEEK_CUR);
            fprintf(fp, "%s", newName);
            break;
        }
    }
    strcpy(position->name, newName);
    printf("%s %d", position->name, position->condition);
    fclose(fp);
}

FACILITY *facModify(FACILITY *facHead) {
    char name[20] = {0};
    printf("Please input the name:");
    scanf("%s", name);
    facNameModify(name, &facHead);
    return facHead;
}

FACILITY *facManage(FACILITY *facHead) {
    int choose;
    printf("Please input your "
           "choice:\n1:Create\n2:Delete\n3.Search\n4.Modify\n5.Exit to main "
           "menu\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        facHead = facCreate(facHead);
        facHead = facManage(facHead);
        break;
    case 2:
        facDelete(facHead);
        facHead = facManage(facHead);
        break;
    case 3:
        facSearch(facHead);
        facHead = facManage(facHead);
        break;
    case 4:
        facHead = facModify(facHead);
        facHead = facManage(facHead);
        break;
    default:
        system("cls");
    }
    return facHead;
}

void userInsert(USER **userTail, USER *newNode) {
    (*userTail)->next = newNode;
    *userTail = newNode;
}

USER *userLoad(USER *userHead) {
    FILE *fp = fopen("user.txt", "r");
    USER *node = NULL;
    int number;
    char name[20] = {0}, serName[20] = {0};
    userHead = (USER *)malloc(sizeof(USER));
    userTail = userHead;
    while (fscanf(fp, "%d%s%s", &number, name, serName) != EOF) {
        node = (USER *)malloc(sizeof(USER));
        node->number = number;
        strcpy(node->name, name);
        strcpy(node->serName, serName);
        printf("%d %s %s\n", node->number, node->name, node->serName);
        node->next = NULL;
        userInsert(&userTail, node);
        memset(name, 0, sizeof(char) * 20);
        memset(serName, 0, sizeof(char) * 20);
        UserNumber++;
    }
    // node = userHead->next;
    fclose(fp);
    return userHead;
}

USER *userCreate(USER *userHead) {
    USER *node;
    char name[20] = {0};
    FILE *fp = fopen("user.txt", "a+");
    if (UserNumber == 1) {
        userHead = (USER *)malloc(sizeof(USER));
        userTail = userHead;
    }
    printf("Press EOF to end input\n");
    printf("Please input the name:");
    while (scanf("%s", name) != EOF) {
        node = (USER *)malloc(sizeof(USER));
        strcpy(node->name, name);
        printf("Please input the service member name:");
        scanf("%s", node->serName);
        node->number = UserNumber;
        printf("%d %s %s\n", node->number, node->name, node->serName);
        fprintf(fp, "%-10d%-10s%-10s\n", node->number, node->name,
                node->serName);
        UserNumber++;
        node->next = NULL;
        userInsert(&userTail, node);
        memset(name, 0, sizeof(char) * 20);
        printf("Press the EOF to end input\n");
        printf("please input the name:");
    }
    // if (UserNumber == 1)
    // node = userHead->next;
    fclose(fp);
    return userHead;
}

USER *userNumSearch(USER *userHead, int number) {
    USER *p;
    p = userHead;
    while (p->next && p->next->number != number) {
        p = p->next;
    }
    if (p->next->number == number)
        return p;
    else
        perror("error search\n");
}

USER *userNameSearch(USER *userHead, char name[]) {
    USER *p = userHead;
    while (p->next && strcmp(p->next->name, name) != 0) {
        p = p->next;
    }
    if (strcmp(p->next->name, name) == 0)
        return p;
    else
        perror("error search\n");
}

USER *userSerNameSearch(USER *userHead, char serName[]) {
    USER *p = userHead;
    while (p->next && strcmp(p->next->serName, serName) != 0) {
        p = p->next;
    }
    if (strcmp(p->next->serName, serName) == 0)
        return p;
    else
        perror("error search\n");
}

void userSearch(USER *userHead) {
    printf("Please choose the way:\n1.name\n2.number\n");
    int choose;
    char name[20] = {0};
    int number;
    USER *prePosition, *curPosition;
    scanf("%d", &choose);
    if (choose == 1) {
        printf("Please input the name:");
        scanf("%s", name);
        prePosition = userNameSearch(userHead, name);
        curPosition = prePosition->next;
    } else {
        printf("Please input the number:");
        scanf("%d", &number);
        prePosition = userNumSearch(userHead, number);
        curPosition = prePosition->next;
    }
    printf("%d %s %s\n", curPosition->number, curPosition->name,
           curPosition->serName);
}

void userNodeDelete(USER *pre) {
    USER *cur = pre->next;
    pre->next = cur->next;
    free(cur);
}

void userNameFileDel(FILE *fp, FILE *rp, USER *pre) {
    USER *chan, *cur = pre->next;
    chan = (USER *)malloc(sizeof(USER));
    while (fscanf(fp, "%d%s%s", &chan->number, chan->name, chan->serName) !=
           EOF) {
        if (strcmp(cur->name, chan->name) == 0)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10s\n", chan->number, chan->name,
                    chan->serName);
    }
}

void userNumFileDel(FILE *fp, FILE *rp, USER *pre) {
    USER *chan, *cur = pre->next;
    chan = (USER *)malloc(sizeof(USER));
    while (fscanf(fp, "%d%s%s", &chan->number, chan->name, chan->serName) !=
           EOF) {
        if (cur->number == chan->number)
            continue;
        else
            fprintf(rp, "%-10d%-10s%-10s\n", chan->number, chan->name,
                    chan->serName);
    }
}

void userFileDelete(USER *userHead, char name[], int number, int choose) {
    FILE *fp = fopen("user.txt", "r");
    FILE *rp = fopen("temp.txt", "w");
    USER *position;
    int err;
    switch (choose) {
    case 1:
        position = userNameSearch(userHead, name);
        userNameFileDel(fp, rp, position);
        break;
    default:
        position = userNumSearch(userHead, number);
        userNumFileDel(fp, rp, position);
    }
    userNodeDelete(position);
    fclose(fp);
    fclose(rp);
    err = remove("user.txt");
    if (err == 0)
        printf("Delete successfully\n");
    else
        perror("error delete\n");
    rename("temp.txt", "user.txt");
}

void userDelete(USER *userHead) {
    int choose;
    char name[20];
    int number;
    printf("Please choose the way:\n1.name\n2.number\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the name to delete:");
        scanf("%s", name);
        break;
    default:
        printf("Please input the number to delete:");
        scanf("%d", &number);
    }
    userFileDelete(userHead, name, number, choose);
    printf("The delete had been finished\n");
}

void userNumModify(int number, USER **userHead) {
    USER *position = userNumSearch(*userHead, number)->next;
    USER chan;
    FILE *fp = fopen("user.txt", "r+");
    int newNum, lenSerName;
    lenSerName = strlen(position->serName);
    printf("Please input the new number:");
    scanf("%d", &newNum);
    while (fscanf(fp, "%d%s%s", &chan.number, chan.name, chan.serName) != EOF) {
        if (position->number == chan.number) {
            fseek(fp, -(20 + lenSerName), SEEK_CUR);
            fprintf(fp, "%d", newNum);
            break;
        }
    }
    position->number = newNum;
    printf("%d %s %s", position->number, position->name, position->serName);
    fclose(fp);
}

void userNameModify(char name[], USER **userHead) {
    USER *position = userNameSearch(*userHead, name)->next;
    USER chan;
    FILE *fp = fopen("user.txt", "r+");
    char newName[20] = {0};
    printf("Please input the new name:");
    scanf("%s", newName);
    int lenSerName = strlen(position->serName);
    while (fscanf(fp, "%d%s%s", &chan.number, chan.name, chan.serName) != EOF) {
        if (strcmp(position->name, chan.name) == 0) {
            fseek(fp, -(10 + lenSerName), SEEK_CUR);
            fprintf(fp, "%s", newName);
            break;
        }
    }
    strcpy(position->name, newName);
    printf("%d %s %s", position->number, position->name, position->serName);
    fclose(fp);
}

void userSerNameMod(char serName[], USER **userHead) {
    USER *position = userSerNameSearch(*userHead, serName)->next;
    USER chan;
    FILE *fp = fopen("user.txt", "r+");
    char newSerName[20] = {0};
    int lenSerName = strlen(position->serName);
    printf("Please input the new service name:");
    scanf("%s", newSerName);
    while (fscanf(fp, "%d%s%s", &chan.number, chan.name, chan.serName) != EOF) {
        if (strcmp(position->serName, chan.serName) == 0) {
            fseek(fp, -lenSerName, SEEK_CUR);
            fprintf(fp, "%s", newSerName);
            break;
        }
        strcpy(position->serName, newSerName);
        printf("%d %s %s", position->number, position->name, position->serName);
        fclose(fp);
    }
}

USER *userModify(USER *userHead) {
    int choose;
    char name[20] = {0}, serviceName[20] = {0};
    int number;
    printf("Please choose the way:\n1.number\n2.name\n3.service name\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        printf("Please input the number:");
        scanf("%d", &number);
        userNumModify(number, &userHead);
        break;
    case 2:
        printf("Please input the name:");
        scanf("%s", name);
        userNameModify(name, &userHead);
        break;
    default:
        printf("Please input the service name:");
        scanf("%s", serviceName);
        userSerNameMod(serviceName, &userHead);
    }
    return userHead;
}

USER *userManage(USER *userHead) {
    int choose;
    userHead = userLoad(userHead);
    printf("Please input your "
           "choice:\n1:Create\n2:Delete\n3.Search\n4.Modify\n5.Exit to main "
           "menu\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
        userHead = userCreate(userHead);
        userHead = userManage(userHead);
        break;
    case 2:
        userDelete(userHead);
        userHead = userManage(userHead);
        break;
    case 3:
        userSearch(userHead);
        userHead = userManage(userHead);
        break;
    case 4:
        userHead = userModify(userHead);
        userHead = userManage(userHead);
        break;
    default:
        system("cls");
    }
    return userHead;
}

void start() {
    printf("\n*********************\n");
    printf("old community stystem\n");
    printf("*********************\n");
    printf("1.Member Management\n");
    printf("2.House Management\n");
    printf("3.Facility Management\n");
    printf("4.User Management\n");
    printf("5.Exit\n");
    printf("Please input your choose:\n");
}

void menu() {
    MEMBER *memHead;
    USER *userHead = NULL;
    FACILITY *facHead = NULL;
    HOUSE *houseHead = NULL;
    int choose;
    system("cls");
    do {
        start();
        fflush(stdin);
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            memHead = memberManage(memHead);
            break;
        case 2:
            houseHead = houseManage(houseHead);
            break;
        case 3:
            facHead = facManage(facHead);
            break;
        case 4:
            userHead = userManage(userHead);
            break;
        default:
            exit(0);
        }
    } while (1);
}

int main(void) { menu(); }
