
#include "HeaderUtilities.h"

int isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return 1;
	return 0;
}

int isInt(char* num) {//Checking the correctness of the int in the string
	if (!num) return 0;
	size_t length = strlen(num);
	for (int i = 0; i < length; i++)
		if (!isNum(num[i]))
			return 0;
	return 1;
}

int isFloat(char* num) {//Checking the correctness of the float in the string
	if (!num) return 0;
	size_t length = strlen(num);
	for (int i = 0; i < length; i++)
		if ((num[i] != '.') && (!isNum(num[i])))
			return 0;
	return 1;
}

int isNegativeFloat(char* num) {
	if (*num == '-')
		return isFloat(num + sizeof(char));
	else
		return isFloat(num);
}

int isNegativeInt(char* num) {
	if (*num == '-')
		return isInt(num + sizeof(char));
	else
		return isInt(num);
}

int isLetter(char* ch) {
	if ((*ch < 'a') || (*ch > 'z')) {//Checking that the character is a letter
		if ((*ch < 'A') || (*ch > 'Z')) //Checking and converting an uppercase letter to lowercase
			return 0;
		*ch += 32;//Converting an uppercase letter to a lowercase letter
	}
	return 1;
}

int isTheStringCorrect(char* string) {//Checking the correctness of the letters and changing uppercase to lowercase letters
	char* tempStr = string;
	while ((tempStr) && (*tempStr != '\0') && (*tempStr != '\n')) {
		if (*tempStr != ' ')//Skipping profits
			if (!isLetter(tempStr))
				return 0;
		tempStr++;
	}
	return 1;
}

float stringConversionToFloat(char* strFloat) {
	float debt1 = 100 * (float)atof(strFloat);
	int debt2 = (int)debt1;//Multiply the debt by one hundred
	return debt2 / (float)100;//Returning the debt with two decimal digits
}

char* GettingLine(FILE* file) {//getting a complete line from the file
	char* input = NULL;//statement about a pointer to a row that the user entered
	char string[200];//Declaration of a variable
	fgets(string, 200, file);//Getting a string from the file
	if (feof(file)) return NULL;//Returning NULL when reaching the end of the file
	input = strdup(string);//Creating a variable and copying the string
	if (!input) {// checking whether there is space in the memory
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return input;
	}
	if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\0') {//Checking whether the entire line was received
		input[strlen(input) - 1] = '\0';//Changing the last cell to \0
		return input;
	}

	char tempBuf[CHUNK] = { 0 };//Declaration of a variable to receive values from the user
	size_t tempLen = 0, inputLen = strlen(input);//declaration of variables to test the length of the received line
	do {
		fgets(tempBuf, CHUNK, file);// getting 10 cells from the row
		tempLen = (int)strlen(tempBuf);//put the number of characters received
		char* temp = (char*)realloc(input, (inputLen + tempLen + 1) * sizeof(char));//adding space to receive the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else
			input = temp;//getting the new length of the string
		strcpy(input + inputLen, tempBuf);// Copy from the last location we copied
		inputLen += tempLen;//Getting the current string length

	} while (tempLen == CHUNK - 1 && tempBuf[CHUNK - 2] != '\n');
	if (input[strlen(input) - 1] == '\n')// Checking if the last location contains '\n'
		input[strlen(input) - 1] = '\0';//set the last place to \0
	else {//
		char* temp = (char*)realloc(input, (strlen(input) + 1) * sizeof(char));//Add a space to the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else {//If the end of the file is reached (in the case of reading from a file)
			input = temp;//getting the new length of the string
			input[strlen(input)] = '\0'; // set the last place to \0
		}
	}
	return input;
}

char* creatingADynamicCharWithContent(char* string) {//Creating a dynamic variable with content
	if (!string) return NULL;//testing that we received a value
	while (*string == ' ' || *string == '\t') string++;//skipping all spaces before the string
	int i = (int)strlen(string) - 1;//creating a variable of the length of the string
	while (string[i] == ' ' || string[i] == '\t') string[i--] = '\0';// deletes all spaces after the string
	char* temp = (char*)malloc((strlen(string) + 1) * sizeof(char));// Create a dynamic variable with the size of the string
	if (!temp) {// check that the allocation was successful
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return NULL;// Returning an error
	}
	else {
		strcpy(temp, string);//copying the string we received from the user to the string we allocated space for
		temp[strlen(temp)] = '\0';//string closure
	}
	return temp;
}

char* getNewFileName(char* extension) {//Requesting another file name
	printf("\n\tEnter a file name: ");
	char* string = GettingLine(stdin);//getting a line from the user includes creating a dynamic string
	if (strcmp((string + (strlen(string) - strlen(extension))), extension)) {// check that there is no file name at the end(CSV)		
		char* str = (char*)malloc((strlen(string) + strlen(extension) + 1) * sizeof(char));//creating a string that will also contain the document extension
		if (!str)//testing whether the allocation was successful
			printf("Not enough memory\n");//print error;//Error printing when there is no space in memory
		else {
			strcpy(str, string);//copy the string received from the user
			strcat(str, extension);//copy the file extension
			strcat(str, "\0");//adding 0\ at the end of the string
			free(string);//release the string we received from the user
			string = str;//setting the string to the string to send
		}
	}
	return string;//sending a pointer with the file name
}
