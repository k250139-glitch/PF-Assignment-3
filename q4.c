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
    struct Book *books;
};

int findBook(struct Shelf *shelf, int id);
void addBook(struct Shelf *shelf, int id, int score);
void accessBook(struct Shelf *shelf, int id);

int main(void) {
    int capacity, operations;

    printf("Enter shelf capacity and number of operations: ");
    scanf("%d %d", &capacity, &operations);

    struct Shelf shelf;
    shelf.capacity = capacity;
    shelf.filled = 0;

    shelf.books = malloc(sizeof(struct Book) * capacity);
    if (shelf.books == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    char op[10];
    int id, score;

    for (int i = 0; i < operations; i++) {
        printf("\nEnter operation (ADD or ACCESS): ");
        scanf("%9s", op);

        if (strcmp(op, "ADD") == 0) {
            printf("Enter book ID and popularity score: ");
            scanf("%d %d", &id, &score);
            addBook(&shelf, id, score);
            printf("Book with ID %d added/updated successfully.\n", id);
        }
        else if (strcmp(op, "ACCESS") == 0) {
            printf("Enter book ID to access: ");
            scanf("%d", &id);
            accessBook(&shelf, id);
        }
        else {
            printf("Invalid operation. Please enter ADD or ACCESS.\n");
            i--;
        }
    }

    free(shelf.books);
    printf("\nAll operations completed. Goodbye!\n");
    return 0;
}

int findBook(struct Shelf *shelf, int id) {
    for (int i = 0; i < shelf->filled; i++) {
        if (shelf->books[i].uniqueId == id)
            return i;
    }
    return -1;
}

void addBook(struct Shelf *shelf, int id, int score) {
    int index = findBook(shelf, id);

    if (index != -1) {
        shelf->books[index].popularityScore = score;
        return;
    }

    if (shelf->filled < shelf->capacity) {
        shelf->books[shelf->filled].uniqueId = id;
        shelf->books[shelf->filled].popularityScore = score;
        shelf->filled++;
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < shelf->capacity; i++) {
        if (shelf->books[i].popularityScore < shelf->books[minIndex].popularityScore) {
            minIndex = i;
        }
    }

    printf("Shelf full! Evicting book with ID %d (popularity %d).\n",
           shelf->books[minIndex].uniqueId, shelf->books[minIndex].popularityScore);

    shelf->books[minIndex].uniqueId = id;
    shelf->books[minIndex].popularityScore = score;
}

void accessBook(struct Shelf *shelf, int id) {
    int index = findBook(shelf, id);

    if (index != -1) {
        printf("Book ID %d has popularity score: %d\n", id, shelf->books[index].popularityScore);
    } else {
        printf("Book ID %d not found on the shelf.\n", id);
    }
}
