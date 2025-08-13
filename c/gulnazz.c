#include <stdio.h>
#include <string.h>

struct user {
    char username[20];
    char password[20];
};

struct user users[50];
int userCount = 0;
int currentUser = 0;

void signUp();
void signIn();
void dashboard();
void showProfile();

int main()
{ 
    int choice;

    while(1)
    {
        printf("\n***** Bus Reservation System *****\n");
        printf("1. Sign up:\n");
        printf("2. Sign in:\n");
        printf("3. Exit:\n");
        printf("Please enter your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: 
            signUp();
            break;

            case 2:
            signIn();
            break;

            case 3:
            printf("Thank You for Exiting.....\n");
            return 0;
            break;

            default:
            printf("Invalid Choice! Try again.\n");
            break;
        }
    }
    return 0;     
}

void signUp()
{
    if (userCount >= 50)
    {
        printf("User limit reached!\n");
        return;
    }

    struct user newUser;
    printf("\n----- Sign Up -----\n");
    printf("enter username: ");
    scanf("%s", &newUser.username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username,newUser.username)==0)
        {
            printf("Username already exists! Try a different one.\n");
            return;
        }
    }
    printf("enter password: ");
    scanf("%s", &newUser.password);

    users[userCount] = newUser;
    userCount++;
    printf("Sign up Successful!\n");
}

void signIn()
{
    char user[20];
    char pass[20];

    printf("\n----- Sign In -----\n");
    printf("enter username: ");
    scanf("%s", &user);
    printf("enter password: ");
    scanf("%s", &pass);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username,user) == 0 && 
            strcmp(users[i].password,pass) == 0)
        {
           currentUser = i;
           printf("Login Successful!\n") ;
           dashboard();
           return;
        } 
    }
    printf("Invalid credentials! Try again.\n");
}

void dashboard()
{
    int choice;

    while(1)
    {
        printf("\n----- Dashboard -----\n");
        printf("Welcome, %s!\n", users[currentUser].username);
        printf("1. View Profile\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice==1)
        {
            showProfile();
        }
        else if(choice==2)
        {
            printf("Logged out successfully.\n");
            currentUser = 0;
            break;
        }
        else
        {
            printf("Invalid option! Try again.\n");
        }
    }
}

void showProfile()
{
    printf("\n------ User Profile -----\n");
    printf("Username: %s\n", users[currentUser].username);
}