#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 150
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_BIRTHDAY_LENGTH 10
#define FILE_NAME "CONTACT INFORMATION.txt"

typedef struct ContactInformation {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int day;
    int month;
} ContactInformation;

ContactInformation contacts[MAX_CONTACTS];
int contactCount = 0;

int daysInMonth(int month) {//non leap year
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

void loadContactsFromFile();
void saveContactsToFile();
void addContact(int num_contacts);
void editContact(int index);
void deleteContact(int index);
void printContacts();
void sortContactsByName();
void sortContactsByBirthday();

void loadContactsFromFile() {
    FILE *file = fopen("FILE_NAME", "r");//file from reading only
    if (file == NULL) {
        printf("No existing contact file found. Starting fresh.\n");//retrieve saved contacts
        return;
    }

    contactCount = 0;
    while (fscanf(file, "%s %d %d %s %s", contacts[contactCount].name, &contacts[contactCount].day,
                  &contacts[contactCount].month, contacts[contactCount].email, contacts[contactCount].phone) != EOF) {
        contactCount++;//how many contacts are used

    }

    fclose(file);
}

void saveContactsToFile() {
    FILE *file = fopen("FILE_NAME", "w");//write
    if (file == NULL) {
        printf("Error saving contacts to file.\n");
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s %d %d %s %s\n", contacts[i].name, contacts[i].day, contacts[i].month,
                contacts[i].email, contacts[i].phone);
    }

    fclose(file);
}

void addContact(int num_contacts) {
    for (int i = 0; i < num_contacts; i++) {
        printf("Enter your full name: ");
        scanf("%s", contacts[contactCount].name);

        printf("Enter day of birth (1-31): ");
        scanf("%d", &contacts[contactCount].day);

        printf("Enter month of birth (1-12): ");
        scanf("%d", &contacts[contactCount].month);

        printf("Enter email: ");
        scanf("%s", contacts[contactCount].email);

        printf("Enter phone number: ");
        scanf("%s", contacts[contactCount].phone);

        contactCount++;
    }
    saveContactsToFile(); // Save contacts to file after adding new ones
}

void editContact(int index) {
    printf("Enter new name: ");
    scanf("%s", contacts[index].name);

    printf("Enter new day of birth (1-31): ");
    scanf("%d", &contacts[index].day);

    printf("Enter new month of birth (1-12): ");
    scanf("%d", &contacts[index].month);

    printf("Enter new email: ");
    scanf("%s", contacts[index].email);

    printf("Enter new phone number: ");
    scanf("%s", contacts[index].phone);

    saveContactsToFile(); // Save contacts to file after editing
}

void deleteContact(int index) {
    for (int i = index; i < contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    contactCount--;

    saveContactsToFile(); // Save contacts to file after deleting
}

void printContacts() {
    if (contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        printf("Name: %s\n", contacts[i].name);
        printf("Birthday: %d/%d\n", contacts[i].day, contacts[i].month);
        printf("Email: %s\n", contacts[i].email);
        printf("Phone: %s\n", contacts[i].phone);
        printf("\n");
    }
}

void sortContactsByName() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                ContactInformation temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    saveContactsToFile(); // Save contacts to file after sorting
}

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
    saveContactsToFile(); // Save contacts to file after sorting
}

int main() {
    loadContactsFromFile(); // Load existing contacts from the file at the start

    int choice;
    while (1) {
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
        printf("7. Exit\n");

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
                    int index;
                    printf("Enter contact index to edit (1-%d): ", contactCount);
                    scanf("%d", &index);
                    editContact(index - 1);
                }
                break;
            case 3:
                if (contactCount == 0) {
                    printf("No contacts to delete.\n");
                } else {
                    int index;
                    printf("Enter contact index to delete (1-%d): ", contactCount);
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
                saveContactsToFile(); // Save contacts to file before exiting
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
