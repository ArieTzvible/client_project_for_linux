
#include "CreatingManager.h"
#include "HeaderMain.h"
#include "HeaderTree.h"
#include "Globals.h"

void crateArrayTreeAndArrayFuncSort() {
	for (int i = 0; i < SIZE_ARRAY; i++) {
		arrayTree[i] = initRoot();
	}
	arrSortfunc[EnFirst] = testingFirstName;
	arrSortfunc[EnLast] = testingLastName;
	arrSortfunc[EnID] = testingID;
	arrSortfunc[EnPhone] = testingPhone;
	arrSortfunc[EnDebt] = testingDebt;
	arrSortfunc[EnDate] = testingDate;
}

PTree initRoot() {

	/*Creating a variable of type tree*/
	PTree tree = (PTree)malloc(sizeof(Tree));

	/*Put the root to NULL*/
	tree->root = NULL;

	/*Returning the tree*/
	return tree;
}

PNode createNodeTree(PClient client) {

	/*Creating a variable of type node*/
	PNode node = (PNode)malloc(sizeof(Node));

	/*Put the client to the client we received*/
	node->client = client;

	/*Set the elements to NULL*/
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	node->nextLike = NULL;

	/*Returning the node*/
	return node;
}

ListManager initANewListManager() //creating a manager structure
{
	ListManager temp = (ListManager)malloc(sizeof(List));//creating a new structure

	if (temp == NULL)
		printf("Not enough memory\n");//print error;//Error printing when there is no space in memory

	else
	{
		temp->head = NULL;//statement to the top of the list
		temp->headError = NULL;//statement to the top of the errors list 
	}

	return temp;//returning the structure
}

PClient initErrorsinAnewCell() //initialize a new client structure
{
	PClient newClient = (PClient)malloc(sizeof(Client));//Declaration and creation of a new structure

	if (!newClient)
	{
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return NULL;
	}

	newClient->next = NULL;
	newClient->firstName = NULL;
	newClient->lastName = NULL;
	newClient->id = NULL;
	newClient->phone = NULL;
	newClient->date.day = 0;
	newClient->date.month = 0;
	newClient->date.year = 0;
	newClient->debt = 0;
	newClient->error.ERROR = 0;
	newClient->error.firstName = 0;//error in first name
	newClient->error.lastName = 0;//Error in last name
	newClient->error.id = 0;//. Error in ID
	newClient->error.phone = 0;//Error on phone
	newClient->error.date = 0;//Error in date
	newClient->error.debt = 0;//Error in debt
	newClient->error.comparisonFirstName = 0;//record T.Z. Does not match first name
	newClient->error.comparisonLastName = 0;//Error ID Does not match last name
	newClient->error.lacksValues = 0;//Error Not enough values

	return newClient;
}

PClient creatingADeepCopyOfAClient(PClient curr) {
	PClient newClient = initErrorsinAnewCell();
	newClient->firstName = strdup(curr->firstName);
	newClient->lastName = strdup(curr->lastName);
	newClient->id = strdup(curr->id);
	newClient->phone = strdup(curr->phone);
	newClient->date = curr->date;
	newClient->debt = curr->debt;
	newClient->next = curr->next;
	if ((!newClient->firstName) || (!newClient->lastName) || (!newClient->id) || (!newClient->phone))
	{
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return NULL;
	}
	return newClient;
}

