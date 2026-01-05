/*
 Filename  : login.c
 Program   : User account management system with creation, deletion, editing, and login authentication
 Input     : User menu selections (1-5), usernames (6-9 chars), passwords (8-14 chars with requirements)
 Output    : Account operations feedback, login status, lockout warnings, user list display
 Author    : Akram, M. Issmaeel
 Version   : V01 - 06.01.2026
 */

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// GLOBAL VARIABLES
#define MAX_USERNAMES 121
#define USERNAME_SIZE 10
#define PASSWORD_SIZE 15
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

// FUNCTION DECLARATIONS
void empty_array();
int check_task();
int user_creator(int user_count, int *accounts);
void username_creator(int user_count);
int password_creator(int user_count);
int delete_user(int *accounts);
int edit_user(int *accounts);
int login();
int compare_username();
int compare_password(int index, int attempts);
int print_values(int a);
int time_locker(int index);

// Input: None
// Output: Runs main menu loop, manages account operations until exit
int main()
{
    empty_array();
    int accounts = 0; // Tracks total number of active accounts

    while (1)
    {
        print_values(accounts);

        int task_number = check_task();

        // Create new user if slots available
        if ((task_number == 1) && (accounts < MAX_USERNAMES))
        {
            printf("[ %d Accounts left ]\n", MAX_USERNAMES - accounts - 1);
            
            // Find first free slot
            for (int i = 0; i < MAX_USERNAMES; i++)
            {
                if (array[i].isFree == true)
                {
                    // Increment counter only on successful creation
                    if (user_creator(i, &accounts) == 1)
                    {
                        accounts++;
                    }
                    break;
                }
            }
        }
        else if ((task_number == 1) && (accounts >= MAX_USERNAMES))
        {
            printf("Account limit has been reached\n");
        }
        if (task_number == 2)
        {
            delete_user(&accounts);
        }
        if (task_number == 3)
        {
            edit_user(&accounts);
        }
        if (task_number == 4)
        {
            login();
        }
        if (task_number == 5)
        {
            print_values(accounts);
            printf("You have exited the terminal\nExiting...");
            return 0;
        }
    }
}

// Input: None
// Output: Returns user's menu selection (1-5)
int check_task()
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
        ; // Clear input buffer
    return task;
}

// Input: user_count - index in array for new username
// Output: Stores validated username (6-9 chars, first uppercase, rest lowercase/digits)
void username_creator(int user_count)
{
    printf("Enter a new username: ");
    int i;
    
    // Read username character by character
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].username[i] = c;
    }
    array[user_count].username[i] = '\0';

    // Validate minimum length (6 characters)
    if (i < 6)
    {
        printf("The username is too small!\n");
        username_creator(user_count);
        return;
    }

    // Validate first character is uppercase
    if ((array[user_count].username[0] < 'A') || (array[user_count].username[0] > 'Z'))
    {
        printf("The first letter has to be CAPITAL!\n");
        while (getchar() != '\n')
            ; // Clear buffer on error
        username_creator(user_count);
        return;
    }

    // Validate remaining characters are lowercase or digits
    for (i = 1; array[user_count].username[i] != '\0' && i < USERNAME_SIZE - 1; i++)
    {
        char c;
        c = array[user_count].username[i];
        if (((c < 'a') || (c > 'z')) && ((c < '0') || (c > '9')))
        {
            printf("All characters except the first have to be small or numbers!\n");
            while (getchar() != '\n')
                ; // Clear buffer on error
            username_creator(user_count);
            return;
        }
    }
}

