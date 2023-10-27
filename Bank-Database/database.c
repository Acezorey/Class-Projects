/****************************************************************
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
//  FILE:        database.c
//
//  DESCRIPTION: 
//    This file contains the database.c source code, with the 
//    now fully implemented bank database functions
//
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

/***************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   If in debug mode, prints out its own name,
//                 the names and data types of its parameters,
//                 and the value of each parameter. Takes in
//                 the input values of its parameters,
//                 creates a struct record, adds all of the
//                 inputted user information to it and links
//                 it to other already existing struct
//                 records in the correct place (in descending
//                 order according to its account number). If
//                 a record with the inputted account number
//                 already exists, this function instead
//                 returns an error value and does not
//                 create a new record. If it was successful
//                 in adding a record and it is the first
//                 record in the list (start is NULL), then
//                 it sets start (the pointer pointed to by
//                 startpointer) to the address of the first
//                 record.
//
//  Parameters:    startpointer (struct record**) : 
//                             The pointer to the start pointer
//                             to the first struct record in
//                             the list
//
//                 accnumber (int) : The inputted account 
//                             number for a new account
//
//                 name (char[]) : The inputted name for a
//                             new account
//
//                 address (char[]) : The inputted address for 
//                             a new account
//
//  Return values: 0 : This function was successful in adding
//                     a record
//
//                -1 : This function was not successful in 
//                     adding a record, since a record with
//                     its account number already exists
//
**************************************************************/  

extern int debugmode;

int addRecord(struct record ** startpointer, int accnumber, char uname[], char uaddress[])
{
    int looper = 1;
    int success = 0;
    struct record * front = (*startpointer);
    struct record * hold = NULL;
    struct record * prev = NULL;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: addRecord\n");
        printf("Parameter names and values:\n");
        printf(" - startpointer (struct record **): %p\n", (void*)startpointer);
        printf(" - accnumber: %i\n", accnumber);
        printf(" - uname (char[]): %s", uname);
        printf(" - uaddress (char[]): \n%s", uaddress);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    if (front != NULL)
    {
        while (looper == 1)
        {
            if (accnumber < front->accountno)
            {
                if (front->next == NULL)
                {
                    hold = (struct record*)malloc(sizeof(struct record));
                    front->next = hold;
                    hold->accountno = accnumber;
                    strcpy(hold->name, uname);
                    strcpy(hold->address, uaddress);
                    hold->next = NULL;
                    looper = 0;
                }
                else
                {
                    prev = front;
                    front = front->next;
                }
            }
            else if (accnumber > front->accountno)
            {
                hold = (struct record*)malloc(sizeof(struct record));
                if (prev != NULL)
                {
                    prev->next = hold;
                }
                else
                {
                    (*startpointer) = hold;
                }
                hold->next = front;
                hold->accountno = accnumber;
                strcpy(hold->name, uname);
                strcpy(hold->address, uaddress);
                looper = 0;
            }
            else
            {
                success = -1;
                looper = 0;
            }
        }
    }
    else
    {
        (*startpointer) = (struct record*)malloc(sizeof(struct record));
        (*startpointer)->accountno = accnumber;
        strcpy((*startpointer)->name, uname);
        strcpy((*startpointer)->address, uaddress);
        (*startpointer)->next = NULL;
    }
    return success;
}

/*************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   If in debug mode, prints out its name,
//                 the name and datatypes of its parameters,
//                 and the value of its parameters. Iterates
//                 through each struct record one by one
//                 and prints out the information stored
//                 within each. If the list is empty, it
//                 instead prints out that the list is
//                 currently empty.
//
//  Parameters:    start (struct record*) :
//                       The pointer to the first struct
//                       record in the list
//
//  Return values: None (void)
//
************************************************************/

void printAllRecords(struct record * start)
{
    struct record * hold = start;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: printAllRecords\n");
        printf("Parameter names and values:\n");
        printf(" - start (struct record *): %p\n", (void*)start);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    if (hold == NULL)
    {
        printf("\nThe database is currently empty\n\n");
    }

    while (hold != NULL)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Account number: %d\n", hold->accountno);
        printf("Account user name: %s", hold->name);
        printf("Account user address: \n%s", hold->address);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        hold = hold->next;
    }
}

/**************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   If in debug mode, prints out its name,
//                 the name and datatypes of its parameters,
//                 and the value of its parameters. Takes
//                 in the value of its input parameters and
//                 looks for the record with the same
//                 account number as the inputted number,
//                 entering the list using the start pointer.
//                 If the inputted number does not correspond
//                 to any account, it instead returns an
//                 error value indicating that the account
//                 does not exist. If the list is empty,
//                 it returns an error value indicating
//                 such.
//
//  Parameters:    start (struct record*) :  The pointer to
//                             the starting record
//
//                 accnumber (int) : The account number of
//                             the account the user wants
//                             to locate
//
//  Return values:  0 : The account was successfully found
//
//                 -1 : The record is empty
//
//                 -2 : The account does not exist
//
*************************************************************/

int findRecord(struct record * start, int accnumber)
{
    struct record * hold = start;
    int success = 0;
    int iterator = 1;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: findRecord\n");
        printf("Parameter names and values:\n");
        printf(" - start (struct record *): %p\n", (void*)start);
        printf(" - accnumber (int): %i\n", accnumber);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    if (hold != NULL)
    {
        while (iterator == 1)
        {
            if (hold == NULL)
            {
                iterator = 0;
                success = -2;
            }
            else if (hold->accountno == accnumber)
            {
                printf("\n~~~~~~~~~~~ Account Found ~~~~~~~~~~~\n");
                printf("Account number: %d\n", hold->accountno);
                printf("Account user name: %s", hold->name);
                printf("Account user address: \n%s", hold->address);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
                iterator = 0;
            }
            else if (hold->accountno > accnumber)
            {
                hold = hold->next;
            }
            else
            {
                iterator = 0;
                success = -2;
            }
        }
    }
    else
    {
        success = -1;
    }
    return success;
}

