#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
    int uniqueId;
    int popularityScore;
};

struct Shelf {
    int capacity;
    int filled;
    struct Book *book;
};

int addBook(struct Shelf *shelf, int x, int y);
int accessBook(struct Shelf *shelf, int x);

int main() {
    char operation[10];
    int x, y, numOfOperations, capacity;
    scanf("%d %d", &capacity, &numOfOperations);
    struct Shelf shelf;
    shelf.capacity = capacity;
    shelf.filled = 0;
    shelf.book = malloc(sizeof(struct Book) * capacity);
    for (int i = 0; i < numOfOperations; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "ADD") == 0) {
            scanf("%d %d", &x, &y);
            addBook(&shelf, x, y);
        } else if (strcmp(operation, "ACCESS") == 0) {
            scanf("%d", &x);
            accessBook(&shelf, x);
        } else {
            printf("Invalid operation\n");
            i--;
        }
    }

    free(shelf.book);
    return 0;
}
int addBook(struct Shelf *shelf, int x, int y) {
    for (int i = 0; i < shelf->filled; i++) {
        if (shelf->book[i].uniqueId == x) {
            shelf->book[i].popularityScore = y;
            return 0;
        }
    }
    if (shelf->filled < shelf->capacity) {
        shelf->book[shelf->filled].uniqueId = x;
        shelf->book[shelf->filled].popularityScore = y;
        shelf->filled++;
        return 0;
    }
    int minIndex = 0;
    for (int i = 1; i < shelf->capacity; i++) {
        if (shelf->book[i].popularityScore < shelf->book[minIndex].popularityScore) {
            minIndex = i;
        }
    }
    shelf->book[minIndex].uniqueId = x;
    shelf->book[minIndex].popularityScore = y;

    return 0;
}
int accessBook(struct Shelf *shelf, int x) {
    for (int i = 0; i < shelf->filled; i++) {
        if (shelf->book[i].uniqueId == x) {
            printf("%d\n", shelf->book[i].popularityScore);
            return 0;
        }
    }
    printf("-1\n");
    return -1;
}
