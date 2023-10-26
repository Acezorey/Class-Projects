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
//  FILE:        database.h
//
//  DESCRIPTION: This file contains the function prototypes
//               for the functions defined in database.c
//  
**************************************************************/

int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char[]);
int readfile(struct record **, char[]);
void cleanup(struct record **);