PClient createNewClientFromFile(char* line) {//creating a new customer from the file
	if (!*line) {
		free(line);
		return NULL;
	}
	PClient temp = initErrorsinAnewCell();//initialize a new client structure
	void (*arr[6])(PClient curr, char* string) = {
		fillingInAFirstName, fillingInALastName, fillingInAID,
		fillingInAPhone, fillingInADebt, fillingInADate };

	int i = 0;
	char* token;
	token = strtok(line, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer

	do {
		arr[i++](temp, token);
		token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
	} while (token && i < 6);

	//Checking that all values exist
	if (!(temp->firstName && temp->lastName && temp->id && temp->phone && temp->debt)) {
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values
	}
	if ((!temp->date.day) && (!temp->date.month) && (!temp->date.year))
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values

	free(line);
	return temp;
}

Date creatingANewDateStructure(char* date) {//create date
	Date temp = { 0 };//Creating a date structure type variable
	if (!date) return temp;//check that the received string contains characters
	char* strDate = date;//Declaration of a variable holding the resulting string
	if (((int)strlen(strDate) == 10) && (strDate[2] == '/' && strDate[5] == '/')) {//Is the date correct.
		char* token;
		token = strtok(date, "/");//accepting up to a comma (a cell in the file) and accepting it into a pointer
		if (isInt(token)) {//Is the number correct?
			int day = atoi(token);//Convert string to number
			if (day <= DAY && day > 0) {//Is the number in the normal range
				temp.day = day;// Application of the number in the designated cell
			}
		}
		token = strtok(NULL, "/");
		if (isInt(token)) {//Is the number correct?
			int month = atoi(token);//Convert string to number
			if (month <= MONTH && month > 0) {//Is the number in the normal range
				temp.month = month;// Application of the number in the designated cell
			}
		}
		token = strtok(NULL, "\n");
		if (isInt(token)) {//Is the number correct?
			int year = atoi(token);//Convert string to number
			if (year <= MAX_YEAR && year > MIN_YEAR) {//Is the number in the normal range
				temp.year = year;// Application of the number in the designated cell
			}
		}
	}
	return temp;//Return new cell
}

void creatingListOfClientsFromAFile(ListManager manager, FILE* file) {//creating a list from the file
	char* tempLine;
	while (!(feof(file))) {// checking whether the end of the file has been reached
		tempLine = GettingLine(file);//send to get a line from the file
		if (tempLine != NULL && *tempLine != '\n') {
			PClient temp = createNewClientFromFile(tempLine);// send to create a new cell
			testingTheNewCell(manager, &temp);//Testing new cell
		}
	}
}

void creatingTreesFromLinkedList(ListManager manager) {

	/*Check if the list is empty*/
	if ((!manager) || (!manager->head))
		return;

	/*Create a pointer to the client*/
	PClient temp = manager->head;

	/*A loop that goes over the list and sends to create a sorted tree*/
	while (temp) {

		/*Sending a client to enter in all sorting trees*/
		nsertingAClientIntoAllSortingTrees(temp);

		/*Move the pointer to the next cell*/
		temp = temp->next;
	}
}

void nsertingAClientIntoAllSortingTrees(PClient client) {
	/*Sending to the function to insert a cell in the first name tree*/
	arrayTree[EnFirst]->root = incomeForTheTree(arrayTree[EnFirst]->root, client, client->firstName, arrSortfunc[EnFirst]);
	/*Sending to the function to insert a cell in the last name tree*/
	arrayTree[EnLast]->root = incomeForTheTree(arrayTree[EnLast]->root, client, client->lastName, arrSortfunc[EnLast]);
	/*Sending to the function to insert a cell in the ID tree*/
	arrayTree[EnID]->root = incomeForTheTree(arrayTree[EnID]->root, client, client->id, arrSortfunc[EnID]);
	/*Sending to the function to insert a cell in the phone tree*/
	arrayTree[EnPhone]->root = incomeForTheTree(arrayTree[EnPhone]->root, client, client->phone, arrSortfunc[EnPhone]);
	/*Sending to the function to insert a cell in the debt tree*/
	arrayTree[EnDebt]->root = incomeForTheTree(arrayTree[EnDebt]->root, client, &(client->debt), arrSortfunc[EnDebt]);
	/*Sending to the function to insert a cell in the date tree*/
	arrayTree[EnDate]->root = incomeForTheTree(arrayTree[EnDate]->root, client, &(client->date), arrSortfunc[EnDate]);
}

void addToHeadTheList(PClient* head, PClient newCell)
{
	newCell->next = *head;
	*head = newCell;
}

/*A function for sorting and adding to the list*/
void addingASortedCustomerToTheList(PClient* head, PClient newCell)
{
	if (!newCell) return;

	if (*head == NULL || newCell->debt <= (*head)->debt) //Checking whether the first cell is empty
	{
		newCell->next = *head;//Bringing the customer to the top of the list
		*head = newCell;//Moving the pointer to the top of the list
		return;
	}

	PClient temp = *head;//Declare a pointer to the first cell in the list

	while (temp)
	{
		/*Test A: End of list. B: A debt smaller than the current debt*/
		if ((!temp->next) || (newCell->debt <= temp->next->debt))
		{
			newCell->next = temp->next;//Bringing the client to the current location
			temp->next = newCell;//Getting the next client on the list
			return;
		}

		temp = temp->next;//Move the pointer to the next cell
	}
}

/*Filling in the details in the client*/
void fillingInAFirstName(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->firstName = creatingADynamicCharWithContent(string);//Getting first name
}
void fillingInALastName(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->lastName = creatingADynamicCharWithContent(string);//Getting last name 
}
void fillingInAID(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->id = creatingADynamicCharWithContent(string);//Getting ID
}
void fillingInAPhone(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->phone = creatingADynamicCharWithContent(string);//Getting phone
}
void fillingInADebt(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	char* strDebt;//Creating a variable for a debt check without the minus
	strDebt = creatingADynamicCharWithContent(string);//Getting debt
	if (strDebt && isNegativeFloat(strDebt))
		curr->debt = stringConversionToFloat(string);//Receiving the number for the client
	else
		curr->error.ERROR = curr->error.debt = 1;//error in receiving the debt
	free(strDebt);
}
void fillingInADate(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->date = creatingANewDateStructure(string);//send to create a date
	if ((!curr->date.day) && (!curr->date.month) && (!curr->date.year))
		curr->error.lacksValues = curr->error.ERROR = 1;//Missing values
	else if (!(curr->date.day && (curr->date.month) && curr->date.year))// check that all date values exist
		curr->error.ERROR = curr->error.date = 1;// Error in date
}

/*Finding the place to insert the tree*/
PNode incomeForTheTree(PNode root, PClient client, void* value, int (*sort)(void*, PClient)) {

	int test;/*Create a variable for the test result*/

	/*Check if the client is empty*/
	if (!value)
		return NULL;

	/*Checking whether the root is valuable*/
	if (!root) {
		/*Creating new node and Returning a value in the root*/
		return createNodeTree(client);
	}

	/*Comparison in a specific function and assignment to the test variable*/
	test = sort(value, root->client);

	/*If there is equality between the cells*/
	if (test == 0) {

		/*Create a pointer to the node*/
		PNode temp = root;

		/*A loop for finding the last similar pointer*/
		while (temp->nextLike)
			temp = temp->nextLike;/*Moving the pointer to the next similar cell*/

		/*Place the cell in the following similar pointer*/
		temp->nextLike = createNodeTree(client);

		/*Place the cell in the parent pointer to the temp cell*/
		temp->nextLike->father = temp;

		return root;
	}

	/*If the current cell is greater than the cell temp*/
	else if (test > 0) {
		/*sending the right tree*/
		root->right = incomeForTheTree(root->right, client, value, sort);
		root->right->father = root;
	}


	/*Checking whether the current cell is smaller than the temp cell*/
	else if (test < 0) {
		/*sending the left tree*/
		root->left = incomeForTheTree(root->left, client, value, sort);
		root->left->father = root;
	}

	return inspectionandRepairOfAVLTree(root, value, sort);


}
PNode findingandApplyingASimilarCell(PNode node) {

	PNode temp = NULL;

	if (node->nextLike) {
		temp = node->nextLike;
		temp->father = node->father;
		temp->left = node->left;
		temp->right = node->right;
	}

	return temp;
}
PNode findingandApplyingASubsequentCell(PNode node, void* val, int Enum) {
	PNode temp = NULL;

	if (node->right) {
		temp = (node->right);

		while (temp->left)
			temp = temp->left;

		if (temp->right) {
			temp->right->father = temp->father;
			temp->father->left = temp->right;
		}
		temp->father = node->father;
		temp->left = node->left;
	}

	else if (node->left) {
		temp = node->left;
		temp->father = node->father;
	}

	return inspectionandRepairOfAVLTree(temp, val, arrSortfunc[Enum]);

}