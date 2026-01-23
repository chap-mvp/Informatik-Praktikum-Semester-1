/*
 Filename  : login.c
 Program   : User account management system with creation, deletion, editing, and login authentication
 Input     : There are no input parameters which are used in main
 Output    : The return value is always 0
 Author    : Akram, M. Issmaeel
 Version   : V02 - 13.01.2026
 ChangeLog : user account_storage[] shifted from global into main, comments added on all function about their purpose, password lock logic changed to time comparison instead of locking he whole program, changed function names to be clearer and variables name to be more consistent among functions
 */

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// GLOBAL VARIABLES
#define MAX_USERNAMES 121
#define USERNAME_SIZE 9 + 1
#define PASSWORD_SIZE 14 + 1
#define LOCK_OUT_TIME 120

// GLOBAL STRUCTS
typedef struct userBase
{
    bool isFree;
    time_t isLocked;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} user;

// FUNCTION DECLARATIONS
void clear_user_account_storage(user *account_storage);
int task_selection_menu();

int validate_username(user *account_storage, int index);
int validate_password(user *account_storage, int index);
int create_user_account(user *account_storage, int index, int *accounts);

int verify_username(user *account_storage);
int verify_password(user *account_storage, int index, int attempts);
int account_locker(user *account_storage, int index);

int delete_user_account(user *account_storage, int *accounts);
int update_user_credentials(user *account_storage, int *accounts);
int authenticate_user(user *account_storage);

int display_registered_users(user *account_storage, int accounts);

// Input: None
// Output: Runs main menu loop, manages account operations until exit
int main()
{
    user account_storage[MAX_USERNAMES];
    clear_user_account_storage(account_storage);
    int accounts = 0; // Tracks total number of active accounts

    while (1)
    {
        time_t current_time = time(NULL);
        display_registered_users(account_storage, accounts);

        int task_number = task_selection_menu();

        // Create new user if slots available
        if ((task_number == 1) && (accounts < MAX_USERNAMES - 1))
        {
            printf("[ %d Accounts left ]\n", MAX_USERNAMES - 1 - accounts);

            // Find first free slot
            for (int i = 0; i < MAX_USERNAMES; i++)
            {
                if (account_storage[i].isFree == true)
                {
                    // Increment counter only on successful creation
                    if (create_user_account(account_storage, i, &accounts) == 1)
                    {
                        accounts++;
                    }
                    break;
                }
            }
        }
        else if ((task_number == 1) && (accounts == MAX_USERNAMES - 1))
        {
            printf("Account limit has been reached\n");
        }
        if (task_number == 2)
        {
            delete_user_account(account_storage, &accounts);
        }
        if (task_number == 3)
        {
            update_user_credentials(account_storage, &accounts);
        }
        if (task_number == 4)
        {
            authenticate_user(account_storage);
        }
        if (task_number == 5)
        {
            display_registered_users(account_storage, accounts);
            printf("You have exited the terminal\nExiting...\n");
            return 0;
        }
    }
}

// Input: account_storage
// Output: Initializes all user slots to empty state with cleared data
// Initializes the user account_storage by marking all slots free, unlocked, and clearing credentials
void clear_user_account_storage(user *account_storage)
{
    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        account_storage[i].isFree = true;
        account_storage[i].isLocked = time(NULL);

        // Zero out all username characters
        for (int j = 0; j < USERNAME_SIZE; j++)
            account_storage[i].username[j] = 0;

        // Zero out all password charactersy
        for (int j = 0; j < PASSWORD_SIZE; j++)
            account_storage[i].password[j] = 0;
    }
}

// Input: None
// Output: Returns user's menu selection (1-5)
// Displays the main menu and returns the selected task number
int task_selection_menu()
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

