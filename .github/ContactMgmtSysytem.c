#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// defines the maximum number
#define MAX_CONTACTS 150
#define MAX_NAME_LENGTH 100
#define MAX_BIRTHDAY_LENGTH 10
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_LENGTH 20

//structure torepresent a contact info
typedef struct ContactInformation {
    char name[MAX_NAME_LENGTH];//name
    char email[MAX_EMAIL_LENGTH];//email
    char phone[MAX_PHONE_LENGTH];//num
    int day;
    int month;
    
} ContactInformation;
//keeping track of number of contact used
ContactInformation contacts[MAX_CONTACTS];
int contactCount = 0;
// calculated the num of days in month
int daysInMonth(int month) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return daysInMonth[month - 1];
}
//print calendar for the month chosen
void printCalendar(int month, int year) {
    // array stored the number of days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //checking for leap year
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        daysInMonth[1] = 29;
    }
// first day of the month
    int dayOfWeek = (5 * ((year - 1) % 4) + 4) % 7;
    for (int i = 1; i < month; i++) {
        dayOfWeek = (dayOfWeek + daysInMonth[i - 1] % 7) % 7;
    }
//print calender
    printf("  Sun Mon Tue Wed Thu Fri Sat\n");
    for (int i = 0; i < dayOfWeek; i++) {
        printf("    ");
    }
    for (int i = 1; i <= daysInMonth[month - 1]; i++) {
        printf("%2d ", i);
        if (((dayOfWeek + i - 1) % 7 == 6)) {
            printf("\n");
        }
    }
    printf("\n");
}
//function to add contact
void addContact(int num_contacts) {
    // loop through num of contacts
    for (int i = 0; i < num_contacts; i++) {
        //get the name
        char name[MAX_NAME_LENGTH];
        printf("Enter your full name: ");
        scanf("%s", name);//storing the name
//get birthday
        int month, day;
        printf("Select your birthday:\n");
        printf("Enter month (1-12): ");
        scanf("%d", &month);
        for (; month <= 12; month++) {
            //print calendar for month
            printCalendar(month, 2024); // print calendar for each month
            printf("Enter month (%d) or 0 to go back: ", month);
            int choice;
            scanf("%d", &choice);
            if (choice == 0) {
                //go back to previous month
                month--;
                continue;
            }
            printf("Select day: ");
            for (day = 1; day <= daysInMonth(month); day++) {
                printf("%d ", day);
                if (day % 7 == 0) {
                    printf("\n");
                }
            }
            printf("\nEnter day (1-%d): ", daysInMonth(month));
            scanf("%d", &day);
            continue;
        }

        char email[MAX_EMAIL_LENGTH];
        printf("Enter email: ");
        scanf("%s", email);

        char phone[MAX_PHONE_LENGTH];
        printf("Enter phone number: ");
        scanf("%s", phone);
//add the contacts to an array
        strcpy(contacts[contactCount].name, name);
        contacts[contactCount].day = day;
        contacts[contactCount].month = month;
        strcpy(contacts[contactCount].email, email);
        strcpy(contacts[contactCount].phone, phone);
        contactCount++;
    }
}
//function to edit
void editContact(int index) {
    char name[MAX_NAME_LENGTH];
    printf("Enter new name: ");
    scanf("%s", name);
//nw birthday
    int month, day;
    printf("Select new birthday:\n");
    for (month = 1; month <= 12; month++) {
        printCalendar(month, 2024); // print calendar for each month
        printf("Enter month (%d) or 0 to go back: ", month);
        int choice;
        scanf("%d", &choice);
        if (choice == 0) {
            month--;
            break;
        }
        printf("Select day: ");
        for (day = 1; day <= daysInMonth(month); day++) {
            printf("%d ", day);
            if (day % 7 == 0) {
                printf("\n");
            }
        }
        printf("\nEnter day (1-%d): ", daysInMonth(month));
        scanf("%d", &day);
        break;
    }

    char email[MAX_EMAIL_LENGTH];
    printf("Enter new email: ");
    scanf("%s", email);

    char phone[MAX_PHONE_LENGTH];
    printf("Enter new phone number: ");
    scanf("%s", phone);
//update the contact into array
    strcpy(contacts[index].name, name);
    contacts[index].day = day;
    contacts[index].month = month;
    strcpy(contacts[index].email, email);
    strcpy(contacts[index].phone, phone);
}
//function to delete contact
void deleteContact(int index) {
    // Shift all contacts after the deleted contact down by one
    for (int i = index; i < contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    //decrement the count
    contactCount--;
}
//sorting contact by name
void sortContactsByName() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                //swap contacts
                ContactInformation temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}
//by birthday
void sortContactsByBirthday() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (contacts[j].month > contacts[j + 1].month || (contacts[j].month == contacts[j + 1].month && contacts[j].day > contacts[j + 1].day)) {
                ContactInformation temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}
//print all contacts
void printContacts() {// check if there are contacts
    if (contactCount == 0) {
        printf("No contacts to display.\n");
    } else{
    for (int i = 0; i < contactCount; i++) {
        printf(" Name: %s\n Birthday: %d/%d\n Email: %s\n Phone: %s\n", contacts[i].name, contacts[i].day, contacts[i].month, contacts[i].email, contacts[i].phone);
        
    }
  
    }
}
//main function
int main() {
    int choice;
    while (1) {//infinite loop
        printf("\n\t\t\t\t**** WELCOME TO CONTACT MANAGEMENT SYSTEM **** \n");
        printf("\t\t\t\t\t+-------------------------------+\n");
        printf("\t\t\t\t\t|          MAIN MENU          |\n");
        printf("\t\t\t\t\t+-------------------------------+\n\n");

        printf("1. Add contact\n");
        printf("2. Edit contact\n");
        printf("3. Delete contact\n");
        printf("4. Sort contacts by name\n");
        printf("5. Sort contacts by birthday\n");
        printf("6. Print contacts\n");
        printf("7. Exit\n\n");

        printf("\t\t\t\t\t+-------------------------------+\n");
        printf("\t\t\t\t\t|        PLEASE SELECT AN      |\n");
        printf("\t\t\t\t\t|        OPTION FROM ABOVE     |\n");
        printf("\t\t\t\t\t+-------------------------------+\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        printf("\n");

        switch (choice) {
            case 1:
                if (contactCount < MAX_CONTACTS) {
                    printf("How many contacts do you want to add? (Max %d): ", MAX_CONTACTS - contactCount);
                    int num_contacts;
                    scanf("%d", &num_contacts);
                    if (num_contacts > MAX_CONTACTS - contactCount) {
                        printf("You can only add %d more contacts.\n", MAX_CONTACTS - contactCount);
                        num_contacts = MAX_CONTACTS - contactCount;
                    }
                    addContact(num_contacts);
                } else {
                    printf("Contact list is full. Please delete some contacts before adding more.\n");
                }
                break;
            case 2:
                if (contactCount == 0) {
                    printf("No contacts to edit.\n");
                } else {
                    printf("Enter contact index to edit (1-%d): ", contactCount);
                    int index;
                    scanf("%d", &index);
                    editContact(index - 1);
                }
                break;
            case 3:
                if (contactCount == 0) {
                    printf("No contacts to delete.\n");
                } else {
                    printf("Enter contact index to delete (1-%d): ", contactCount);
                    int index;
                    scanf("%d", &index);
                    deleteContact(index - 1);
                }
                break;
            case 4:
                sortContactsByName();
                break;
            case 5:
                sortContactsByBirthday();
                break;
            case 6:
                printContacts();
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
