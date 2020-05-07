#include "student.h"
#include "adddialog.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <QString>
#include <QTableWidget>
#define TABLE_TOP_LEFT 218
#define TABLE_TOP_RIGHT 191
#define TABLE_BOTTOM_LEFT 192
#define TABLE_BOTTOM_RIGHT 217
#define TABLE_VERTICAL 179

#define MIN(n1, n2) (((n1) < (n2)) ? (n1) : (n2))


SList *GetStudent(SList *head, size_t index)
{
    for (size_t i = 0; i < index && head != NULL; ++i)
    {
        head = head->next;
    }
    return head;
}

void SetSurnameFromStr(SList *head, size_t index, QString str)
{
    SList *student = GetStudent(head, index);
    memcpy(student->student.surname, str.toStdString().c_str(), str.size()+1);
}

void SetNameFromStr(SList *head, size_t index, QString str)
{
    SList *student = GetStudent(head, index);
    memcpy(student->student.name, str.toStdString().c_str(), str.size()+1);
}

void SetBirthdayFromStr(SList *head, size_t index, QString str)
{
    SList *student = GetStudent(head, index);
    QStringList strList = str.split('.');
    student->student.birthday.day = strList[0].toUInt();
    student->student.birthday.month = strList[1].toUInt();
    student->student.birthday.year = strList[2].toUInt();
}

void SetMarksFromArray(SList *head, size_t index, int marks[COUNT_OF_MARKS])
{
    SList *student = GetStudent(head, index);
    for (size_t i = 0; i < COUNT_OF_MARKS; ++i)
    {
        student->student.marks[i] = marks[i];
    }
}

QString GetFullName(SList *head, size_t index)
{
    for(size_t i = 1; i < index && head != NULL; ++i)
    {
        head = head->next;
    }
    if (head == NULL) return "";
    return QString::fromLocal8Bit(head->student.surname)
            + " "
            + QString::fromLocal8Bit(head->student.name);
}