// Input: index - index in account_storage for new username
// Output: Stores validated username (6-9 chars, first uppercase, rest lowercase/digits)
// Reads, validates, and stores a unique username according to defined format rules
int validate_username(user *account_storage, int index)
{
    int i;

    // Read username character by character
    for (i = 0; i < USERNAME_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        account_storage[index].username[i] = c;
    }
    account_storage[index].username[i] = '\0';

    // Check if username exceeds maximum length
    if (i == USERNAME_SIZE - 1)
    {
        char c = getchar();
        if (c != '\n')
        {
            printf("The username larger than 9 characters!\n");
            return 0;
        }
    }

    // Validate minimum length (6 characters)
    if (i < 6)
    {
        printf("The username smaller than 6 letters!\n");
        return 0;
    }

    // Validate first character is uppercase
    if ((account_storage[index].username[0] < 'A') || (account_storage[index].username[0] > 'Z'))
    {
        printf("The first letter has to be CAPITAL!\n");
        return 0;
    }

    // Validate remaining characters are lowercase or digits
    for (i = 1; account_storage[index].username[i] != '\0' && i < USERNAME_SIZE - 1; i++)
    {
        char c;
        c = account_storage[index].username[i];
        if (((c < 'a') || (c > 'z')) && ((c < '0') || (c > '9')))
        {
            printf("All characters except the first have to be small or numbers!\n");
            return 0;
        }
    }

    for (int i = 0; i < MAX_USERNAMES; i++)
    {
        int user_name_comparison_counter = 0;
        for (int j = 0; j < USERNAME_SIZE; j++)
        {

            if (account_storage[i].isFree == true)
                break;
            if (account_storage[i].username[j] == account_storage[index].username[j])
            {
                user_name_comparison_counter++;
                if (i == index)
                    continue;
            }
            if (user_name_comparison_counter == USERNAME_SIZE)
            {
                // Clean up failed account creation
                account_storage[index].isFree = true;
                for (int j = 0; j < USERNAME_SIZE; j++)
                    account_storage[index].username[j] = 0;
                printf("The username already exists!\n");
                return 0;
            }
        }
    }
    return 1;
}

// Input: index - index in account_storage for new password
// Output: Returns 1 if valid (8-14 chars with uppercase, lowercase, digit), 0 otherwise
// Reads, validates, and stores a password meeting length and character requirements
int validate_password(user *account_storage, int index)
{
    int i;
    // Read password character by character
    for (i = 0; i < PASSWORD_SIZE - 1; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;
        account_storage[index].password[i] = c;
    }
    account_storage[index].password[i] = '\0';

    // Check if password exceeds maximum length
    if (i == PASSWORD_SIZE - 1)
    {
        char c = getchar();
        if (c != '\n')
        {
            printf("The password is larger than 14 characters!!\n");
            return 0;
        }
    }

    // Validate minimum length (8 characters)
    if (i < 8)
    {
        printf("The password is less than 8 characters!\n");
        return 0;
    }

    // Check password contains required character types
    bool capital_letter = false;
    bool small_letter = false;
    bool number = false;
    for (i = 0; account_storage[index].password[i] != '\0' && i < PASSWORD_SIZE - 1; i++)
    {
        char c;
        c = account_storage[index].password[i];
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
        return 0;
    }
    return 1;
}

// Input: index - index for new user, accounts - pointer to account counter
// Output: Returns 1 if user created successfully with matching passwords, 0 on failure
// Creates a new user by setting username and password with confirmation and validation
int create_user_account(user *account_storage, int index, int *accounts)
{
    // Mark slot as occupied
    account_storage[index].isFree = false;

    printf("====================================\nUSERNAME RULES: \n1. Can only consist of letters!\n2. First letter has to be capital!\n3. No other letter can be capital!\n4. Length between 6 and 9 characters! \n====================================\n");

    printf("Enter a new username: ");
    if (validate_username(account_storage, index) != 1)
    {
        // Reset slot on failure
        account_storage[index].isFree = true;
        for (int j = 0; j < USERNAME_SIZE; j++)
            account_storage[index].username[j] = 0;
        return 0;
    }

    printf("====================================\nPASSWORD RULES: \n1. At least 1 capital letter!\n2- At least 1 non-capital letter!\n3. At least 1 number!\n4. Length between 8 and 14 characters! \n====================================\n");
    // First password entry
    printf("Enter a new password: ");
    if (validate_password(account_storage, index) != 1)
    {
        // Reset slot on failure
        account_storage[index].isFree = true;
        for (int j = 0; j < USERNAME_SIZE; j++)
            account_storage[index].username[j] = 0;
        for (int j = 0; j < PASSWORD_SIZE; j++)
            account_storage[index].password[j] = 0;
        return 0;
    }

    // Password confirmation (stored in last account_storage slot as temporary buffer)
    printf("Enter a new password again: ");
    validate_password(account_storage, MAX_USERNAMES - 1);

    // Compare both password entries
    for (int i = 0; i < PASSWORD_SIZE; i++)
    {
        if (account_storage[index].password[i] != account_storage[MAX_USERNAMES - 1].password[i])
        {
            printf("You entered the wrong password!\n");
            // Clean up failed account creation
            account_storage[index].isFree = true;
            for (int j = 0; j < USERNAME_SIZE; j++)
                account_storage[index].username[j] = 0;
            for (int j = 0; j < PASSWORD_SIZE; j++)
                account_storage[index].password[j] = 0;
            for (int j = 0; j < PASSWORD_SIZE; j++)
                account_storage[MAX_USERNAMES - 1].password[j] = 0;
            return 0;
        }
    }

    return 1;
}

