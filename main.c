#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30

typedef struct
{
    char firstname[30];
    char lastname[30];
    char type[7];
    int strength;
    int resist;
    int pierce;
    int accuracy;
    int id;
    int isinitialized;

} wizards;

void autofillValues(wizards *autoWizard);
void insert(wizards *insertwizard, int *currentsize);
void search(wizards *wizard);
void removeWizard(wizards *wizard, int *currentsize);
void display(wizards *wizard);
void checkFirstName(wizards *wizard);
void checkLastName(wizards *wizard);
void checkSchoolType(wizards *wizard);
void records(wizards *wizard);
void manual();

int main(void)
{
    int userchoice;
    wizards wizard[MAX_SIZE];
    autofillValues(wizard);

    int currentsize = 6;


    printf("Welcome to the Wizard Database!\n");

    while (userchoice != 5)
    {
        manual();
        printf("Selection: ");
        scanf("%d", &userchoice);

        while (userchoice > 5 || userchoice <= 0)
        {
            printf("Invalid Selection!!!\n");
            printf("Please enter a selection from the options above: ");
            scanf("%d", &userchoice);
        }

        switch (userchoice)
        {
        case 1:
            insert(wizard, &currentsize);
            break;
        case 2:
            removeWizard(wizard, &currentsize);
            break;
        case 3:
            search(wizard);
            break;
        case 4:
            display(wizard);
            break;
        default:
            records(wizard);
            printf("Records of Wizards in Database created\n");
            printf("Thank you for using the Wizard Database\n");
        }
    }

    return 0;
}
void records(wizards *wizard)
{
    FILE *ptrrecords = fopen("Records.txt", "w");

    if (ptrrecords == NULL)
    {
        printf("File was not opened!\n");
    }
    else
    {
        int max = MAX_SIZE;
        max += 1;
        // for loop to write wizard info to wizards.txt
        for (int x = 0; x < MAX_SIZE; x++)
        {
            if (wizard[x].isinitialized == 1 && wizard[x].id <= 30)
            {
                fprintf(ptrrecords, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
                fprintf(ptrrecords, "Wizard ID:\t%d\n", wizard[x].id);
                fprintf(ptrrecords, "First name:\t%s\n", wizard[x].firstname);
                fprintf(ptrrecords, "Last name:\t%s\n", wizard[x].lastname);
                fprintf(ptrrecords, "School:\t\t\t%s\n", wizard[x].type);
                fprintf(ptrrecords, "Strength:\t\t%d\n", wizard[x].strength);
                fprintf(ptrrecords, "Resist:\t\t\t%d\n", wizard[x].resist);
                fprintf(ptrrecords, "Accuracy:\t\t%d\n", wizard[x].accuracy);
                fprintf(ptrrecords, "Pierce:\t\t\t%d\n", wizard[x].pierce);
            }
        }
    }
}

// display all wizards in database
void display(wizards *wizard)
{
    int max = MAX_SIZE;
    max += 1;

    printf("Wizards currently in Database: \n");
    // for loop to iterate through wizard arr and display wizard info
    for (int x = 0; x < MAX_SIZE; x++)
    {
        if (wizard[x].isinitialized == 1 && wizard[x].id <= 30)
        {
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("Wizard ID:\t\t%d\n", wizard[x].id);
            printf("First name:\t\t%s\t\n", wizard[x].firstname);
            printf("Last name:\t\t%s\n", wizard[x].lastname);
            printf("School:\t\t\t%s\n", wizard[x].type);
            printf("Strength:\t\t%d\n", wizard[x].strength);
            printf("Resist:\t\t\t%d\n", wizard[x].resist);
            printf("Accuracy:\t\t%d\n", wizard[x].accuracy);
            printf("Pierce:\t\t\t%d\n", wizard[x].pierce);
        }
    }
    printf("\n");
}

// search wizard to see if wizard exist using entered user ID
void search(wizards *wizard)
{
    int wizardid;
    int isvalid = 0;
    int indexofwizard;
    printf("Enter the ID of Wizard: ");
    scanf("%d", &wizardid);


    // for loop to check if id from user is in the database
    for (int x = 0; x < MAX_SIZE; x++)
    {
        if (wizard[x].id == wizardid && wizard[x].isinitialized == 1)
        {
            isvalid = 1;
            indexofwizard = x;
        }
    }

    // if user input id is in the database display a success message
    if (isvalid == 1)
    {
        printf("The Wizard %s is in the Database\n",
               wizard[indexofwizard].firstname);
    }
    else     // else display message that wizard was not found
    {
        printf("A Wizard with the ID %d is not in the Database\n", wizardid);
    }
}

// removes wizard from wizard arr
void removeWizard(wizards *wizard, int *currentsize)
{
    int wizardremoval = 0;
    int count = 0;
    int validid = 0;


    printf("Enter the ID of the Wizard to remove: ");
    scanf("%d", &wizardremoval);

    // check if user input is valid
    while (wizardremoval < 1)
    {
        scanf("%*[^\n]");
        printf("Invalid input!!!\n");
        printf("Please enter a valid Wizard ID number: ");
        scanf("%d", &wizardremoval);
    }

    // check to see if id from user is valid
    for (int x = 0; x < MAX_SIZE; x++)
    {
        if (wizard[x].id == wizardremoval)
        {
            validid = 1;
        }
    }

    if (validid == 1)
    {

        // gets index of id for removal
        for (int x = 0; x < MAX_SIZE; x++)
        {
            if (wizard[x].id == wizardremoval && wizard[x].isinitialized == 1)
            {
                printf("Removing %s from the Database\n", wizard[x].firstname);
                count = x;
            }
        }

        // removes/replaces index with next index
        for (int x = wizardremoval; x < MAX_SIZE; x++)
        {
            wizard[x].isinitialized = 0;
            wizard[x] = wizard[x + 1];
        }

        *currentsize -= 1;
        wizard--;
    }
    else
    {
        printf("Wizard is not in database.\n");
    }
}

// displays manual on how to use database
void manual()
{
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("1: Add Wizard to Database\n");
    printf("2: Remove Wizard from Database\n");
    printf("3: Search Database for Wizard\n");
    printf("4: Display all Wizards\n");
    printf("5: Exit Wizard Database\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}

void insert(wizards *insertwizard, int *currentsize)
{
    *currentsize = *currentsize + 1;
    insertwizard += *currentsize;

    if(*currentsize > MAX_SIZE)
    {
        printf("The Wizard Database is full!\n");
        *currentsize = *currentsize - 1;
    }
    else
    {

        insertwizard->id = *currentsize;

        printf("Enter your first name: ");
        scanf("%s", insertwizard->firstname);
        scanf("%*[^\n]");
        checkFirstName(insertwizard);
        insertwizard->firstname[0] = toupper(insertwizard->firstname[0]);

        printf("Enter your last name: ");
        scanf("%s", insertwizard->lastname);
        scanf("%*[^\n]");
        checkLastName(insertwizard);
        insertwizard->lastname[0] = toupper(insertwizard->lastname[0]);

        printf("Here are your school selections\n");
        printf("Spirit schools: Death, Myth, Life\n");
        printf("Elemental schools: Storm, Fire, Ice\n");
        printf("Mixture: Balance\n");
        printf("Enter your school: ");
        scanf("%s", insertwizard->type);
        scanf("%*[^\n]");
        checkSchoolType(insertwizard);
        insertwizard->type[0] = toupper(insertwizard->type[0]);

        printf("Enter your strength 1-100: ");
        scanf("%d", &insertwizard->strength);

        while (insertwizard->strength < 1 || insertwizard->strength > 100)
        {
            scanf("%*[^\n]");
            printf("Invalid input!!!\n");
            printf("Strength can only be between 1-100\n");
            printf("Enter your strength: ");
            scanf("%d", &insertwizard->strength);
        }

        printf("Enter your resist 1-50: ");
        scanf("%d", &insertwizard->resist);
        while (insertwizard->resist < 1 || insertwizard->resist > 50)
        {
            scanf("%*[^\n]");
            printf("Invalid input!!!\n");
            printf("Resist can only be between 1-50\n");
            printf("Enter your resist: ");
            scanf("%d", &insertwizard->resist);
        }

        printf("Enter your accuracy 1-100: ");
        scanf("%d", &insertwizard->accuracy);
        while (insertwizard->accuracy < 1 || insertwizard->accuracy > 100)
        {
            scanf("%*[^\n]");
            printf("Invalid input!!!\n");
            printf("Accuracy can only be between 1-100\n");
            printf("Enter your accuracy: ");
            scanf("%d", &insertwizard->accuracy);
        }

        printf("Enter your pierce 1-30: ");
        scanf("%d", &insertwizard->pierce);
        while (insertwizard->pierce < 1 || insertwizard->pierce > 30)
        {
            scanf("%*[^\n]");
            printf("Invalid input!!!\n");
            printf("Pierce can only be between 1-30\n");
            printf("Enter your pierce: ");
            scanf("%d%*c", &insertwizard->pierce);
        }

        insertwizard->isinitialized = 1;

    }

}

// check if first name only contains letters
void checkFirstName(wizards *wizard)
{
    int hasdigit = 0;

    for (int x = 0; x < strlen(wizard->firstname); x++)
    {
        if (!(isalpha(wizard->firstname[x])))
        {
            hasdigit = 1;
        }
    }

    if (hasdigit == 1)
    {
        printf("Your wizards name can only contain letters!\n");
        printf("Please enter your first name: ");
        scanf("%s", wizard->firstname);
        scanf("%*[^\n]");
        checkFirstName(wizard);
    }
}

// check if first name only contains letters
void checkLastName(wizards *wizard)
{
    int hasdigit = 0;

    for (int x = 0; x < strlen(wizard->lastname); x++)
    {
        if (!(isalpha(wizard->lastname[x])))
        {
            hasdigit = 1;
        }
    }

    if (hasdigit == 1)
    {
        scanf("%*[^\n]");
        printf("Your wizards name can only contain letters!\n");
        printf("Please enter your first name: ");
        scanf("%s", wizard->lastname);
        scanf("%*[^\n]");
        checkLastName(wizard);
    }
}

// checks if school type only contains letters
void checkSchoolType(wizards *wizard)
{

    int checkchars = 0;

    // checks if all characters are letters
    for (int y = 0; y < strlen(wizard->type); y++)
    {
        if (!(isalpha(wizard->type[y])))
        {
            checkchars = 1;
        }
    }

    // if all characters arent letters prompt user to retry
    if (checkchars == 1)
    {
        printf("Invalid school!!!\n");
        printf("Please enter a valid school: ");
        scanf("%s", wizard->type);
        scanf("%*[^\n]");
        checkSchoolType(wizard);
    }

    // lowercases all characters in wizard->type string
    for (int x = 0; x < strlen(wizard->type); x++)
    {
        wizard->type[x] = tolower(wizard->type[x]);
    }

    // checks to make sure user school type is valid
    if (strcmp(wizard->type, "balance") != 0 &&
            strcmp(wizard->type, "storm") != 0 && strcmp(wizard->type, "fire") != 0 &&
            strcmp(wizard->type, "ice") != 0 && strcmp(wizard->type, "myth") != 0 &&
            strcmp(wizard->type, "death") != 0 && strcmp(wizard->type, "life") != 0)
    {
        printf("Invalid school!!!\n");
        printf("Please enter a valid school: ");
        scanf("%s", wizard->type);
        scanf("%*[^\n]");
        checkSchoolType(wizard);
    }
}

// auto creates six wizards for database
void autofillValues(wizards *autoWizard)
{



    // creating wizard1
    strcpy(autoWizard->firstname, "Kane");
    strcpy(autoWizard->lastname, "LifeGiver");
    strcpy(autoWizard->type, "Life");
    autoWizard->strength = 43;
    autoWizard->resist = 33;
    autoWizard->accuracy = 90;
    autoWizard->pierce = 7;
    autoWizard->isinitialized = 1;
    autoWizard->id = 1;
    autoWizard++;

    // creating wizard2
    strcpy(autoWizard->firstname, "Chris");
    strcpy(autoWizard->lastname, "ThunderPotion");
    strcpy(autoWizard->type, "Storm");
    autoWizard->strength = 65;
    autoWizard->resist = 15;
    autoWizard->accuracy = 70;
    autoWizard->pierce = 15;
    autoWizard->isinitialized = 1;
    autoWizard->id = 2;
    autoWizard++;

    // creating wizard3
    strcpy(autoWizard->firstname, "Keena");
    strcpy(autoWizard->lastname, "Wraith");
    strcpy(autoWizard->type, "Death");
    autoWizard->strength = 49;
    autoWizard->resist = 30;
    autoWizard->accuracy = 85;
    autoWizard->pierce = 10;
    autoWizard->isinitialized = 1;
    autoWizard->id = 3;
    autoWizard++;

    // creating wizard4
    strcpy(autoWizard->firstname, "Suri");
    strcpy(autoWizard->lastname, "IceWeaver");
    strcpy(autoWizard->type, "Ice");
    autoWizard->strength = 31;
    autoWizard->resist = 50;
    autoWizard->accuracy = 80;
    autoWizard->pierce = 6;
    autoWizard->isinitialized = 1;
    autoWizard->id = 4;
    autoWizard++;

    // creating wizard5
    strcpy(autoWizard->firstname, "Morgrim");
    strcpy(autoWizard->lastname, "SandDune");
    strcpy(autoWizard->type, "Balance");
    autoWizard->strength = 45;
    autoWizard->resist = 37;
    autoWizard->accuracy = 85;
    autoWizard->pierce = 8;
    autoWizard->isinitialized = 1;
    autoWizard->id = 5;
    autoWizard++;

    // creating wizard6
    strcpy(autoWizard->firstname, "Brooke");
    strcpy(autoWizard->lastname, "FairyTale");
    strcpy(autoWizard->type, "Myth");
    autoWizard->strength = 53;
    autoWizard->resist = 28;
    autoWizard->accuracy = 80;
    autoWizard->pierce = 10;
    autoWizard->isinitialized = 1;
    autoWizard->id = 6;
    //autoWizard++;

}
