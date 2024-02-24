#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a file or directory
typedef struct Node {
    char name[100];
    struct Node *parent;
    struct Node *children;
    struct Node *nextSibling;
    int isDirectory;
} Node;

// Function prototypes
Node* createNode(const char *name, int isDirectory);
Node* findNode(Node *root, const char *path);
void listContents(Node *currentNode);
void createFile(Node *parent);
void createDirectory(Node *parent);
void deleteNode(Node *parent, const char *name);
void printTree(Node *root, int depth);

// Create a new node
Node* createNode(const char *name, int isDirectory) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->nextSibling = NULL;
    newNode->isDirectory = isDirectory;
    return newNode;
}

// Find a node in the tree given its path
Node* findNode(Node *root, const char *path) {
    if (strcmp(root->name, path) == 0)
        return root;
    Node *child = root->children;
    while (child != NULL) {
        Node *result = findNode(child, path);
        if (result != NULL)
            return result;
        child = child->nextSibling;
    }
    return NULL;
}

// List contents of a directory
void listContents(Node *currentNode) {
    if (currentNode->isDirectory) {
        printf("Contents of directory '%s':\n", currentNode->name);
        Node *child = currentNode->children;
        while (child != NULL) {
            printf("%s\n", child->name);
            child = child->nextSibling;
        }
    } else {
        printf("'%s' is not a directory.\n", currentNode->name);
    }
}

// Create a file
void createFile(Node *parent) {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    Node *fileNode = createNode(filename, 0);
    fileNode->parent = parent;

    // Add the file to the parent's list of children
    if (parent->children == NULL) {
        parent->children = fileNode;
    } else {
        Node *child = parent->children;
        while (child->nextSibling != NULL) {
            child = child->nextSibling;
        }
        child->nextSibling = fileNode;
    }
}

// Create a directory
void createDirectory(Node *parent) {
    char dirname[100];
    printf("Enter directory name: ");
    scanf("%s", dirname);
    Node *dirNode = createNode(dirname, 1);
    dirNode->parent = parent;

    // Add the directory to the parent's list of children
    if (parent->children == NULL) {
        parent->children = dirNode;
    } else {
        Node *child = parent->children;
        while (child->nextSibling != NULL) {
            child = child->nextSibling;
        }
        child->nextSibling = dirNode;
    }
}

// Delete a node (file or directory)
void deleteNode(Node *parent, const char *name) {
    Node *prev = NULL;
    Node *current = parent->children;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->nextSibling;
    }

    if (current == NULL) {
        printf("'%s' not found.\n", name);
        return;
    }

    if (prev == NULL)
        parent->children = current->nextSibling;
    else
        prev->nextSibling = current->nextSibling;

    free(current);
    printf("'%s' deleted successfully.\n", name);
}

// Print the tree structure
void printTree(Node *root, int depth) {
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%s\n", root->name);

    Node *child = root->children;
    while (child != NULL) {
        printTree(child, depth + 1);
        child = child->nextSibling;
    }
}

int main() {
    Node *root = createNode("root", 1); // root directory
    Node *currentDirectory = root;

    int choice;
    char name[100];

    do {
        printf("\nCurrent directory: %s\n", currentDirectory->name);
        printf("1. List contents\n");
        printf("2. Traverse into directory\n");
        printf("3. Create file\n");
        printf("4. Create directory\n");
        printf("5. Delete file/directory\n");
        printf("6. Print directory structure\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listContents(currentDirectory);
                break;
            case 2:
                printf("Enter directory name to traverse into: ");
                scanf("%s", name);
                Node *newDir = findNode(currentDirectory, name);
                if (newDir != NULL && newDir->isDirectory)
                    currentDirectory = newDir;
                else
                    printf("Directory not found.\n");
                break;
            case 3:
                createFile(currentDirectory);
                break;
            case 4:
                createDirectory(currentDirectory);
                break;
            case 5:
                printf("Enter name of file/directory to delete: ");
                scanf("%s", name);
                deleteNode(currentDirectory, name);
                break;
            case 6:
                printf("Directory structure:\n");
                printTree(root, 0);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}
