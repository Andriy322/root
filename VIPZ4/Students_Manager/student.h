#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QTableWidget>

#define NAME_SIZE 20
#define MIN_MARK 0
#define MAX_MARK 5
#define MAX_COUNT_OF_MARKS 7
#define COUNT_OF_MARKS 5
#define MAX_AGE 200

#define NUM_TO_STR_(num) #num
#define NUM_TO_STR(num) NUM_TO_STR_(num)

#define STR_NAME_SIZE NUM_TO_STR(NAME_SIZE)

typedef unsigned long long  size_t;

#if COUNT_OF_MARKS > MAX_COUNT_OF_MARKS
#error Fatal error! COUNT_OF_MARKS must be lower than MAX_COUNT_OF_MARKS
#endif

typedef struct
{
	unsigned char day;
	unsigned char month;
	unsigned short year;
} Birthday;

typedef struct
{
	char surname[NAME_SIZE+1];
	char name[NAME_SIZE+1];
	Birthday birthday;
	unsigned marks[COUNT_OF_MARKS];
} Student;

typedef struct StudentsList
{
	Student student;
	struct StudentsList *next;
} SList;

typedef enum
{
	FALSE,
	TRUE
} Bool;

typedef enum
{
    NORMAL,
    REVERSED
} SortingMode;

SList *GetStudent(SList *head, size_t index);

void SetSurnameFromStr(SList *head, size_t index, QString str);
void SetNameFromStr(SList *head, size_t index, QString str);
void SetBirthdayFromStr(SList *head, size_t index, QString str);
void SetMarksFromArray(SList *head, size_t index, int marks[COUNT_OF_MARKS]);

// Returns full name of student by index
QString GetFullName(SList *head, size_t index);

// Returns 1 if string contains only alphabetical characters, else 0
int IsStrAlpha(unsigned char str[]);

// Returns 1 if element was inserted at the head successfully, else 0
int AddToHead(SList** head, Student student);

// Returns 1 if element was inserted at the tail successfully, else 0
int AddToTail(SList** head, Student student);

// Remove student by index in list (index begins from 1)
int Remove(SList **head, size_t index);

// Returns count of removed students
unsigned RemoveByMark(SList** head, unsigned mark);

// Free SList
void FreeList(SList** head);

// Returns count of students if file was read successfully, else 0 if error
size_t ReadStudentData(FILE* file, SList** head, unsigned maxCount);

// Write student list to file (rewrites file)
void WriteStudentData(FILE* file, const SList* head);

// Returns 1 if birthday is correct, else 0
int IsBirthdayCorrect(const Birthday* birthday);

// Returns 1 if mark is correct, else 0
int IsMarkCorrect(unsigned mark);

// Read from console surname, name, birthday date and marks. Returns generated struct Student.
// Example of input data:
//	Enter surname: Swift
//	Enter name: John
//	Enter birthday: 16.03.1998
//	Enter 5 marks: 5 5 3 4 3
bool ReadStudent(Student *student);

// Returns string with birthday date
QString GetBirthday(const Birthday* date);

// Print birthday in format dd.mm.yyyy to stream 'file'
void PrintBirthday(FILE* file, const Birthday* date);

// Returns string with marks of student
char* MarksToString(const Student* student, char str[], size_t size);

// Print list of marks (3, 5, ...) to stream 'file'
void PrintMarks(FILE* file, const Student* student);

// Returns averege mark of student
double GetAverageMark(const Student* student);

// Print student table with columns <Surname>, <Name>, <Birthday>, <Exam marks>
void PrintStudentTable(const SList *students, size_t size, QTableWidget *table);

// Swap size_t elements of array (array[ind1] with array[ind2])
void SwapSize_t(size_t* array, size_t ind1, size_t ind2);

// Swap double elements of array (array[ind1] with array[ind2])
void SwapDouble(double* array, size_t ind1, size_t ind2);

// Returns 1 if names of the worst students was printed successfully, else 0
//int PrintLowMarkStudents(const SList* head, size_t size, size_t countToPrint);

// Swap student1 and student2
SList* Swap(SList* student1, SList* student2, SList* root);

// Sort list in reversed alphabetical order
void SortByName(SList** head, SortingMode mode);

#endif // !STUDENT_H
