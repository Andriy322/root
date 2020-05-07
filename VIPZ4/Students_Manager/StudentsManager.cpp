#include "student.h"
#include "StudentsManager.h"
#include <string.h>
#include <QTableWidget>
#include <QWidget>
#include <qmessagebox.h>

QWidget *widget = nullptr;
char filePath[FILE_PATH_LEN+1] = "\0";
SList* list = NULL;
size_t countOfStudents = 0;

void SetWidget(QWidget *curWidget)
{
    widget = curWidget;
}

void SetSurname(QString surname, unsigned index)
{
    SetSurnameFromStr(list, index, surname);
}

void SetName(QString name, unsigned index)
{
    SetNameFromStr(list, index, name);
}

void SetBirthday(QString birthday, unsigned index)
{
    SetBirthdayFromStr(list, index, birthday);
}

void SetMarks(int marks[COUNT_OF_MARKS], unsigned index)
{
    SetMarksFromArray(list, index, marks);
}
void Clear()
{
	FreeList(&list);

}

int OpenFile(QString path)
{
    if (path == "") return 0;
    filePath[0] = '\0';
    if (path.size() > FILE_PATH_LEN)
    {
        QMessageBox::critical(widget, "Error", "Too long file path");
        return 0;
    }

    memcpy(filePath, path.toStdString().c_str(), path.size()+1);
    filePath[path.size()] = '\0';

    FILE* inputFile = fopen(filePath, "r");
	if (inputFile == NULL)
	{
		filePath[0] = '\0';
        QMessageBox::critical(widget, "Error", "Opening file error");
		return 0;
	}

    countOfStudents = ReadStudentData(inputFile, &list, MAX_STUDENTS_COUNT);
	fclose(inputFile);

    if (countOfStudents == 0)
    {
        QMessageBox::warning(widget, "Info", "File '" + path + "' does not contain any entries or is corrupted");
    }
    return 1;
}
void AddRequest()
{
    Student newStudent;
	if (countOfStudents >= MAX_STUDENTS_COUNT)
	{
        QMessageBox::warning(widget, "Warning", "Operation cannot be executed. "
            "You have reached the limit of students count: " + QString::number(MAX_STUDENTS_COUNT));
	}
	else
    if (ReadStudent(&newStudent))
	{
        if (AddToTail(&list, newStudent))
        {
            ++countOfStudents;
        }
        else
        {
            QMessageBox::critical(widget, "Error", "Operation failed");
        }
	}

}
void RemoveStudentByMark()
{
	unsigned mark = 0;
	printf("Enter mark: ");
	if (!scanf("%u", &mark) || mark < MIN_MARK || mark > MAX_MARK)
	{
		rewind(stdin);
		printf("Invalid value! Operation was canceled.\n");
		return;
	}
	unsigned countOfRemoved = RemoveByMark(&list, mark);
	countOfStudents -= countOfRemoved;
	printf("%u student(s) has(ve) been removed\n", countOfRemoved);
}

void SortList(SortingMode mode)
{
    SortByName(&list, mode);

}

void PrintTable(QTableWidget *table)
{
    PrintStudentTable(list, countOfStudents, table);
}
void SynchWithFile(QString path)
{
    if (path.size() > FILE_PATH_LEN)
    {
        QMessageBox::critical(widget, "Error", "Too long file path");
        return;
    }
    memcpy(filePath, path.toStdString().c_str(), path.size()+1);
    filePath[path.size()] = '\0';

	FILE* outputFile = fopen(filePath, "w");
	if (outputFile == NULL)
	{
        QMessageBox::critical(widget, "Error", "Opening file error");
		return;
	}
	WriteStudentData(outputFile, list);
	fclose(outputFile);

    QMessageBox::information(widget, "Info", "File has been successfully saved");
}
void RemoveStudent(QTableWidget *table)
{
    if (table->selectedItems().isEmpty())
    {
        QMessageBox::warning(widget, "Warning", "You didn't select any item");
        return;
    }

    while (!table->selectedItems().isEmpty())
    {
        unsigned index = table->selectedItems()[0]->row() + 1;
        table->removeRow(index-1);
        QString name = GetFullName(list, index);
        if (Remove(&list, index))
        {
            --countOfStudents;
        }
        else
        {
            QMessageBox::critical(widget, "Error", "This student doesn't exist in the list");
        }
    }
}
