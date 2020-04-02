#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int testFileName(char* fname);
int countLinesInFile(FILE* fp);
double age(int present_date, int present_month, int present_year, int birth_date, int birth_month, int birth_year);
typedef struct {
	char name[50];
	char surname[50];
}Personal;
typedef struct {
	int day;
	int month;
	int year;
}dateofbirth;
typedef struct {
	Personal person;
	dateofbirth birthday;
	int marks[10];
	struct student* mNext;
}student;
void SwapElements(student* man1, student* man2);
void delete(student* man1);
int main()
{
	FILE* fp;
	fp = NULL;
	char* filename[45];
	do {
		strcpy(filename, "C:\\Andriy\\Cprogram\\lab10\\laba10.txt");
		if (testFileName(filename)) {
			fp = NULL;
			fp = fopen(filename, "r+");//file opening
			if (!fp) {
				printf("Can't open file\n");
				getchar();

			}
			else {
				break;
			}
		}
		else {
			printf("File isn't exists\n");
			getchar();
		}
	} while (1);

	//check number of lines in file for reading data
	int nOfNodesInFile = countLinesInFile(fp); 
	printf("Amount of nodes in file %d.\n", nOfNodesInFile);
	//memory allocating
	student* start = NULL;
	student* studic = (student*)malloc(sizeof(student));
	student* students = (student*)malloc(nOfNodesInFile * sizeof(student));
	//cycle for data reading
	for (int i = 0; i < nOfNodesInFile; i++) {
		if (!start) start = studic;
		fscanf(fp, "%s", &studic->person.surname);
		fscanf(fp, "%s", &studic->person.name);
		fscanf(fp, "%d", &studic->birthday.day);
		fscanf(fp, "%d", &studic->birthday.month);
		fscanf(fp, "%d", &studic->birthday.year);
		for (int j = 0; j < 5; j++) {
			fscanf(fp, "%d", &studic->marks[j]);
		}
		struct student* past = (student*)malloc(sizeof(student));
		studic->mNext = past;
		studic = past;
	}
	studic->mNext = NULL;
	studic = start;
	//printing of list
	while (studic->mNext != NULL)
	{
		printf("-------------------------------------------------------------------\n");
		printf("|%s    %s    %d    %d    %d ", studic->person.surname, studic->person.name, studic->birthday.day, studic->birthday.month, studic->birthday.year);
		for (int j = 0; j < 5; j++) {
			printf("%d ", studic->marks[j]);
		}
		printf("|\n");
		studic = studic->mNext;
	}


	printf("-------------------------------------------------------------------\n");
	printf("\n-------------------------------------------------------------------\n");
	//allocate memory for extra student
	student* NewStudent = (student*)malloc(sizeof(student));

	printf("Enter surname of new student:");
	scanf("%s", &NewStudent->person.surname);
	printf("Enter name of new student:");
	scanf("%s", &NewStudent->person.name);
	printf("Enter day of birthday of new student:");
	scanf("%d", &NewStudent->birthday.day);
	printf("Enter month of birthday of new student:");
	scanf("%d", &NewStudent->birthday.month);
	printf("Enter year of birthday of new student:");
	scanf("%d", &NewStudent->birthday.year);
	printf("Enter all marks of new student:");
	for (int j = 0; j < 5; j++) {
		scanf("%d ", &NewStudent->marks[j]);
	}



	studic = start;
	start = NewStudent;
	NewStudent->mNext = studic;
	while (studic->mNext != NULL)
	{
		studic = studic->mNext;
	}


	studic->mNext = NULL;

	studic = start;
	do
	{
		printf("-------------------------------------------------------------------\n");
		printf("|%s    %s    %d    %d    %d ", studic->person.surname, studic->person.name, studic->birthday.day, studic->birthday.month, studic->birthday.year);
		for (int j = 0; j < 5; j++) {
			printf("%d ", studic->marks[j]);

		}

		printf("|\n");
		studic = studic->mNext;
	} while (studic->mNext != NULL);
	printf("-------------------------------------------------------------------\n");
	printf("\n-------------------------------------------------------------------\n");

	int present_date = 16;
	int present_month = 12;
	int present_year = 2019;

	double avgage = 0;
	studic = start;
	for (int i = 0; i < nOfNodesInFile + 1; i++) {
		avgage += age(present_date, present_month, present_year, studic->birthday.day
			, studic->birthday.month, studic->birthday.year);
		studic = studic->mNext;
	}
	avgage = avgage / (nOfNodesInFile + 1);
	printf("Student avg age is : %lf\n", avgage);

	studic = start;
	student* studic2 = (student*)malloc(sizeof(student));

	studic2 = studic->mNext;

	for (; studic != NULL; studic = studic->mNext) {
		for (studic2 = studic; studic2 != NULL; studic2 = studic2->mNext) {
			if (strcmp(studic->person.surname, studic2->person.surname) > 0) {

				SwapElements(studic, studic2);
			}
		}
	}
	double ageOfCurrentStudent = 0;
	studic = start;
	while (studic->mNext != NULL)
	{
		ageOfCurrentStudent = age(present_date, present_month, present_year, studic->birthday.day
			, studic->birthday.month, studic->birthday.year);
		if (ageOfCurrentStudent < avgage) {
			printf("-------------------------------------------------------------------\n");
			printf("|%s    %s    %d    %d    %d ", studic->person.surname, studic->person.name, studic->birthday.day, studic->birthday.month, studic->birthday.year);
			for (int j = 0; j < 5; j++) {
				printf("%d ", studic->marks[j]);
			}
			printf("|\n");
		}
		else {

		}
		studic = studic->mNext;
	}
	studic = start;

	delete(studic);
	printf("\n-------------------------------------------------------------------\n");
	printf("List after delete.\n");
	studic = start;
	do
	{
		printf("-------------------------------------------------------------------\n");
		printf("|%s    %s    %d    %d    %d ", studic->person.surname, studic->person.name, studic->birthday.day, studic->birthday.month, studic->birthday.year);
		for (int j = 0; j < 5; j++) {
			printf("%d ", studic->marks[j]);

		}

		printf("|\n");
		studic = studic->mNext;
	} while (studic->mNext != NULL);
	printf("-------------------------------------------------------------------\n");


	return 0;
}

