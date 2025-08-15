#include <stdio.h>
#include <string.h>

struct user {
    char username[20];
    char password[20];
};

struct Bus {
    int busNo;
    char source[20];
    char destination[20];
    int totalSeats;
    int availableSeats;
    float fare;
};

struct user users[50];
int userCount = 0;
int currentUser = 0;

struct Bus buses[3]; 

void signUp();
void signIn();
void dashboard();
void showProfile();
void userMenu();
void bookTicket();
void cancelTicket();
void checkBusStatus();
void showAvailableBuses();

int main()
{
    buses[0].busNo = 101;
    strcpy(buses[0].source, "Delhi");
    strcpy(buses[0].destination, "Bihar");
    buses[0].totalSeats = 50;
    buses[0].availableSeats = 50;
    buses[0].fare = 500.0;

    buses[1].busNo = 102;
    strcpy(buses[1].source, "Patna");
    strcpy(buses[1].destination, "Lucknow");
    buses[1].totalSeats = 40;
    buses[1].availableSeats = 40;
    buses[1].fare = 450.0;

    buses[2].busNo = 103;
    strcpy(buses[2].source, "Mumbai");
    strcpy(buses[2].destination, "Pune");
    buses[2].totalSeats = 30;
    buses[2].availableSeats = 30;
    buses[2].fare = 300.0;

    int choice;

    while(1)
    {
        printf("\n*** Bus Reservation System ***\n");
        printf("1. Sign up\n");
        printf("2. Sign in\n");
        printf("3. Exit\n");
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
            
            default: 
            printf("Invalid Choice! Try again.\n");
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
    printf("Enter username: ");
    scanf("%s", newUser.username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, newUser.username) == 0)
        {
            printf("Username already exists! Try a different one.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    users[userCount] = newUser;
    userCount++;
    printf("Sign up Successful!\n");
}

void signIn()
{
    char user[20];
    char pass[20];

    printf("\n----- Sign In -----\n");
    printf("Enter username: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", pass);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, user) == 0 &&
            strcmp(users[i].password, pass) == 0)
        {
           currentUser = i;
           printf("Login Successful!\n");
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
        printf("2. User Menu\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            showProfile();
        }
        else if(choice == 2)
        {
            userMenu();
        }
        else if(choice == 3)
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

void userMenu()
{
    int option;
    while(1)
    {
        printf("\n=== User Menu ===\n");
        printf("1. Book a Ticket\n");
        printf("2. Cancel a Ticket\n");
        printf("3. Check Bus Status\n");
        printf("4. Logout\n");
        printf("Choose your option: ");
        scanf("%d", &option);

        if (option == 1)
        {
            bookTicket();
        }
        else if (option == 2)
        {
            cancelTicket();
        }
        else if (option == 3)
        {
            checkBusStatus();
        }
        else if (option == 4)
        {
            printf("Logged Out.\n");
            break;
        }
        else
        {
            printf("Invalid Option! Try again.\n");
        }
    }
}

void showAvailableBuses()
{
    printf("\n--- Available Buses ---\n");
    for(int i = 0; i < 3; i++)
    {
        printf("Bus Number: %d | %s -> %s | Total Seats: %d | Available Seats: %d | Fare: %.2f\n",
                buses[i].busNo, buses[i].source, buses[i].destination,
                buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
    }
}

void bookTicket()
{
    int busNo, seats, flag = 0;
    showAvailableBuses();

    printf("Enter Bus Number to book: ");
    scanf("%d", &busNo);

    for(int i = 0; i < 3; i++)
    {
        if(buses[i].busNo == busNo)
        {
            flag = 1;
            printf("Enter number of seats: ");
            scanf("%d", &seats);
            if(seats > 0 && seats <= buses[i].availableSeats)
            {
                buses[i].availableSeats -= seats;
                printf("Booking Successful! %d seats booked on Bus %d\n", seats, busNo);
            }
            else
            {
                printf("Invalid or insufficient seats!\n");
            }
            break;
        }
    }
    if(!flag)
    {
        printf("Bus not found!\n");
    }
}

void cancelTicket()
{
    int busNo, seats, flag = 0;
    showAvailableBuses();

    printf("Enter Bus Number to cancel seats: ");
    scanf("%d", &busNo);

    for(int i = 0; i < 3; i++)
    {
        if(buses[i].busNo == busNo)
        {
            flag= 1;
            printf("Enter number of seats to cancel: ");
            scanf("%d", &seats);
            if(seats > 0 && buses[i].availableSeats + seats <= buses[i].totalSeats)
            {
                buses[i].availableSeats += seats;
                printf("Cancellation Successful! %d seats canceled on Bus %d\n", seats, busNo);
            }
            else
            {
                printf("Invalid number of seats!\n");
            }
            break;
        }
    }
    if(!flag)
    {
        printf("Bus not found!\n");
    }
}

void checkBusStatus()
{
    int busNo, flag = 0;
    printf("Enter Bus Number to check status: ");
    scanf("%d", &busNo);

    for(int i = 0; i < 3; i++)
    {
        if(buses[i].busNo == busNo)
        {
            flag = 1;
            printf("\n--- Bus Status ---\n");
            printf("Bus Number: %d\n", buses[i].busNo);
            printf("Source: %s\n", buses[i].source);
            printf("Destination: %s\n", buses[i].destination);
            printf("Total Seats: %d\n", buses[i].totalSeats);
            printf("Available Seats: %d\n", buses[i].availableSeats);
            printf("Fare: %.2f\n", buses[i].fare);
            break;
        }
    }
    if(!flag)
    {
        printf("Bus not found!\n");
    }
}