#pragma once

#ifndef HeaderTree
#define HeaderTree
#include "HeaderMain.h"

//*** A V L *******
PNode inspectionandRepairOfAVLTree(PNode root, void* val, int (*sort)(void*, PClient));
/*Rotation to receive an AVL tree*/
PNode rotation(PNode root, int balance, void* val, int (*sort)(void*, PClient));
/*Finding the height of the tree*/
int hightTree(PNode root);
/*Finding the balance factor*/
int balanceFactor(PNode root);
/*Left Rotate*/
PNode leftRotate(PNode father);
/*Right Rotate*/
PNode rightRotate(PNode father);

PNode findingAReplacementCell(PNode node, void* val, int Enum);
PNode findingAClientByParameter(PNode root, void* value, int (*sort)(void*, PClient));
void takingOutCellAndInsertToTree(PClient client, int Enum, void* prevVal, void* currVal);
void cellUpdateInTrees(PClient* newCell, PClient* curr);

int max_(int a, int b);

#endif