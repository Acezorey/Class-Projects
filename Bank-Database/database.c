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
//                 and the value of each parameter. Does
//                 nothing otherwise
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
//  Return values: None
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
        printf("\n - uaddress (char[]): \n%s", uaddress);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
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
//                 and the value of its parameters. Does
//                 nothing otherwise
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
//                 and the value of its parameters. Does
//                 nothing but return 0 if it ran successfully
//                 otherwise
//
//  Parameters:    start (struct record*) :  The pointer to
//                             the starting record
//
//                 accnumber (int) : The account number of
//                             the account the user wants
//                             to locate
//
//  Return values:  0 : This function ran successfully
//                 -1 : This function did not run 
//                      successfully
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
                success = -1;
            }
            else if (hold->accountno == accnumber)
            {
                printf("\n~~Account found~~\n\n");
                printf("Account number: %d\n", hold->accountno);
                printf("Account user name: %s", hold->name);
                printf("Account user address: \n%s", hold->address);
                iterator = 0;
            }
            else if (hold->accountno > accnumber)
            {
                hold = hold->next;
            }
            else
            {
                iterator = 0;
                success = -1;
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
//                 and the value of its parameters. Does nothing
//                 but return 0 if successful otherwise.
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
                    success = -1;
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
//  DESCRIPTION:   This function reads from the memory file
//                 and creates a list of accounts, using
//                 addRecord, utilizing the data found in
//                 the file
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
