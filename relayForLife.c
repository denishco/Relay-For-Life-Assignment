// Deniz Erdem
// June 22 2018
// Relay For Life Summaitve

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct participant {
	char fname[32];
	char lname[32];
	int grade;
	char homeroom[32];
	char teamName[32];
	int teamNum;
	int kitNum;
};

struct donation {
	char fname[32];
	char lname[32];
	char addr[32];
	int amount;
	int kitNum;
};

// Globals
int totalParts = 0;
struct participant partArray[100];

int totalDons = 0;
struct donation donArray[100];

char partFileName[32] = "participants.txt";
char donFileName[32] = "donations.txt";

// Functions
void initPartEmpty (struct participant p) {
	strcpy(p.fname, "");
	strcpy(p.lname, "");
	p.grade = 0;
	strcpy(p.homeroom, "");
	strcpy(p.teamName, "");
	p.teamNum = 0;
	p.kitNum = 0;
}

void initDonEmpty (struct donation d) {
	strcpy(d.fname, "");
	strcpy(d.lname, "");
	strcpy(d.addr, "");
	d.amount = 0;
	d.kitNum = 0;
}

void initPart(struct participant* p, char _fname[32], char _lname[32], int _grade, char _homeroom[32], char _teamName[32], int _teamNum, int _kitNum) {
	strcpy((*p).fname, _fname);
	strcpy((*p).lname, _lname);
	(*p).grade = _grade;
	strcpy((*p).homeroom, _homeroom);
	strcpy((*p).teamName, _teamName);
	(*p).teamNum = _teamNum;
	(*p).kitNum = _kitNum;
}

void initDon(struct donation* d, char _fname[32], char _lname[32], char _addr[32], int _amount, int _kitNum) {
	strcpy((*d).fname, _fname);
	strcpy((*d).lname, _lname);
	strcpy((*d).addr, _addr);
	(*d).amount = _amount;
	(*d).kitNum = _kitNum;
}

void addPart(struct participant p) {
	partArray[totalParts] = p;
	totalParts++;
}

void deletePart(struct participant p) {
	int partIndex = indexPartByKitNum(p.kitNum);
	int i;
	for (i = partIndex; i < 100 - 1; i++) {
		// Shift array to the left by 1 overwriting the one we want to delete
		partArray[i] = partArray[i + 1];
	}

	totalParts--;
}


void writePart(struct participant p) {
	FILE* fp;
	fp = fopen(partFileName, "a");

	if(fp == NULL){
		printf("\nError opening file:%s\n", partFileName);
		return 0;
	} else {
		fprintf(fp, "%s\n", p.fname);
		fprintf(fp, "%s\n", p.lname);
		fprintf(fp, "%i\n", p.grade);
		fprintf(fp, "%s\n", p.homeroom);
		fprintf(fp, "%s\n", p.teamName);
		fprintf(fp, "%i\n", p.teamNum);
		fprintf(fp, "%i\n", p.kitNum);
	}

	fclose(fp);
}

void writeParts() {
	int i = 0;
	for (i = 0; i < totalParts; i++) {
		writePart(partArray[i]);
	}
}

void printPart(struct participant p) {
	printf("First name:%s\n", p.fname);
	printf("Last name:%s\n", p.lname);
	printf("Grade:%i\n", p.grade);
	printf("Homeroom:%s\n", p.homeroom);
	printf("Team name:%s\n", p.teamName);
	printf("Team number:%i\n", p.teamNum);
	printf("Kit number:%i\n\n", p.kitNum);
}

void viewAllParts() {
	int i = 0;
	for (i = 0; i < totalParts; i++) {
		printPart(partArray[i]);
	}
}

void addDon(struct donation p) {
	donArray[totalDons] = p;
	totalDons++;
}

void deleteDon(struct donation d) {
	int donIndex = indexDonByKitNum(d.kitNum);
	int i;
	for (i = donIndex; i < 100 - 1; i++) {
		// Shift array to the left by 1 overwriting the one we want to delete
		donArray[i] = donArray[i + 1];
	}

	totalDons--;
}

void writeDon(struct donation d) {
	FILE* fp;
	fp = fopen(donFileName, "a");

	if(fp == NULL){
		printf("\nError opening file:%s\n", donFileName);
		return 0;
	} else {
		fprintf(fp, "%s\n", d.fname);
		fprintf(fp, "%s\n", d.lname);
		fprintf(fp, "%s\n", d.addr);
		fprintf(fp, "%i\n", d.amount);
		fprintf(fp, "%i\n", d.kitNum);
	}

	fclose(fp);
}

