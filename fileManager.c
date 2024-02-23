#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100

void displayMenu();
void createFile();
void readFile();
void writeFile();
void deleteFile();
void listFiles();

int main() {
    int choice;

    while (1) {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                writeFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                listFiles();
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\nFile Management System\n");
    printf("1. Create a file\n");
    printf("2. Read a file\n");
    printf("3. Write to a file\n");
    printf("4. Delete a file\n");
    printf("5. List all files\n");
    printf("6. Exit\n");
}

void createFile() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error creating the file.\n");
        return;
    }

    fclose(file);
    printf("File '%s' created successfully.\n", filename);
}

void readFile() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    char buffer[1000];

    printf("Enter the name of the file to read: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

void writeFile() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    char data[1000];

    printf("Enter the name of the file to write: ");
    scanf("%s", filename);

    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("Enter data to write to the file (Ctrl+D to finish):\n");

    while (fgets(data, sizeof(data), stdin) != NULL) {
        fprintf(file, "%s", data);
    }

    fclose(file);
    printf("Data written to '%s' successfully.\n", filename);
}

void deleteFile() {
    char filename[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error deleting the file.\n");
    }
}

void listFiles() {
    system("ls -l");
}
