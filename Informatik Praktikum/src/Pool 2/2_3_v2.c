// LIBRARIES
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// GLOBAL VARIABLES
#define MAX_USERNAMES 3
#define USERNAME_SIZE 9
#define PASSWORD_SIZE 14
#define LOCK_OUT_TIME 5

// GLOBAL STRUCTS
typedef struct userBase
{
    bool isFree;
    bool isLocked;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} user;

// GLOBAL ARRAYS
user array[MAX_USERNAMES];

// FUNCTIONS

// Empties the array every time the program starts
void empty_username_array();

// Asks user which task to perform before each iteration
int check_for_task();

// Calls the function to create a username with password
int user_creator_caller(int *accounts);
// Creates a username with password
int user_creator(int user_count);

// Checks for validity of user data which needs to be deleted
int deletion_function(int *accounts);
// Checks for validity of user data which needs to be changed
int edit_function();

// Used in deletion and editing to determine existence of a user
int search_username_function();
// Called by search_username_function() to check for correct password
int compare_password_function(int index, int attempts);

// Prints the usernames everytime the program does a task
int print_values(int a);
// Puts the tagged users into a timer
int time_locker(int index);

// Checks whether user exists
int login();

int main()
{
    empty_username_array();
    int accounts = 0;

    while (1)
    {
        print_values(accounts);

        int task_number = check_for_task();

        if ((task_number == 1) && (accounts < MAX_USERNAMES)) // Create a new user
        {
            printf("[ %d Accounts left ]\n", MAX_USERNAMES - accounts);
            user_creator_caller(&accounts);
        }
        else if ((task_number == 1) && (!accounts < MAX_USERNAMES))
        {
            printf("User limit has been reached\n");
        }
        if (task_number == 2) // Delete a user
        {
            deletion_function(&accounts);
            accounts--;
        }
        if (task_number == 3) // Edit a user
        {
            edit_function();
        }
        if (task_number == 4) // Log into the program
        {
            login();
        }
        if (task_number == 5) // Exit the program
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

int check_for_task()
{
    int task;
    printf("[ 1 - New user    ]\n"
           "[ 2 - Delete user ]\n"
           "[ 3 - Edit user   ]\n"
           "[ 4 - Check login ]\n"
           "[ 5 - Exit        ]\n"
           "[ Enter here  -  ");
    scanf("%d", &task);
    while (getchar() != '\n')
        ;
    return task;
}

int user_creator(int user_count)
{
    array[user_count].isFree = false;
    array[user_count].isLocked = false;

    // Create a username
    printf("Enter a new username: ");
    int i;
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].username[i] = c;
    }
    array[user_count].username[i] = '\0';

    // Create a password
    printf("Enter a new password: ");
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].password[i] = c;
    }
    array[user_count].password[i] = '\0';
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
                {
                    return i;
                }
            }
            if (comparison == 1)
            {
                return i;
            }
        }
    }
    return -1;
}

// compare pwd
int compare_password_function(int index, int attempts)
{
    if (attempts >= 3)
    {
        printf("Too many wrong tries, you are now locked for 2 minutes!\n");
        time_locker(index);
        return -1;
    }

    if (array[index].isFree)
        return -1;

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

   

    for (int j = 0; j < i; j++)
    {                  // j is size of password, you just go back and overwrite on screen
        putchar('\b'); // move back
        putchar('*');  // overwrite
    }

    int match = 1;

    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        if (array[index].password[i] != temp_password[i])
        {
            match = 0;
            break;
        }
        if (temp_password[i] == '\0')
            break;
    }
    if (match)
        return index;

    return compare_password_function(index, attempts + 1);
}

int deletion_function(int *accounts)
{
    int user_index = search_username_function();
    if (user_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    int pass_index = compare_password_function(user_index, 0);

    while (user_index != pass_index)
    {
        printf("You entered the wrong password!\n");
        return 0;
    }

    printf("User |%s| is being deleted.\n", array[user_index].username);

    array[user_index].isFree = true;
    for (int j = 0; j < USERNAME_SIZE; j++)
        array[user_index].username[j] = 0;
    for (int j = 0; j < PASSWORD_SIZE; j++)
        array[user_index].password[j] = 0;
    (*accounts)--;
    printf("The user has been deleted.\n");
    return 1;
}

int edit_function()
{
    int username_index = search_username_function();

    if (username_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    int password_index = compare_password_function(username_index, 0);

    if (password_index == -1)
    {
        printf("Wrong password!\n");
        return 0;
    }

    printf("Enter your new username and password below:\n");
    user_creator(username_index);
}

int print_values(int a)
{
    printf("------------------------------------\n");

    if (a == 0)
        return 0;
    printf("These are the available users: \n");
    for (int i = 0; i < MAX_USERNAMES; i++)
        if (array[i].isFree == false)
            printf("User %d: %s\n", i + 1, array[i].username);

    printf("------------------------------------\n");
}

int user_creator_caller(int *accounts)
{
    for (int i = 0; i < MAX_USERNAMES; i++)
        if (array[i].isFree == true)
        {
            user_creator(i);
            break;
        }
    (*accounts)++;
}

void empty_username_array()
{
    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        array[i].isFree = true;
        array[i].isLocked = false;
        for (int j = 0; j < USERNAME_SIZE; j++)
            array[i].username[j] = 0;
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[i].password[j] = 0;
    }
}

int time_locker(int index)
{
    array[index].isLocked = true;

    time_t start = time(NULL);
    time_t end = start + LOCK_OUT_TIME;
    while (time(NULL) < end)
    {
        // Wait
    }

    array[index].isLocked = false;
    printf("Timer complete\n");
    return 0;
}

int login()
{
    int a = search_username_function();
    int b = compare_password_function(a, 0);
    if (a == b)
        printf("The user you entered exists!\n");
    else
        printf("The account does not exist!\n");
}