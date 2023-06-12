
#pragma once

#ifndef CreatingManager
#define CreatingManager

#include "HeaderTest.h"

void crateArrayTreeAndArrayFuncSort();

PTree initRoot();//Root initialization
ListManager initANewListManager();//Creating a new manager structure
PClient initErrorsinAnewCell();//Creating a structure of a new client

/*Creating a trees*/
PNode createNodeTree(PClient client);
void creatingTreesFromLinkedList(ListManager manager);
void nsertingAClientIntoAllSortingTrees(PClient client);
PNode incomeForTheTree(PNode root, PClient client, void* value, int (*sort)(void*, PClient));
PNode findingandApplyingASimilarCell(PNode node);
PNode findingandApplyingASubsequentCell(PNode node, void* val, int Enum);

/*Creating a client*/
void fillingInAFirstName(PClient curr, char* string);
void fillingInALastName(PClient curr, char* string);
void fillingInAID(PClient curr, char* string);
void fillingInAPhone(PClient curr, char* string);
void fillingInADebt(PClient curr, char* string);
void fillingInADate(PClient curr, char* string);
PClient creatingADeepCopyOfAClient(PClient curr);
PClient createNewClientFromFile(char* line);//Create a new cell from the file
void creatingListOfClientsFromAFile(ListManager manager, FILE* file);//creating a list from the file
Date creatingANewDateStructure(char* date);//Create a new date

void addToHeadTheList(PClient* head, PClient newCell);//add to the top of the list
void addingASortedCustomerToTheList(PClient* head, PClient newCell);//Sorting and adding to the list

#endif