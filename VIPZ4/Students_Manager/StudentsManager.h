#ifndef STUDENTS_MANAGER_H
#define STUDENTS_MANAGER_H
#include <QWidget>
#include <QTableWidget>
#include "student.h"

#define MAX_STUDENTS_COUNT 30
#define FILE_PATH_LEN 255
#define COUNT_OF_THE_LAST 5

void SetWidget(QWidget *curWidget);

void SetSurname(QString surname, unsigned index);
void SetName(QString name, unsigned index);
void SetBirthday(QString birthday, unsigned index);
void SetMarks(int marks[COUNT_OF_MARKS], unsigned index);


void ShowHelp();


void Clear();


int OpenFile(QString path);


void AddRequest();


void ShowBadList();

void RemoveStudent(QTableWidget *table);


void RemoveStudentByMark();


void SortList(SortingMode mode);


void PrintTable(QTableWidget *table);


void SynchWithFile(QString path);

#endif