// Input: user_count - index in array for new password
// Output: Returns 1 if valid (8-14 chars with uppercase, lowercase, digit), 0 otherwise
int password_creator(int user_count)
{
    int i;
    
    // Read password character by character
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        array[user_count].password[i] = c;
    }
    array[user_count].password[i] = '\0';

    // Check if password exceeds maximum length
    if (i == PASSWORD_SIZE - 1)
    {
        char c = getchar();
        if (c != '\n')
        {
            printf("The password is too large!\n");
            // Clear password data on failure
            for (int j = 0; j < PASSWORD_SIZE; j++)
                array[user_count].password[j] = 0;
            while (getchar() != '\n')
                ; // Clear remaining input
            return 0;
        }
    }

    // Validate minimum length (8 characters)
    if (i < 8)
    {
        printf("The password is too small!\n");
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[user_count].password[j] = 0;
        return 0;
    }

    // Check password contains required character types
    bool capital_letter = false;
    bool small_letter = false;
    bool number = false;
    for (i = 0; array[user_count].password[i] != '\0' && i < PASSWORD_SIZE - 1; i++)
    {
        char c;
        c = array[user_count].password[i];
        if ((c >= 'A') && (c <= 'Z'))
            capital_letter = true;
        if ((c >= 'a') && (c <= 'z'))
            small_letter = true;
        if ((c >= '0') && (c <= '9'))
            number = true;
    }
    
    // Validate all three character types are present
    if (!(capital_letter && small_letter && number))
    {
        printf("You need at least one capital letter, one small letter and one number!\n");
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[user_count].password[j] = 0;
        return 0;
    }
    return 1;
}

// Input: user_count - index for new user, accounts - pointer to account counter
// Output: Returns 1 if user created successfully with matching passwords, 0 on failure
int user_creator(int user_count, int *accounts)
{
    // Mark slot as occupied
    array[user_count].isFree = false;
    array[user_count].isLocked = false;

    username_creator(user_count);

    // First password entry
    printf("Enter a new password: ");
    int a = password_creator(user_count);
    if (a == 0)
    {
        printf("Wrong input, read above, please restart!\n");
        // Reset slot on failure
        array[user_count].isFree = true;
        array[user_count].isLocked = false;
        for (int j = 0; j < USERNAME_SIZE; j++)
            array[user_count].username[j] = 0;
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[user_count].password[j] = 0;
        return 0;
    }

    // Password confirmation (stored in last array slot as temporary buffer)
    printf("Enter a new password again: ");
    password_creator(MAX_USERNAMES - 1);

    // Compare both password entries
    for (int i = 0; i < PASSWORD_SIZE; i++)
    {
        if (array[user_count].password[i] != array[MAX_USERNAMES - 1].password[i])
        {
            printf("You entered the wrong password!\n");
            // Clean up failed account creation
            array[user_count].isFree = true;
            array[user_count].isLocked = false;
            for (int j = 0; j < USERNAME_SIZE; j++)
                array[user_count].username[j] = 0;
            for (int j = 0; j < PASSWORD_SIZE; j++)
                array[user_count].password[j] = 0;
            for (int j = 0; j < PASSWORD_SIZE; j++)
                array[MAX_USERNAMES - 1].password[j] = 0;
            return 0;
        }
    }

    return 1;
}

// Input: None, prompts user for username
// Output: Returns array index if username found, -1 if not found
int compare_username()
{
    char temp_username[USERNAME_SIZE];
    printf("Enter your username: ");
    int i;
    
    // Read username input
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        temp_username[i] = c;
    }
    temp_username[i] = '\0';

    // Search through all occupied slots
    for (i = 0; i < MAX_USERNAMES; i++)
    {
        if (array[i].isFree == false)
        {
            int comparison = 1;
            int j;
            
            // Compare character by character
            for (j = 0; j < USERNAME_SIZE - 1; j++)
            {
                if (array[i].username[j] != temp_username[j])
                {
                    comparison = 0;
                    break;
                }
                // Check for end of string match
                if (temp_username[j] == '\0')
                    return i;
            }
            if (comparison == 1)
                return i;
        }
    }
    return -1; // Username not found
}