void clearFile(char* fileName) {
	FILE* fp;
	fp = fopen(fileName, "w");
	fclose(fp);
}

void writeDons() {
	int i = 0;
	for (i = 0; i < totalDons; i++) {
		writeDon(donArray[i]);
	}
}

void readDons() {
	FILE* fp;

	fp = fopen(donFileName, "r");
	if(fp == NULL){
		printf("\nError opening file:%s\n", donFileName);
		return 0;
	}else{
		char line[256];
		int i = 0;
		int j = 0;
		while (fgets(line, sizeof(line), fp)) {
			struct donation newDon;
			switch (j) {
				case 0:
					if (line == '\n') {
						return;
					}
					strcpy(newDon.fname, line);
					break;
				case 1:
					strcpy(newDon.lname, line);
					break;
				case 2:
					strcpy(newDon.addr, line);
					break;
				case 3:
					newDon.amount = atoi(line);
					break;
				case 4:
					newDon.kitNum = atoi(line);
					addDon(newDon);
					j = -1;
					i++;
					break;
			}
			j++;
		}
	}

	fclose(fp);
}

void printDon(struct donation d) {
	printf("First name:%s\n", d.fname);
	printf("Last name:%s\n", d.lname);
	printf("Address:%s\n", d.addr);
	printf("Amount:%i\n", d.amount);
	printf("Kit number:%i\n\n", d.kitNum);
}

void viewAllDons() {
	int i = 0;
	for (i = 0; i < totalDons; i++) {
		printDon(donArray[i]);
	}
}

int donsPerPart(int kitNum) {
	int td = 0;
	int i = 0;
	for (i = 0; i < totalDons; i++) {
		if(donArray[i].kitNum == kitNum) {
			td += donArray[i].amount;
		}
	}

	return td;
}

int donsPerTeam(int teamNum) {
	int td = 0;
	int i = 0;
	for (i = 0; i < totalParts; i++) {
		if(partArray[i].teamNum == teamNum) {
			td += donsPerPart(partArray[i].kitNum);
		}
	}

	return td;
}

