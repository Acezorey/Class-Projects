/****************************************************************
//
//  NAME:        Ace Reyes
//
//  Homework:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 27, 2023
//
//  FILE:        record.h
//
//  DESCRIPTION: This file contains the definition of a 
//               struct record
//  
**************************************************************/

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};
