
#include "HeaderDelet.h"
#include "HeaderTree.h"
#include "Globals.h"

void deletingACellFromTheList(PClient* currentCell) {//deleting a cell from the list
	if (*currentCell) {
		if ((*currentCell)->firstName)
			free((*currentCell)->firstName);//Releasing a first name string
		if ((*currentCell)->lastName)
			free((*currentCell)->lastName);//Releasing last name string
		if ((*currentCell)->id)
			free((*currentCell)->id);//Releasing an ID string
		if ((*currentCell)->phone)
			free((*currentCell)->phone);//Releasing a phone string
		free(*currentCell);//release current cell
		*currentCell = NULL;
	}
}

void deletingTheEntireList(ListManager manager) {//deleting the whole list
	while (manager->head) {//Checking the list is not empty
		PClient temp = manager->head;
		manager->head = manager->head->next;//Move the pointer to the next cell
		deletingACellFromTheList(&temp);//cell release
	}
	while (manager->headError) {//Checking the list is not empty
		PClient temp = manager->headError;
		manager->headError = manager->headError->next;//Move the pointer to the next cell
		deletingACellFromTheList(&temp);//cell release
	}
	free(manager);//Releasing the manager structure
}

void errorPrintingandDeletingACell(PClient* cell, char* str) {//printing an error and deleting a cell
	printf("%s", str);//printing an error
	deletingACellFromTheList(cell);//deleting a cell
}

void deletingArrayOfTree() {
	for (int i = 0; i < SIZE_ARRAY; i++) {
		deletingTree(&(arrayTree[i]->root));
		free(arrayTree[i]);
		arrayTree[i] = NULL;
	}
}

void deletingTree(PNode* root) {
	/*Check if the node is empty*/
	if (!(*root))
		return;

	/*Deleting the left tree*/
	if ((*root)->left)
		deletingTree(&((*root)->left));

	/*Deleting the right tree*/
	if ((*root)->right)
		deletingTree(&((*root)->right));

	if (!deletingNodeAndDeletingLikeds(root))
		return;
}

PNode deletingNodeAndDeletingLikeds(PNode* node) {
	/*Declaring the pointer variable Node*/
	PNode like = *node, temp;

	/*Check if the node is empty*/
	while (like) {
		temp = like;
		like = like->nextLike;
		free(temp);
		temp = NULL;
	}

	return NULL;
}

PNode deletingNode(PNode* node, void* val, int Enum) {

	/*Check if the node is empty*/
	if (!(*node))
		return NULL;

	/*Finding a replacement to the node*/
	PNode temp = findingAReplacementCell(*node, val, Enum);

	/*Deleting node*/
	free(*node);

	/*Applying the cell to NULL*/
	*node = NULL;

	/*Returning the replacement cell*/
	return temp;
}