void swap(struct participant* xp, struct participant* yp) {
	struct participant temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSortParts() {
	int i, j;
	for (i = 0; i < 100-1; i++) {
		for (j = 0; j < 100-i-1; j++) {
			if (donsPerPart(partArray[j].kitNum) < donsPerPart(partArray[j+1].kitNum)) {
				swap(&partArray[j], &partArray[j+1]);
			}
		}
	}
}

void bubbleSortTeams() {
	int i, j;
	for (i = 0; i < 100-1; i++) {
		for (j = 0; j < 100-i-1; j++) {
			if (donsPerTeam(partArray[j].teamNum) < donsPerTeam(partArray[j+1].teamNum)) {
				swap(&partArray[j], &partArray[j+1]);
			}
		}
	}
}

void printTop5Teams() {
	bubbleSortTeams();
	int i = 0;
	for (i = 0; i < 5; i++) {
		printf("\n------------------------\n");
		printf("\nTeam %i\n", i);
		printf("------------------------\n");
		printf("\nTeam %i\n", i);
		printf("\nTeam number %i\n", partArray[i].teamNum);
		printf("\nTeam name %s\n", partArray[i].teamName);
		printf("\nTeam donations $%i\n\n", donsPerTeam(partArray[i].teamNum));
	}
}

void printTop5Parts(){
	bubbleSortParts();
	int i = 0;
	for (i = 0; i < 5; i++) {
		printf("\n------------------------\n");
		printf("\nParticipant %i\n", i);
		printf("------------------------\n");
		printf("\nParticipant kit number %i\n", partArray[i].kitNum);
		printf("\nParticipant donations $%i\n\n", donsPerPart(partArray[i].kitNum));
	}
}

int donExists(int kitNum) {
	int i = 0;
	for (i = 0; i < totalDons; i++) {
		if (donArray[i].kitNum == kitNum) {
			return 1;
		}
	}

	return 0;
}

int partExists(int kitNum) {
	int i = 0;
	for (i = 0; i < totalParts; i++) {
		if (partArray[i].kitNum == kitNum) {
			return 1;
		}
	}

	return 0;
}

void addPartDon(int kitNum, int donAmount, char* fname, char* lname, char* addr) {
	struct donation newDon;
	initDon(&newDon, fname, lname, addr, donAmount, kitNum);
	addDon(newDon);
}

void readParts(){
	FILE* fp;

	fp = fopen(partFileName, "r");
	if(fp == NULL){
		printf("\nError opening file:%s\n", partFileName);
		return 0;
	}else{
		char line[256];
		int j = 0;
		while (fgets(line, sizeof(line), fp)) {
			struct participant newPart;
			switch (j) {
				case 0:
					if (line == '\n') {
						return;
					}
					strcpy(newPart.fname, line);
					break;
				case 1:
					strcpy(newPart.lname, line);
					break;
				case 2:
					newPart.grade = atoi(line);
					break;
				case 3:
					strcpy(newPart.homeroom, line);
					break;
				case 4:
					strcpy(newPart.teamName, line);
					break;
				case 5:
					newPart.teamNum = atoi(line);
					break;
				case 6:
					newPart.kitNum = atoi(line);
					addPart(newPart);
					j = -1;
					break;
			}
			j++;
		}
	}

	fclose(fp);
}

int indexPartByKitNum(int kitNum) {
	int i = 0;
	for (i = 0; i < totalParts; i++) {
		if (partArray[i].kitNum == kitNum) {
			return i;
		}
	}

	return -1;
}

int indexDonByKitNum(int kitNum) {
	int i = 0;
	for (i = 0; i < totalDons; i++) {
		if (donArray[i].kitNum == kitNum) {
			return i;
		}
	}

	return -1;
}

// User interface stuff --------------------------------------------------
int getUserNum(char query[64]) {
	int inputIsValid = 0;
	char input[16];
	int totalNums = 0;
	int result = 0;

	while(inputIsValid == 0){
		printf("%s", query);

		scanf("%s", input);

		if (input[0] == '0') {
			return 0;
		} else if (atoi(input) == 0) {
			system("cls");
			printf("Invalid input\n");
		} else {
			return atoi(input);
		}

	}
}

void donsPertTeamMenu() {
	printf("$%i\n", donsPerTeam(getUserNum("Enter team num: ")));
}

void donsPerPartMenu() {
	printf("$%i\n", donsPerPart(getUserNum("Enter kit num: ")));
}

void addDonMenu() {
	struct donation newDon;
	char value[32];

	printf("Enter first name: ");
	scanf("%s", value);
	strcpy(newDon.fname, value);

	printf("Enter last name: ");
	scanf("%s", value);
	strcpy(newDon.lname, value);

	printf("Enter address: ");
	scanf("%s", value);
	strcpy(newDon.addr, value);

	newDon.amount = getUserNum("Enter donation amount: ");

	newDon.kitNum = getUserNum("Enter kit number: ");

	addDon(newDon);
}

void deletePartMenu() {
	int inputIsValid = 0;
	int kitNum;
	int partIndex;

	while(inputIsValid == 0){
		printf("Enter participant kit number: ");
		scanf("%i", &kitNum);

		if (partExists(kitNum) == 0) {
			printf("Participant does not exist\n");
		} else {
			inputIsValid = 1;
		}
	}

	partIndex = indexPartByKitNum(kitNum);

	deletePart(partArray[partIndex]);
}

void addPartMenu() {
	struct participant newPart;
	char value[32];

	printf("Enter first name: ");
	scanf("%s", value);
	strcpy(newPart.fname, value);

	printf("Enter last name: ");
	scanf("%s", value);
	strcpy(newPart.lname, value);

	newPart.grade = getUserNum("Enter grade: ");

	printf("Enter home room: ");
	scanf("%s", value);
	strcpy(newPart.homeroom, value);

	printf("Enter team name: ");
	scanf("%s", value);
	strcpy(newPart.teamName, value);

	newPart.teamNum = getUserNum("Enter team number: ");

	newPart.kitNum = getUserNum("Enter kit number: ");

	addPart(newPart);
}

void editPartMenu() {
	int inputIsValid = 0;
	int kitNum;
	char input;
	int partIndex;

	kitNum = getUserNum("Enter participant kit number: ");

	if (partExists(kitNum) == 0) {
		printf("Participant does not exist\n");
		return;
	}

	partIndex = indexPartByKitNum(kitNum);

	inputIsValid = 0;

	while(inputIsValid == 0){
		printPart(partArray[partIndex]);
		printf("What would you like to edit\n");
		printf("1. First name\n");
		printf("2. Last name\n");
		printf("3. Grade\n");
		printf("4. Homeroom\n");
		printf("5. Team name\n");
		printf("6. Team number\n");

		scanf("%c", &input);

		if(input >= 48 && input <= 57){
			inputIsValid = 1;
		}else{
			system("cls");
			printf("Invalid input\n");
		}
	}

	int choice = input - 48;

	char value[32];

	switch(choice) {
		case 1:
			printf("Enter first name: ");
			scanf("%s", value);
			strcpy(partArray[partIndex].fname, value);
			break;
		case 2:
			printf("Enter last name: ");
			scanf("%s", value);
			strcpy(partArray[partIndex].lname, value);
			break;
		case 3:
			partArray[partIndex].grade = getUserNum("Enter grade: ");
			break;
		case 4:
			printf("Enter home room: ");
			scanf("%s", value);
			strcpy(partArray[partIndex].homeroom, value);
			break;
		case 5:
			printf("Enter team name: ");
			scanf("%s", value);
			strcpy(partArray[partIndex].teamName, value);
			break;
		case 6:
			partArray[partIndex].teamNum = getUserNum("Enter team number: ");
			break;
		default:
			printf("Invalid choice\n");
			break;
	}
}

int mainMenu() {
	int inputIsValid = 0;
	char input;

	while(inputIsValid == 0){
		printf("------------------------\n");
		printf("|Relay For Life Manager|\n");
		printf("------------------------\n\n\n");

		printf("1. View all participants\n");
		printf("2. Edit participant\n");
		printf("3. Add participant\n");
		printf("4. Delete participant\n");
		printf("5. Add donation\n");
		printf("6. View total donations per participant\n");
		printf("7. View total donations per team\n");
		printf("8. View top 5 teams\n");
		printf("9. View top 5 participants\n");
		printf("0. Quit the program\n");
		printf("Choice: ");
		scanf("%c", &input);

		if(input >= 48 && input <= 57){
			inputIsValid = 1;
		}else{
			system("cls");
			printf("Invalid input\n");
		}
	}

	int choice = input - 48;

	system("cls");
	switch(choice) {
		case 1:
			viewAllParts();
			system("pause");
			break;
		case 2:
			editPartMenu();
			system("pause");
			break;
		case 3:
			addPartMenu();
			system("pause");
			break;
		case 4:
			deletePartMenu();
			system("pause");
			break;
		case 5:
			addDonMenu();
			system("pause");
			break;
		case 6:
			donsPerPartMenu();
			system("pause");
			break;
		case 7:
			donsPertTeamMenu();
			system("pause");
			break;
		case 8:
			printTop5Teams();
			system("pause");
			break;
		case 9:
			printTop5Parts();
			system("pause");
			break;
		case 0:
			return 1;
			break;
		default:
			printf("Invalid choice\n");
			break;
	}

	return 0;
}

void testInit() {
	// Add a bunch of test participants
	struct donation d1, d2, d3;
	initDon(&d1, "Bob", "Joe", "500 march road", 300, 1);
	initDon(&d2, "Stacy", "Gds", "530 march road", 300, 1);
	initDon(&d3, "Ken", "Fds", "530 march road", 300, 1);
	addDon(d1);
	addDon(d2);
	addDon(d3);
	writeDons();

	// Add a bunch of test donations
	struct participant p1, p2, p3;
	initPart(&p1, "Joe", "Dj", 100, "test", "test", 34, 1);
	initPart(&p2, "Joe", "Dj", 100, "test", "test", 34, 1);
	initPart(&p3, "Joe", "Dj", 100, "test", "test", 34, 1);
	addPart(p1);
	addPart(p2);
	addPart(p3);
	writeParts();
}

// Main ------------------------------------------------------------------
int main () {
	// Uncomment for testing
	// clearFile(partFileName);
	// clearFile(donFileName);
	//testInit();

	int done = 0;

	// Read database
	readDons();
	readParts();

	while (done == 0) {
		// Display main menu
		done = mainMenu();
	}

	// Save everything to database
	writeParts();
	writeDons();

	return 0;
}

