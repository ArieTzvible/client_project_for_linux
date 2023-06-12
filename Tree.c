
#include "HeaderTree.h"
#include "Globals.h"

//**** AVL *******
PNode inspectionandRepairOfAVLTree(PNode root, void* val, int (*sort)(void*, PClient)) {
	/*Finding the balance factor*/
	int balance = balanceFactor(root);

	if (balance > 1 || balance < -1) {
		return rotation(root, balance, val, sort);
	}

	return root;
}

/*Finding the height of the tree*/
int hightTree(PNode root) {
	if (!root)
		return -1;

	if ((!root->left) && (!root->right))
		return 0;

	return 1 + max_(hightTree(root->left), hightTree(root->right));
}

int max_(int a, int b){
	return a > b ? a : b;
}

/*Finding the balance factor*/
int balanceFactor(PNode root) {
	if (!root)
		return 0;

	return hightTree(root->left) - hightTree(root->right);
}

/*Left Rotate*/
PNode leftRotate(PNode Father) {
	if (!Father)
		return NULL;

	Node* movingAxis = Father->right;
	Node* Adoption = movingAxis->left;

	// Perform rotation
	movingAxis->left = Father;
	Father->father = movingAxis;
	Father->right = Adoption;
	if (Adoption)
		Adoption->father = Father;

	movingAxis->father = NULL;

	// Return new root
	return movingAxis;
}

/*Right Rotate*/
PNode rightRotate(PNode Father) {
	if (!Father)
		return NULL;

	PNode movingAxis = Father->left;
	PNode Adoption = movingAxis->right;

	// Perform rotation
	movingAxis->right = Father;
	Father->father = movingAxis;
	Father->left = Adoption;
	if (Adoption)
		Adoption->father = Father;

	movingAxis->father = NULL;

	// Return new root
	return movingAxis;
}

/*Rotation to receive an AVL tree*/
PNode rotation(PNode root, int balance, void* val, int (*sort)(void*, PClient)) {
	if (!root)
		return NULL;

	int isValBigger;
	PNode temp = root;
	if (balance > 1) {
		/*Checking whether the val is greater than the left pointer*/
		isValBigger = sort(val, root->left->client);

		// Left Left Case
		if (isValBigger < 0)
			return rightRotate(root);
		// Left Right Case
		if (isValBigger > 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}

	else {
		/*Checking whether the val is greater than the right pointer*/
		isValBigger = sort(val, root->right->client);

		// Right Right Case
		if (isValBigger > 0)
			return leftRotate(root);

		// Right Left Case
		if (isValBigger < 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

PNode findingAReplacementCell(PNode node, void* val, int Enum) {

	if (!node)
		return NULL;

	if (node->nextLike)
		return findingandApplyingASimilarCell(node);

	return findingandApplyingASubsequentCell(node, val, Enum);
}

void cellUpdateInTrees(PClient* newCell, PClient* currCell) {//Cell update

	//***    Cell update   **********
	float prevDebt = (*currCell)->debt;
	(*currCell)->debt += (*newCell)->debt;
	takingOutCellAndInsertToTree(*currCell, EnDebt, &prevDebt, &((*newCell)->debt));

	if (comparingDates((*newCell)->date, (*currCell)->date) > 0) //Checking if the new cell's date is closer
	{
		Date prevDate = {0};
		prevDate.day = (*currCell)->date.day;
		prevDate.month = (*currCell)->date.month;
		prevDate.year = (*currCell)->date.year;

		(*currCell)->date = (*newCell)->date;

		takingOutCellAndInsertToTree(*currCell, EnDate, &prevDate, &((*newCell)->date));
		
		if (strcmp((*currCell)->phone, (*newCell)->phone)) {//Update the phone in the current cell
			char prevPhone[11];
			strcpy(prevPhone, (*currCell)->phone);

			free((*currCell)->phone);

			(*currCell)->phone = creatingADynamicCharWithContent((*newCell)->phone);//Getting a new string for the phone

			takingOutCellAndInsertToTree(*currCell, EnPhone, prevPhone, (*currCell)->phone);
		}
	}
}

void takingOutCellAndInsertToTree(PClient client, int Enum, void* prevVal, void* currVal) {
	PTree t = arrayTree[Enum];
	PNode nodeCurr, temp;

	nodeCurr = findingAClientByParameter(arrayTree[Enum]->root, prevVal, arrSortfunc[Enum]);
	if (!nodeCurr)
		return;

	temp = nodeCurr;

	while (arrSortfunc[EnID](temp->client->id, client)) {
		temp = temp->nextLike;
	}

	// Inspectionand repair of AVL tree.
	while (temp) {
		temp = inspectionandRepairOfAVLTree(temp, currVal, arrSortfunc[Enum]);
		temp = temp->father;
	}
	if (nodeCurr->father->left == nodeCurr)
		nodeCurr->father->left = NULL;
	else if (nodeCurr->father->right == nodeCurr)
		nodeCurr->father->right = NULL;

	free(nodeCurr);
	nodeCurr = NULL;
	arrayTree[Enum]->root = incomeForTheTree(arrayTree[Enum]->root, client, currVal, arrSortfunc[Enum]);

}

PNode findingAClientByParameter(PNode root, void* value, int (*sort)(void*, PClient)) {
	if (!root)
		return NULL;

	int test = sort(value, root->client);//getting the test value

	if (test < 0)
		return findingAClientByParameter(root->left, value, sort);

	else if (test > 0)
		return findingAClientByParameter(root->right, value, sort);

	else
		return root;

}