// Input: None, prompts user for username
// Output: Returns account_storage index if username found, -1 if not found
// Searches for a username in the account_storage and returns its index or -1 if not found
int verify_username(user *account_storage)
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
        if (account_storage[i].isFree == false)
        {
            int comparison = 1;
            int j;

            // Compare character by character
            for (j = 0; j < USERNAME_SIZE - 1; j++)
            {
                if (account_storage[i].username[j] != temp_username[j])
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

// Input: index - user account_storage position, attempts - failed login count
// Output: Returns index if password matches, -1 if failed/locked (locks after 3 attempts)
// Verifies a user’s password with limited attempts and triggers account lock on failure
int verify_password(user *account_storage, int index, int attempts)
{
    // Lock account after 3 failed attempts
    if (attempts >= 3)
    {
        printf("Too many wrong tries, you are now locked for 2 minutes!\n");
        account_locker(account_storage, index);
        return -1;
    }

    if (account_storage[index].isFree)
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
        if (account_storage[index].password[i] != temp_password[i])
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
    return verify_password(account_storage, index, attempts + 1);
}

// Input: index - user to lock
// Output: Locks account for LOCK_OUT_TIME seconds, returns 0
// Locks a user account for a fixed timeout period after repeated failed logins
int account_locker(user *account_storage, int index)
{
    // Calculate lockout end time
    time_t start = time(NULL);
    account_storage[index].isLocked = start + LOCK_OUT_TIME;
    return 0;
}

// Input: accounts - pointer to account counter
// Output: Returns 1 if user deleted successfully after authentication, 0 on failure
// Authenticates and deletes an existing user, freeing the occupied slot
int delete_user_account(user *account_storage, int *accounts)
{
    // Verify username exists
    int user_index = verify_username(account_storage);
    if (user_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    if (account_storage[user_index].isLocked > time(NULL))
    {
        printf("User still locked for %d seconds!\n", account_storage[user_index].isLocked - time(NULL));
        return 0;
    }

    // Verify password matches
    int pass_index = verify_password(account_storage, user_index, 0);

    if (user_index != pass_index)
    {
        printf("You entered the wrong password!\n");
        return 0;
    }

    printf("User |%s| is being deleted.\n", account_storage[user_index].username);

    // Clear user data and mark slot as free
    account_storage[user_index].isFree = true;
    for (int j = 0; j < USERNAME_SIZE; j++)
        account_storage[user_index].username[j] = 0;
    for (int j = 0; j < PASSWORD_SIZE; j++)
        account_storage[user_index].password[j] = 0;
    (*accounts)--; // Decrement account counter
    printf("The user has been deleted.\n");
    return 1;
}

// Input: accounts - pointer to account counter
// Output: Returns 1 if user edited successfully after authentication, 0 on failure
// Authenticates a user and allows updating their username and password
int update_user_credentials(user *account_storage, int *accounts)
{
    // Verify username exists
    int user_index = verify_username(account_storage);

    if (user_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    if (account_storage[user_index].isLocked > time(NULL))
    {
        printf("User still locked for %d seconds!\n", account_storage[user_index].isLocked - time(NULL));
        return 0;
    }

    // Verify password matches
    int password_index = verify_password(account_storage, user_index, 0);

    if (password_index == -1)
    {
        printf("Wrong password!\n");
        return 0;
    }

    printf("Enter your new username and password below:\n");

    // Preserve slot state in case of failure
    int old_state = account_storage[user_index].isFree;

    // Attempt to create new credentials
    if (create_user_account(account_storage, user_index, accounts) == 0)
    {
        account_storage[user_index].isFree = old_state; // Restore state on failure
        return 0;
    }

    return 1;
}

// Input: None, prompts for username and password
// Output: Returns 0, prints login success or failure message
// Authenticates a user and reports login success or failure
int authenticate_user(user *account_storage)
{
    // Verify username exists
    int user_index = verify_username(account_storage);
    if (user_index == -1)
    {
        printf("User not found!\n");
        return 0;
    }

    if (account_storage[user_index].isLocked > time(NULL))
    {
        printf("User still locked for %d seconds!\n", account_storage[user_index].isLocked - time(NULL));
        return 0;
    }

    // Verify password matches
    int password_index = verify_password(account_storage, user_index, 0);
    if (user_index == password_index)
        printf("Successfully logged in!\n");
    else
        printf("The account does not exist!\n");
}

// Input: a - current account count
// Output: Prints list of registered usernames, returns 0
// Prints all currently registered usernames and their indices
int display_registered_users(user *account_storage, int accounts)
{
    printf("------------------------------------\n");
    if (accounts == 0)
        return 0;
    printf("These are the registered users: \n");

    // Display all active users
    for (int i = 0; i < MAX_USERNAMES; i++)
        if (account_storage[i].isFree == false)
            printf("User %d: %s\n", i + 1, account_storage[i].username);
    printf("------------------------------------\n");
}