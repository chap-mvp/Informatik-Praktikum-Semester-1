// LIBRARIES
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// GLOBAL VARIABLES
#define MAX_USERNAMES 5
#define USERNAME_SIZE 9
#define PASSWORD_SIZE 14

// GLOBAL STRUCTS
typedef struct userBase
{
    bool isFree;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} user;

// GLOBAL ARRAYS
user array[MAX_USERNAMES];

// FUNCTIONS

user insertion_function(int user_count);
int search_username_function();
int search_password_function(int index);
int deletion_function();
int edit_function();

int main()
{
    int user_count = 0;
    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        array[i].isFree = true;
        for (int j = 0; j < USERNAME_SIZE; j++)
            array[i].username[j] = 0;
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[i].password[j] = 0;
    }

    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        printf("User %d: %s\n", i + 1, array[i].username);
    }

    while (1)
    {
        int task;
        printf("Press 1 to create a new user\nPress 2 to delete a user\nPress 3 to edit a user\nPress 4 to end the program\n");
        scanf("%d", &task);
        // Flushing the leftover newline character in input buffer
        while (getchar() != '\n')
            ;

        int counter = 0;
        if ((task == 1) && (counter < MAX_USERNAMES)) // Create a new user
        {
            for (int i = 0; i < MAX_USERNAMES; i++)
                if (array[i].isFree == true)
                {
                    array[i] = insertion_function(i);
                    counter++;
                    break;
                }
        }
        if (task == 2) // Delete a user
        {
            deletion_function();
            for (int i = 0; i < MAX_USERNAMES; i++)
            {
                if (array[i].isFree == false)
                    printf("User %d: %s\n", i + 1, array[i].username);
                else
                    i--;
            }
        }
        if (task == 3) // Edit a user
        {
            edit_function();
        }
        if (task == 4) // Log into the program
        {
        }
        if (task == 5) // Edit a user
        {
            for (int i = 0; i < MAX_USERNAMES; i++)
            {
                printf("User %d: %s\n", i + 1, array[i].username);
            }
            printf("You have exited the terminal\nExiting...");
            return 0;
        }
    }
}

user insertion_function(int user_count)
{
    array[user_count].isFree = false;

    printf("Enter a username: ");
    int i;
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].username[i] = c;
    }
    array[user_count].username[i] = '\0';

    printf("Enter a password: ");
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].password[i] = c;
    }
    array[user_count].password[i] = '\0';

    return array[user_count];
}

int search_username_function()
{
    char temp_username[USERNAME_SIZE];
    printf("Enter your username: ");
    int i;
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        temp_username[i] = c;
    }
    temp_username[i] = '\0';

    for (i = 0; i < MAX_USERNAMES; i++)
    {
        if (array[i].isFree == false)
        {
            int comparison = 1;
            int j;
            for (j = 0; j < USERNAME_SIZE - 1; j++)
            {
                if (array[i].username[j] != temp_username[j])
                {
                    comparison = 0;
                    break;
                }
                if (temp_username[j] == '\0')
                    return i;
            }
            if (comparison == 1)
            {
                return i;
            }
        }
    }
    return -1;
}

int search_password_function(int index)
{
    char temp_password[PASSWORD_SIZE];
    printf("Enter your password: ");
    int i;
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        temp_password[i] = c;
    }
    temp_password[i] = '\0';

    for (i = index; i < index + 1; i++)
    {
        if (array[i].isFree == false)
        {
            int comparison = 1;
            int j;
            for (j = 0; j < PASSWORD_SIZE - 1; j++)
            {
                if (array[i].password[j] != temp_password[j])
                {
                    comparison = 0;
                    break;
                }
                if (temp_password[j] == '\0')
                    return i;
            }
            if (comparison == 1)
            {
                return i;
            }
        }
    }
    return -1;
}

int deletion_function()
{
    int index = search_username_function();

    if (index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    array[index].isFree = true;
    for (int j = 0; j < USERNAME_SIZE; j++)
        array[index].username[j] = 0;
    for (int j = 0; j < PASSWORD_SIZE; j++)
        array[index].password[j] = 0;
    return 1;
}

int edit_function()
{
    int username_index = search_username_function();
    int t = 0;

    if (username_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    int password_index = search_password_function(username_index);

    if (password_index == -1)
    {
        printf("Wrong password!\n");
        return 0;
    }

    printf("Enter your new username and password below:\n");
    insertion_function(username_index);
}