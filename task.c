#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_NAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// User struct
struct User
{
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    union UserStatus
    {
        struct Flag
        {
            bool active;
        } flag;
        int value;
    } status;
};

// Function to register a new user
void registerUser(struct User users[], int *numUsers)
{
    if (*numUsers >= MAX_USERS)
    {
        printf("Maximum number of users reached.\n");
        return;
    }

    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    printf("Enter user status (0 for false, 1 for true): ");
    scanf("%d", &newUser.status.value);

    users[*numUsers] = newUser;
    (*numUsers)++;

    printf("User registered successfully.\n");
}

// Function to check if a user is active
bool isUserActive(struct User user)
{
    return user.status.flag.active;
}

// Function to perform user login
void loginUser(struct User users[], int numUsers)
{
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            bool isActive = isUserActive(users[i]);
            if (isActive)
            {
                printf("Login successful.\n");
                return;
            }
            else
            {
                printf("User is not active. Please contact the administrator.\n");
                return;
            }
        }
    }

    printf("Invalid username or password.\n");
}

int main()
{
    struct User users[MAX_USERS];
    int numUsers = 0;

    int choice;
    do
    {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerUser(users, &numUsers);
            break;
        case 2:
            loginUser(users, numUsers);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}