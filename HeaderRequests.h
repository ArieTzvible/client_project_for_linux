
#pragma once

#ifndef HeaderRequests
#define HeaderRequests

#include "HeaderMain.h"

PClient createANewCellFromTheUser(char* line);//Creating a new client from the user
void sortingByRequest(ListManager list);//Sort by request from the user
int testFunction(PNode root, void* value, char opr, int (*testing)(void*, PClient));//Sorting and printing function according to the request
void addingClientFromUser(ListManager* list, FILE* out);//Print a new line from the user to the file

#endif