
#pragma once

#ifndef Header
#define Header

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <crtdbg.h>

#define FILE_NAME "f.csv"
#define FILE_NAME_EXTENSION ".csv"// ending
#define ID 9//Maximum digits in ID.
#define PHONE 10//Maximum digits in phon.
#define DAY 31//Maximum days.
#define MONTH 12//Maximum months.
#define MAX_YEAR 2500//Maximum years
#define MIN_YEAR 1000//Minimum years ending

/*The length of the array is the same
as the number of variables in the client*/
#define SIZE_ARRAY 6
/*Creating an ENUM for the client values*/
enum treeEnum {
	EnFirst, EnLast, EnID, EnPhone, EnDebt, EnDate
};


typedef struct Date {//Date structure.
	unsigned int day : 6;
	unsigned int month : 4;
	unsigned int year : 12;
}Date;

typedef struct Error {//Client error checking structure
	unsigned int ERROR : 1;//Checking for errors.
	unsigned int firstName : 1;//Error getting first name.
	unsigned int lastName : 1;//Error getting last name
	unsigned int id : 1;//Error getting ID.
	unsigned int phone : 1;//Error getting phone.
	unsigned int date : 1;//Error getting date.
	unsigned int debt : 1;//Error getting debt.
	unsigned int lacksValues : 1;//Missing values error.  
	unsigned int comparisonFirstName : 1;//Error first name does not match ID.
	unsigned int comparisonLastName : 1;//Error last name does not match ID.
}Error;

typedef struct Client {//Client structure.
	char* firstName;
	char* lastName;
	char* id;
	char* phone;
	struct Client* next;//A place to receive the next cell
	float debt;
	Date date;
	Error error;//Errors by error structure
}Client, * PClient;

typedef struct List {//List manager structure
	PClient head;//The head list 
	PClient headError;//The head errors list
}List, * ListManager;

typedef struct node {
	PClient client;
	struct node* father;
	struct node* left, * right;
	struct node* nextLike;
}Node, * PNode;

typedef struct tree {
	PNode root;
}Tree, * PTree;






#endif