// Input: index - user array position, attempts - failed login count
// Output: Returns index if password matches, -1 if failed/locked (locks after 3 attempts)
int compare_password(int index, int attempts)
{
    // Lock account after 3 failed attempts
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
    // Read password input
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        temp_password[i] = c;
    }
    temp_password[i] = '\0';

    int match = 1;

    // Compare entered password with stored password
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        if (array[index].password[i] != temp_password[i])
        {
            match = 0;
            break;
        }
        // Check for end of string match
        if (temp_password[i] == '\0')
            break;
    }
    if (match)
        return index;

    // Recursively retry with incremented attempt counter
    return compare_password(index, attempts + 1);
}

// Input: accounts - pointer to account counter
// Output: Returns 1 if user deleted successfully after authentication, 0 on failure
int delete_user(int *accounts)
{
    // Verify username exists
    int user_index = compare_username();
    if (user_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    // Verify password matches
    int pass_index = compare_password(user_index, 0);

    if (user_index != pass_index)
    {
        printf("You entered the wrong password!\n");
        return 0;
    }

    printf("User |%s| is being deleted.\n", array[user_index].username);

    // Clear user data and mark slot as free
    array[user_index].isFree = true;
    for (int j = 0; j < USERNAME_SIZE; j++)
        array[user_index].username[j] = 0;
    for (int j = 0; j < PASSWORD_SIZE; j++)
        array[user_index].password[j] = 0;
    (*accounts)--; // Decrement account counter
    printf("The user has been deleted.\n");
    return 1;
}

// Input: accounts - pointer to account counter
// Output: Returns 1 if user edited successfully after authentication, 0 on failure
int edit_user(int *accounts)
{
    // Verify username exists
    int username_index = compare_username();

    if (username_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    // Verify password matches
    int password_index = compare_password(username_index, 0);

    if (password_index == -1)
    {
        printf("Wrong password!\n");
        return 0;
    }

    printf("Enter your new username and password below:\n");
    
    // Preserve slot state in case of failure
    int old_state = array[username_index].isFree;
    
    // Attempt to create new credentials
    if (user_creator(username_index, accounts) == 0)
    {
        array[username_index].isFree = old_state; // Restore state on failure
        return 0;
    }
    
    return 1;
}

// Input: a - current account count
// Output: Prints list of registered usernames, returns 0
int print_values(int a)
{
    printf("------------------------------------\n");
    if (a == 0)
        return 0;
    printf("These are the registered users: \n");
    
    // Display all active users
    for (int i = 0; i < MAX_USERNAMES; i++)
        if (array[i].isFree == false)
            printf("User %d: %s\n", i + 1, array[i].username);
    printf("------------------------------------\n");
}

// Input: None
// Output: Initializes all user slots to empty state with cleared data
void empty_array()
{
    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        array[i].isFree = true;
        array[i].isLocked = false;
        
        // Zero out all username characters
        for (int j = 0; j < USERNAME_SIZE; j++)
            array[i].username[j] = 0;
            
        // Zero out all password characters
        for (int j = 0; j < PASSWORD_SIZE; j++)
            array[i].password[j] = 0;
    }
}

// Input: index - user to lock
// Output: Locks account for LOCK_OUT_TIME seconds, returns 0
int time_locker(int index)
{
    array[index].isLocked = true;

    // Calculate lockout end time
    time_t start = time(NULL);
    time_t end = start + LOCK_OUT_TIME;
    
    // Busy wait until lockout expires
    while (time(NULL) < end)
    {
    }

    array[index].isLocked = false;
    printf("Timer complete\n");
    return 0;
}

// Input: None, prompts for username and password
// Output: Returns 0, prints login success or failure message
int login()
{
    // Verify username exists
    int a = compare_username();
    if (a == -1)
    {
        printf("User not found!\n");
        return 0;
    }
    
    // Verify password matches
    int b = compare_password(a, 0);
    if (a == b)
        printf("Successfully logged in!\n");
    else
        printf("The account does not exist!\n");
}