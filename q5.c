#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char **insertLine(char **lines, int *numLines, int *capacity, int index, const char *text);
char **deleteLine(char **lines, int *numLines, int *capacity, int index);
void printAllLines(char **lines, int numLines);
void freeAll(char **lines, int numLines);
char **shrinkToFit(char **lines, int numLines, int *capacity);
void saveToFile(char **lines, int numLines, const char *filename);
char **loadFromFile(char **lines, int *numLines, int *capacity, const char *filename);
int main(void) {
    int initialCapacity = 2;
    int maxLineLength = 1024;

    char **lines = malloc(initialCapacity * sizeof(char*));
    if (!lines) {
        perror("Failed to allocate memory for lines array");
        exit(EXIT_FAILURE);
    }
    int numLines = 0;
    int capacity = initialCapacity;
    int choice;
    while (1) {
        printf("\n--- Minimal Line Editor ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink to Fit\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) {
            int index;
            char buffer[1024];
            printf("Enter line index to insert at (0 to %d): ", numLines);
            if (scanf("%d", &index) != 1 || index < 0 || index > numLines) {
                fprintf(stderr, "Invalid index\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            printf("Enter line text: ");
            if (!fgets(buffer, maxLineLength, stdin)) {
                fprintf(stderr, "Failed to read line\n");
                continue;
            }
            buffer[strcspn(buffer, "\n")] = '\0';

            lines = insertLine(lines, &numLines, &capacity, index, buffer);
        }
        else if (choice == 2) {
            int index;
            printf("Enter line index to delete (0 to %d): ", numLines-1);
            if (scanf("%d", &index) != 1 || index < 0 || index >= numLines) {
                fprintf(stderr, "Invalid index\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            lines = deleteLine(lines, &numLines, &capacity, index);
        }
        else if (choice == 3) {
            printAllLines(lines, numLines);
        }
        else if (choice == 4) {
            lines = shrinkToFit(lines, numLines, &capacity);
            printf("Shrunk array to fit %d lines.\n", numLines);
        }
        else if (choice == 5) {
            char filename[256];
            printf("Enter filename to save: ");
            if (!fgets(filename, 256, stdin)) continue;
            filename[strcspn(filename, "\n")] = '\0';
            saveToFile(lines, numLines, filename);
        }
        else if (choice == 6) {
            char filename[256];
            printf("Enter filename to load: ");
            if (!fgets(filename, 256, stdin)) continue;
            filename[strcspn(filename, "\n")] = '\0';
            lines = loadFromFile(lines, &numLines, &capacity, filename);
        }
        else if (choice == 7) {
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }
    freeAll(lines, numLines);
    return 0;
}

char **insertLine(char **lines, int *numLines, int *capacity, int index, const char *text) {
    if (*numLines >= *capacity) {
        int newCapacity = (*capacity) * 2;
        char **temp = realloc(lines, newCapacity * sizeof(char*));
        if (!temp) {
            perror("Memory allocation failed");
            return lines;
        }
        lines = temp;
        *capacity = newCapacity;
    }

    int i;
    for (i = *numLines; i > index; i--) {
        lines[i] = lines[i-1];
    }
    lines[index] = malloc(strlen(text) + 1);
    if (!lines[index]) {
        perror("Memory allocation failed");
        return lines;
    }
    strcpy(lines[index], text);
    (*numLines)++;
    return lines;
}

char **deleteLine(char **lines, int *numLines, int *capacity, int index) {
    free(lines[index]);
    int i;
    for (i = index; i < *numLines - 1; i++) {
        lines[i] = lines[i+1];
    }
    (*numLines)--;
    return lines;
}

void printAllLines(char **lines, int numLines) {
    printf("\n--- Text Buffer ---\n");
    int i;
    for (i = 0; i < numLines; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void freeAll(char **lines, int numLines) {
    int i;
    for (i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);
}

char **shrinkToFit(char **lines, int numLines, int *capacity) {
    if (numLines == 0) {
        free(lines);
        lines = NULL;
        *capacity = 0;
        return lines;
    }
    char **temp = realloc(lines, numLines * sizeof(char*));
    if (!temp) {
        perror("Shrink memory failed");
        return lines;
    }
    *capacity = numLines;
    return temp;
}

void saveToFile(char **lines, int numLines, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File open failed");
        return;
    }
    int i;
    for (i = 0; i < numLines; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
    printf("Saved %d lines to %s\n", numLines, filename);
}

char **loadFromFile(char **lines, int *numLines, int *capacity, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return lines;
    }
    freeAll(lines, *numLines);
    lines = malloc(2 * sizeof(char*));
    if (!lines) {
        perror("Memory allocation failed");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    *numLines = 0;
    *capacity = 2;
    char buffer[1024];
    while (fgets(buffer, 1024, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        lines = insertLine(lines, numLines, capacity, *numLines, buffer);
    }
    fclose(fp);
    printf("Loaded %d lines from %s\n", *numLines, filename);
    return lines;
}