/****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   If in debug mode, prints out its name,
//                 the name and datatypes of its parameters,
//                 and the value of its parameters. Deletes the
//                 account with the target user inputted account
//                 number (sets start pointer to NULL if the
//                 account is the only record in the list).
//                 Returns an error if the list is empty
//                 or the account does not exist.
//
//  Parameters:    startpointer (struct record**) :
//                       The pointer to the pointer to the
//                       starting record
//                    
//                 accnumber (int) : The account number of the
//                       record the user wants to delete
//
//  Return values:  0 : This function ran successfully
//                 -1 : This function did not run successfully
//
****************************************************************/

int deleteRecord(struct record ** startpointer, int accnumber)
{
    int success = 0;
    int looper = 1;
    struct record * prev = NULL;
    struct record * hold;
    struct record * front;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: deleteRecord\n");
        printf("Parameter names and values:\n");
        printf(" - startpointer (struct record **): %p\n", (void*)startpointer);
        printf(" - accnumber (int): %i\n", accnumber);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    if ((*startpointer) == NULL)
    {
        success = -1;
    }
    else
    {
        hold = (*startpointer);

        while (looper == 1)
        {
            if (hold->accountno == accnumber)
            {
                if (prev == NULL)
                {
                    if (hold->next == NULL)
                    {
                        (*startpointer) = NULL;
                    }
                    else
                    {
                        (*startpointer) = hold->next;
                    }
                    free(hold);
                    looper = 0;
                }
                else
                {
                    prev->next = front;
                    free(hold);
                    looper = 0;
                }
            }
            else
            {
                if (hold->next == NULL)
                {
                    looper = 0;
                    success = -2;
                }
                else
                {
                    prev = hold;
                    hold = hold->next;
                    front = hold->next;
                }
            }
        }
    }
    return success;
}

/**************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This function iteratively prints out
//                 the information from every struct record
//                 in the given list to a memory file
//
//  Parameters:    start (struct record*): The pointer to the
//                           first struct record in the list
//
//                 filename (char[]): The name of the file
//                           to be opened
//
//  Return values: 0: This function ran successfully
//                -1: This function did not run successfully
//
**************************************************************/

int writefile(struct record * start, char filename[])
{
    FILE * file = fopen(filename, "w");
    struct record * hold = start;
    int success = 0;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: writefile\n");
        printf("Parameter names and values:\n");
        printf(" - start (struct record *): %p\n", (void*)start);
        printf(" - filename (char[]): %s\n", filename);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    while (hold != NULL)
    {
        fprintf(file, "%d", hold->accountno);
        fputs(hold->name, file);
        fputs(hold->address, file);
        fputc('\n', file);
        hold = hold->next;
    }

    fclose(file);
    return success;
}

/*************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This function reads from a memory storage
//                 file (if one exists), and uses addRecord
//                 to continuously add records to the list
//                 using the information found in the
//                 memory file
//
//  Parameters:    startpointer (struct record**): The pointer
//                          to the pointer to the first 
//                          struct record in the list
//
//                 filename (char[]): The name of the file
//                          to be opened and read
//
//  Return values: 0: The function ran successfully
//                -1: The function did not run successfully
//
*************************************************************/

int readfile(struct record ** startpointer, char filename[])
{
    FILE * file = fopen(filename, "r");
    int success = 0;
    int accnum = 0;
    int looper = 1;
    int iterator = 0;
    char accname[30];
    char accaddress[50];
    char c;
    char prevc = 0;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: readfile\n");
        printf("Parameter names and values:\n");
        printf(" - startpointer (struct record **): %p\n", (void*)startpointer);
        printf(" - filename (char[]): %s\n", filename);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    if (file == NULL)
    {
        success = -1;
    }
    else
    {
        while (looper == 1)
        {
            c = fgetc(file);
            if (c == EOF)
            {
                looper = 0;
            }
            else
            {
                ungetc(c, file);
                fscanf(file, "%d", &accnum);
                fgets(accname, 30, file);
                looper = 2;
                while (looper == 2)
                {
                    c = fgetc(file);
                    if (c == '\n' && prevc == '\n')
                    {
                        accaddress[iterator] = 0;
                        looper = 1;
                        iterator = 0;
                    }
                    else
                    {
                        accaddress[iterator] = c;
                        prevc = c;
                        iterator++;
                    }
                }
                addRecord(startpointer, accnum, accname, accaddress);
            }
        }
        fclose(file);
    }
    return success;
}

/************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   This function deletes and deallocates the
//                 memory spaces of all struct records
//                 in the list
//
//  Parameters:    startpointer (struct record **): The pointer
//                        to the pointer to the first struct
//                        record in the list
//
//  Return values: None (void)
//
************************************************************/

void cleanup(struct record ** startpointer)
{
    struct record * hold = (*startpointer);
    struct record * front;

    if (debugmode == 1)
    {
        printf("\n\n~~~~~~~~~~Debug Mode Output~~~~~~~~~~\n");
        printf("Function name: cleanup\n");
        printf("Parameter names and values:\n");
        printf(" - startpointer (struct record **): %p\n", (void*)startpointer);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    while (hold != NULL)
    {
        front = hold->next;
        free(hold);
        hold = front;
    }
    (*startpointer) = NULL;
}