int IsStrAlpha(unsigned char str[])
{
	if (str[0] == '-' || str[0] == '\0' || !isalpha(str[0]))
	{
		return 0;
	}
	for (size_t i = 1; str[i] != '\0'; ++i)
	{
		if (!isalpha((unsigned char)str[i]))
		{
			if (!(str[i] == '-' && isalpha(str[i - 1]) && isalpha(str[i + 1])))
			{
				return 0;
			}
		}
	}
	return 1;
}
int AddToHead(SList **head, Student student)
{
	if (head == NULL)
	{
		return 0;
	}

	SList *element = (SList*)malloc(sizeof(SList));
	if (element == NULL)
	{
		return 0;
	}
	
	element->student = student;
	element->next = (*head == NULL ? NULL : *head);
	*head = element;
	
	return 1;
}
int AddToTail(SList** head, Student student)
{
	if (head == NULL)
	{
		return 0;
	}

	SList* element = (SList*)malloc(sizeof(SList));
	if (element == NULL)
	{
		return 0;
	}

	element->student = student;
	element->next = NULL;
	
	if (*head == NULL)
	{
		*head = element;
	}
	else
	{
		SList* tmp = *head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = element;
	}

	return 1;
}
//----------------------------------------------------------------
// Remove student by index in list (index begins from 1)
int Remove(SList **head, size_t index)
{
    if (head == NULL || *head == NULL || index == 0)
    {
        return 0;
    }
    SList *tmp;
    if (index == 1)
    {
        tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
    else
    {
        SList *cur = *head;
        for (size_t i = 2; i < index && cur != NULL; ++i)
        {
            cur = cur->next;
        }
        if (cur == NULL || cur->next == NULL) return 0;

        tmp = cur->next->next;
        free(cur->next);
        cur->next = tmp;
    }
    return 1;
}
//----------------------------------------------------------------
// Returns count of removed students
unsigned RemoveByMark(SList **head, unsigned mark)
{
	if (head == NULL || *head == NULL)
	{
		return 0;
	}
	
	size_t countOfRemoved = 0;
	SList *tmp = *head;
	Bool isRemoved;

	while (tmp->next != NULL)
	{
		isRemoved = FALSE;
		for (size_t i = 0; i < COUNT_OF_MARKS; ++i)
		{
			if (tmp->next->student.marks[i] == mark)
			{
				isRemoved = TRUE;
				++countOfRemoved;
				SList *tmp2 = tmp->next;
				tmp->next = tmp2->next;
				free(tmp2);

				break;
			}
		}
		if (!isRemoved)
		{
			tmp = tmp->next;
		}
	}

	for (size_t i = 0; i < COUNT_OF_MARKS; ++i)
	{
		if ((*head)->student.marks[i] == mark)
		{
			++countOfRemoved;
			tmp = *head;
			*head = (*head)->next;
			free(tmp);

			break;
		}
	}

	return countOfRemoved;
}
//----------------------------------------------------------------
// Free SList
void FreeList(SList **head)
{
	if (head == NULL)
	{
		return;
	}

	SList *tmp = *head;
	while (tmp != NULL)
	{
		*head = tmp->next;
		free(tmp);
		tmp = *head;
	}
}
//----------------------------------------------------------------
// Returns count of students if file was read successfully, else 0 if error
size_t ReadStudentData(FILE* file, SList **head, unsigned maxCount)
{
    if (head == NULL)
	{
		return 0;
	}

	FreeList(head);

	Student student;
	size_t i = 0;

	for (; !feof(file) && i < maxCount; ++i)
	{
		fgetc(file);
		fgetc(file);
		if (feof(file)) break;
		fseek(file, -2, SEEK_CUR);
		
		if (fscanf(file, "%" STR_NAME_SIZE "s\t%" STR_NAME_SIZE "s\t%u.%u.%u\t",
            student.surname,
            student.name,
			&student.birthday.day,
			&student.birthday.month,
			&student.birthday.year) != 5
            || !IsStrAlpha((unsigned char*)student.surname)
            || !IsStrAlpha((unsigned char*)student.name)
			|| !IsBirthdayCorrect(&student.birthday))
		{
			FreeList(head);
			return 0;
		}

		for (size_t j = 0; j < COUNT_OF_MARKS; ++j)
		{
			if (fscanf(file, "%u,", &student.marks[j]) != 1
				|| !IsMarkCorrect(student.marks[j]))
			{
				FreeList(head);
				return 0;
			}
		}

		if (!AddToTail(head, student))
		{
			FreeList(head);
			return 0;
		}
	}

	return i;
}
//----------------------------------------------------------------
// Write student list to file (rewrites file)
void WriteStudentData(FILE* file, const SList* head)
{
	if (file == NULL || head == NULL)
	{
		return;
	}

	do
	{
		fprintf(file, "%s\t%s\t", head->student.surname, head->student.name);
		PrintBirthday(file, &(head->student.birthday));
		fprintf(file, "\t");
		PrintMarks(file, &(head->student));
		fprintf(file, "\n");
	} while ((head = head->next) != NULL);
}

int IsBirthdayCorrect(const Birthday *birthday)
{
	time_t t;
	time(&t);
	int curYear = localtime(&t)->tm_year + 1900;
#ifdef MAX_AGE
	int lowYearLimit = curYear - MAX_AGE;
#else
	int lowYearLimit = 0;
#endif
	if (birthday->day >= 1
		&& birthday->month >= 1 && birthday->month <= 12
		&& birthday->year > lowYearLimit && birthday->year < curYear)
	{
		if (birthday->month == 2)
		{
			if (((birthday->year % 4 && birthday->day <= 28)
				|| (!(birthday->year % 4) && birthday->day <= 29)))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		if (birthday->month == 1
			|| birthday->month == 3
			|| birthday->month == 5
			|| birthday->month == 7
			|| birthday->month == 8
			|| birthday->month == 10
			|| birthday->month == 12)
		{
			if (birthday->day <= 31) return 1;
			else return 0;
		}
		else
		{
			if (birthday->day <= 30) return 1;
		}
	}

	return 0;
}

int IsMarkCorrect(unsigned mark)
{
	if (mark >= MIN_MARK && mark <= MAX_MARK)
	{
		return 1;
	}

	return 0;
}

bool ReadStudent(Student *student)
{
    AddDialog dialog(nullptr, student);
    dialog.setModal(true);
    return dialog.exec() == QDialog::Accepted;
}
QString GetBirthday(const Birthday *date)
{
	if (date == NULL)
	{
        return "";
    }
    QString str = "";
    if (date->day < 10) str += "0";
    str += QString::number(date->day) + ".";
    if (date->month < 10) str += "0";
    str += QString::number(date->month) + "." + QString::number(date->year);
	return str;
}
void PrintBirthday(FILE *file, const Birthday *date)
{
	if (date == NULL || file == NULL)
	{
		return;
	}
    fprintf(file, "%02u.%02u.%-5u", date->day, date->month, date->year);
}
char* MarksToString(const Student *student, char str[], size_t size)
{
	if (student == NULL)
	{
		return str;
	}
	size_t offset = 0;
	for (size_t i = 0; i < COUNT_OF_MARKS; ++i)
	{
		offset += snprintf(str + offset, size - offset, "%u, ", student->marks[i]);
	}
	*(str + offset - 2) = '\0';
	return str;
}
void PrintMarks(FILE *file, const Student *student)
{
	if (student == NULL || file == NULL)
	{
		return;
	}
	for (size_t i = 0; i < COUNT_OF_MARKS-1; ++i)
	{
		fprintf(file, "%u, ", student->marks[i]);
	}
	fprintf(file, "%u", student->marks[COUNT_OF_MARKS - 1]);
}
double GetAverageMark(const Student *student)
{
	if (student == NULL)
	{
		return 0;
	}
	long sum = 0;
	for (size_t i = 0; i < COUNT_OF_MARKS; ++i)
	{
		sum += student->marks[i];
	}
	return 1.0 * sum / COUNT_OF_MARKS;
}

void PrintStudentTable(const SList *students, size_t size, QTableWidget *table)
{
	if (students == NULL)
    {
		return;
	}
    table->clearContents();
    table->setRowCount(size);
    for (size_t i = 0; i < size && students != NULL; ++i)
    {
        table->setItem(i, 0, new QTableWidgetItem(students->student.surname));
        table->setItem(i, 1, new QTableWidgetItem(students->student.name));
        table->setItem(i, 2, new QTableWidgetItem(GetBirthday(&(students->student.birthday))));
        for (size_t j = 0; j < COUNT_OF_MARKS; ++j)
        {
            table->setItem(i, 3+j, new QTableWidgetItem(QString::number(students->student.marks[j])));
        }
        students = students->next;
    }
}
void SwapSize_t(size_t *array, size_t ind1, size_t ind2)
{
	size_t tmp = array[ind1];
	array[ind1] = array[ind2];
	array[ind2] = tmp;
}
void SwapDouble(double *array, size_t ind1, size_t ind2)
{
	double tmp = array[ind1];
	array[ind1] = array[ind2];
	array[ind2] = tmp;
}

int Compare(const Student *student1, const Student *student2)
{
	if (strcmp(student1->surname, student2->surname) < 0
		|| (strcmp(student1->surname, student2->surname) == 0
			&& strcmp(student1->name, student2->name) < 0))
	{
		return -1;
	}
	else if (strcmp(student1->surname, student2->surname) == 0
		&& strcmp(student1->name, student2->name) == 0)
	{
		return 0;
	}
	return 1;
}
SList* Swap(SList* head, SList* student1, SList* student2)
{
	SList* prev1, *prev2, *next1, *next2;
	prev1 = head;
	prev2 = head;
	if (prev1 == student1)
	{
		prev1 = NULL;
	}
	else
	{
		while (prev1->next != student1)
		{
			prev1 = prev1->next;
		}
	}
	if (prev2 == student2)
	{
		prev2 = NULL;
	}
	else
	{
		while (prev2->next != student2)
		{
			prev2 = prev2->next;
		}
	}
	next1 = student1->next;
	next2 = student2->next;
	if (student2 == next1)
	{
		student2->next = student1;
		student1->next = next2;
		if (student1 != head)
		{
			prev1->next = student2;
		}
	}
	else
		if (student1 == next2)
		{
			student1->next = student2;
			student2->next = next1;
			if (student2 != head)
			{
				prev2->next = student2;
			}
		}
		else
		{
			if (student1 != head)
			{
				prev1->next = student2;
			}
			student2->next = next1;
			if (student2 != head)
			{
				prev2->next = student1;
			}
			student1->next = next2;
		}
	if (student1 == head)
	{
		return(student2);
	}
	if (student2 == head)
	{
		return(student1);
	}
	return(head);
}
void SortByName(SList **head, SortingMode mode)
{
    bool isTrue = (mode == SortingMode::NORMAL);
	if (head == NULL) return;

	SList* min;
	SList* tmp;
	SList* selected = *head;
	while (selected != NULL)
	{
		min = selected;
		tmp = selected->next;
		while (tmp != NULL)
		{
            if ((Compare(&(min->student), &(tmp->student)) > 0) == isTrue)
            {
                min = tmp;
            }
			tmp = tmp->next;
		}
		if (min != selected)
		{
			*head = Swap(*head, selected, min);
			selected = min->next;
		}
		else selected = selected->next;
	}
}