int testFileName(char* fname) {

	if (strstr(fname, ".txt")) {
		return 1;
	}
	else {
		return 0;
	}
}
int countLinesInFile(FILE* fp) {
	char sym;
	int numberOfAllNodes = 0;
	sym = getc(fp);
	while (sym != EOF) {
		if (sym == '\n') {
			numberOfAllNodes++;
		}
		sym = getc(fp);
	}
	fseek(fp, SEEK_SET, 0);
	return numberOfAllNodes;
}
double age(int present_date, int present_month, int present_year, int birth_date, int birth_month, int birth_year)
{
	int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (birth_date > present_date) {
		present_date = present_date + month[birth_month - 1];
		present_month = present_month - 1;
	}
	if (birth_month > present_month) {
		present_year = present_year - 1;
		present_month = present_month + 12;
	}
	int final_date = present_date - birth_date;
	int final_month = present_month - birth_month;
	int final_year = present_year - birth_year;

	double final_age = final_date + (final_month * 30) + (final_year * 365);
	return final_age;
}
void SwapElements(student* man1, student* man2) {
	student man;
	memcpy(man.person.name, man1->person.name, 50);
	memcpy(man.person.surname, man1->person.surname, 50);

	memcpy(man1->person.name, man2->person.name, 50);
	memcpy(man1->person.surname, man2->person.surname, 50);

	memcpy(man2->person.name, man.person.name, 50);
	memcpy(man2->person.surname, man.person.surname, 50);


	man.birthday.day = man1->birthday.day;
	man.birthday.month = man1->birthday.month;
	man.birthday.year = man1->birthday.year;

	man1->birthday.day = man2->birthday.day;
	man1->birthday.month = man2->birthday.month;
	man1->birthday.year = man2->birthday.year;

	man2->birthday.day = man.birthday.day;
	man2->birthday.month = man.birthday.month;
	man2->birthday.year = man.birthday.year;

	for (int i = 0; i < 5; i++)
	{
		man.marks[i] = man1->marks[i];
		man1->marks[i] = man2->marks[i];
		man2->marks[i] = man.marks[i];
	}
}
int check(int arr[])
{
	int c = 0;
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] == 4 || arr[i] == 5) { c++; return 1; }
	}

	return 0;
}
void delete(student* cur) {
	while (1) {
		student* prev = cur;
		cur = cur->mNext;
		if (!cur) break;
		int a = check(cur->marks);
		if (a == 0) {

			if (!cur->mNext) {
				prev->mNext = NULL;
				break;
			}
			prev->mNext = cur->mNext;

			free(cur);
			cur = prev;
			if (!cur->mNext) break;
		}
	}
};
