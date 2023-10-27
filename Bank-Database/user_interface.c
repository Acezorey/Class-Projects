/*****************************************************************
//
//  NAME:        Ace Reyes
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 27, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file contains the user interface source code for
//   the bank user interface
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

void getaddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION: * Displays to the user an introductory message
//                 and menu screen, prompting the user to select
//                 a menu option. Upon selection, main will
//                 prompt the user for any more additional
//                 required information, sometimes through
//                 the use of the function getaddress, and then
//                 call the appropriate database.c function
//                 with the collected information.
//
//               * If the input for the menu option provided by
//                 the user is determined to not be valid, main
//                 will ask the user to retype their input
//
//               * If debug mode was attempted to be run, main
//                 first checks if debug mode was called 
//                 correctly. Prints out an error message if
//                 not, and activates debug mode (sets
//                 global variable debugmode to 1) if valid
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
/                                  to the program.
//
//  Return values: int success: 0 if function ran successfully,
//                              -1 if it did not
//
****************************************************************/

int debugmode = 0;

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    struct record ** startPointer = &start;

    int success = 0;
    int runFunction = 1;
    int userInputNum = 0;
    int looper = 1;
    int iterator = 0;
    int functionsuccess = 0;
    int fs = 0;
    int switcher = 0;

    char selector = 0;

    char buffercleaner[100];
    char debug[6] = "debug";
    char add[4] = "add";
    char printall[9] = "printall";
    char find[5] = "find";
    char delete[7] = "delete";
    char quit[5] = "quit";

    char userInput[30];
    char check[9];
    char address[50];

    if (argc > 2)
    {
        success = -1;
    }
    else if (argc == 2 && strcmp(debug, argv[1]) != 0)
    {
        success = -1;
    }
    else if  (argc == 2 && strcmp(debug, argv[1]) == 0)
    {
        debugmode = 1;
    }

    if (success == -1)
    {
        printf("-input: Unknown arguments\n");
        printf("To enter debug mode type only 'debug' as the argument\n");
        printf("along with the name of the file\n");
        printf("Example: './project debug'\n");
    }
    else
    {
        readfile(startPointer, "memory.txt");

        if (debugmode == 1)
        {
            printf("\n\nDEBUG MODE\n");
            printf("@========================================================================@\n");
        }
        else
        {
            printf("\n\n@===================================");
            printf("=====================================@\n");
        }
        printf("\n                   - Welcome to Ace's Bank Database -\n\n");
        printf("\nEnter in the name of the menu option to select it\n");

        while (runFunction == 1)
        {
            userInputNum = 0;
            iterator = 0;
            switcher = 0;
            looper = 1;
            printf("\nMenu options:\n");
            printf(" - add: Adds a new record into the database\n");
            printf(" - printall: Prints all records in the database\n");
            printf(" - find: Finds the record with a specified account number\n");
            printf(" - delete: Deletes the existing record with a specified acccount number\n");
            printf(" - quit: Quits the program\n\n");
            printf("\nChoose a menu option: ");

            fgets(userInput, 50, stdin);

            if (userInput[0] == 'a')
            {
                if (strlen(userInput) <= strlen(add) + 1)
                {
                    switcher = 1;
                    strcpy(check, add);
                }
            }
            else if (userInput[0] == 'p')
            {
                if (strlen(userInput) <= strlen(printall) + 1)
                {
                    switcher = 2;
                    strcpy(check, printall);
                }
            }
            else if (userInput[0] == 'f')
            {
                if (strlen(userInput) <= strlen(find) + 1)
                {
                    switcher = 3;
                    strcpy(check, find);
                }
            }
            else if (userInput[0] == 'd')
            {
                if (strlen(userInput) <= strlen(delete) + 1)
                {
                    switcher = 4;
                    strcpy(check, delete);
                }
            }
            else if (userInput[0] == 'q')
            {
                if (strlen(userInput) <= strlen(quit) + 1)
                {
                    switcher = 5;
                    strcpy(check, quit);
                }
            }

            if (switcher != 0)
            {
                while (iterator < strlen(userInput) - 1)
                {
                    if (userInput[iterator] != check[iterator] && userInput[iterator] != '\n')
                    {
                        switcher = 0;
                    }
                    iterator++;
                }
            }

            switch (switcher)
            {
                case 1:
                printf("\nChosen menu option: add\n\n");

                while (looper == 1)
                {
                    printf("\nEnter in an account number: ");
                    scanf("%d", &userInputNum);
                    if (userInputNum <= 0)
                    {
                        printf("\nPlease enter in a posivive non-zero number\n");
                        fgets(buffercleaner, 100, stdin);
                    }
                    else
                    {
                        fgets(buffercleaner, 100, stdin);
                        looper = 0;
                    }
                }
                printf("\nEnter your name: ");
                fgets(userInput, 30, stdin);
                printf("\nType in your address\n\n");
                printf("This address has a limit of 50 characters\n");
                printf("In order to enter in your address, press 'enter' twice in a row\n\n");
                printf("Address:\n\n");
                looper = 1;
                while (looper == 1)
                {
                    getaddress(address, 50);
                    printf("\n\nInputted address:\n\n");
                    printf("%s", address);
                    printf("\nIs this your correct address? (Y/N): ");
                    looper = 2;
                    while (looper == 2)
                    {
                        selector = fgetc(stdin);
                        if (selector == 'Y' || selector == 'y')
                        {
                            fs = addRecord(startPointer, userInputNum, userInput, address);
                            functionsuccess = fs;
                            if (functionsuccess == 0)
                            {
                                printf("\nYou have successfully added a record\n\n");
                            }
                            else
                            {
                                printf("\nFailed to add record,");
                                printf(" account with that number already exists\n");
                                printf("Cannot add duplicate accounts\n\n");
                            }
                            looper = 0;
                        }
                        else if (selector == 'N' || selector == 'n')
                        {
                            printf("\n\nRe-enter your address:\n\n");
                            looper = 1;
                        }
                        else if (selector != '\n')
                        {
                            printf("\nEnter in either 'Y' or 'N': ");
                        }
                        fgets(buffercleaner, 100, stdin);
                    }
                }
                break;

                case 2:
                printf("\nChosen menu option: printall\n\n");
                printAllRecords(start);
                printf("\n");
                break;

                case 3:
                printf("\nChosen menu option: find\n\n");

                while (looper == 1)
                {
                    printf("\nEnter in the account number you wish to look for: ");
                    scanf("%i", &userInputNum);
                    if (userInputNum <= 0)
                    {
                        printf("\nPlease enter in a positive non-zero number\n");
                        fgets(buffercleaner, 100, stdin);
                    }
                    else
                    {
                        printf("\nFinding account: %i\n\n", userInputNum);
                        fgets(buffercleaner, 100, stdin);
                        looper = 0;
                    }
                }
                functionsuccess = findRecord(start, userInputNum);
                if (functionsuccess == -1)
                {
                    printf("\nFailed to find account, database is currently empty\n\n");
                }
                else if (functionsuccess == -2)
                {
                    printf("\nFailed to find account, account does not exist\n\n");
                }
                break;

                case 4:
                printf("\nChosen menu option: delete\n\n");

                while (looper == 1)
                {
                    printf("\nEnter in the account number you wish to delete: ");
                    scanf("%d", &userInputNum);
                    if (userInputNum <= 0)
                    {
                        printf("\nPlease enter in a positive non-zero number\n");
                        fgets(buffercleaner, 100, stdin);
                    }
                    else
                    {
                        printf("\nDeleting account: %i\n\n", userInputNum);
                        fgets(buffercleaner, 100, stdin);
                        looper = 0;
                    }
                }
                functionsuccess = deleteRecord(startPointer, userInputNum);
                if (functionsuccess == -1)
                {
                    printf("\nFailed to delete account, database is currently empty\n\n");
                }
                else if (functionsuccess == -2)
                {
                    printf("\nFailed to delete account, account does not exist\n\n");
                }
                else if (functionsuccess == 0)
                {
                    printf("\nSuccessfully deleted account %d\n\n", userInputNum);
                }
                break;

                case 5:
                printf("\nChosen menu option: quit\n\n");
                writefile(start, "memory.txt");
                runFunction = 0;
                break;

                case 0:
                printf("\nPlease enter a valid menu option name\n");
                break;
            }
        }
        cleanup(startPointer);
        printf("\n               - Thank you for using Ace's Bank Database -\n\n");
        printf("@========================================================================@\n\n\n");
    }
    return success;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION: * This function uses an fgetc loop in order to
//                 extract the user's inputted address, no matter
//                 the format, terminating only once "Enter" is
//                 pressed twice subsequently.
//
//               * In debug mode, this function additionally
//                 prints out its name, the name of the 
//                 parameters passed to it, and their values
//
//  Parameters:    address (char[]) : The array storing the address
//                 size (int)  : The size of the address array
//
//  Return values: None
//
****************************************************************/

void getaddress(char* address, int size)
{
    char c;
    char prevc = 0;
    int looper = 1;
    int index = 0;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: getaddress\n");
        printf("Function parameter names and values:\n");
        printf("- address (char[]): \n%s", address);
        printf("\n- size (int): %d", size);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    while (looper == 1)
    {
        c = fgetc(stdin);
        if (c == '\n' && prevc == '\n')
        {
            address[index] = 0;
            looper = 0;
        }
        else
        {
            address[index] = c;
            prevc = c;
            index++;
        }
        if (index == size - 2)
        {
            address[index] = 0;
            looper = 0;
        }
    }
}
