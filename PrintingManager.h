
#pragma once

#ifndef PrintingManager
#define PrintingManager

#include "Header.h"

int printingSimilarCustomers(PNode node, int flag);
int printingClientsInDescendingOrder(PNode root, int flag);//Printing clients from sorted tree froms small to large
int printingClientsInAscendingOrder(PNode root, int flag);//Printing clients from sorted tree from big to small 
void printInstructions();//Printing instructions for the program.
void printTableHead(char* print);//Creating a printable table header
void printCell(PClient cell);//Single client printing
void printingDebtorsOnly(PClient head);//Printing a list of debts only.
void printListDebtsFromTheSmallestToTheLargest(PClient head, char* mainTitle);//Printing the list from the smallest debt to the largest
void printingCellsWithErrors(PClient head);//Client printing with errors
void printErrors(char* error, int* printsThatWere);//Print the error
void printASortedCell(PClient previousList, int flag);//Print a sorted cell

#endif