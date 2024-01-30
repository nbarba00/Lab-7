#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Directory {
    char name[MAX_NAME_LENGTH];
    struct Directory* subDirectories;
    struct Directory* next;
};

typedef struct Directory Directory;

Directory* createDirectory(char name[MAX_NAME_LENGTH]) {
    Directory* newDirectory = (Directory*)malloc(sizeof(Directory));
    if (!newDirectory) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newDirectory->name, name);
    newDirectory->subDirectories = NULL;
    newDirectory->next = NULL;
    return newDirectory;
}

Directory* createSubdirectory(char name[MAX_NAME_LENGTH], Directory* currentDirectory) {
    Directory* newDirectory = createDirectory(name);
    if (!newDirectory) {
        printf("New directory creation failed!\n");
        exit(EXIT_FAILURE);
    }
    newDirectory->next = currentDirectory->subDirectories;
    currentDirectory->subDirectories = newDirectory;
    return newDirectory;
}

Directory* changeDirectory(char name[MAX_NAME_LENGTH], Directory* currentDirectory) {
    Directory* subdirectory = currentDirectory->subDirectories;
    while (subdirectory != NULL) {
        if (strcmp(subdirectory->name, name) == 0) {
            return subdirectory;
        }
        subdirectory = subdirectory->next;
    }
    printf("Directory '%s' not found.\n", name);
    return currentDirectory;
}

void listDirectoryContents(Directory* currentDirectory) {
    printf("Contents of directory '%s':\n", currentDirectory->name);
    Directory* subdirectory = currentDirectory->subDirectories;
    while (subdirectory != NULL) {
        printf(" - %s\n", subdirectory->name);
        subdirectory = subdirectory->next;
    }
    if (currentDirectory->subDirectories == NULL) {
        printf("   (empty)\n");
    }
}

int main() {
    Directory headDirectory = {
        .name = {0},
        .subDirectories = NULL,
        .next = NULL
    };
    Directory* rootDirectory = createDirectory("C:");
    headDirectory.next = rootDirectory;

    Directory* currentDirectory = rootDirectory;

    while (1) {
        printf("\nMenu:\n");
        printf("1 - md (Create Directory)\n");
        printf("2 - cd dir (Change Directory)\n");
        printf("3 - cd.. (Go Up)\n");
        printf("4 - dir (List Contents)\n");
        printf("5 - exit\n");

        char choice[10];
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            createSubdirectory(directoryName, currentDirectory);
        }
        else if (strcmp(choice, "2") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            currentDirectory = changeDirectory(directoryName, currentDirectory);
        }
        else if (strcmp(choice, "3") == 0) {
            if (currentDirectory != rootDirectory) {
                // Move up one directory
                currentDirectory = currentDirectory->next;
                printf("Currently in '%s'\n", currentDirectory->name);
            }
            else {
                printf("Already in the root directory.\n");
            }
        }
        else if (strcmp(choice, "4") == 0) {
            listDirectoryContents(currentDirectory);
        }
        else if (strcmp(choice, "5") == 0) {
            printf("Exiting the program.\n");
            break;
        }
        else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    // Free allocated memory 
    free(rootDirectory);

    return 0;
}
