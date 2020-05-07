#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "student.h"
#include "StudentsManager.h"
#include <QFileDialog>
#include <QPalette>
#include <QMessageBox>
#include <QScrollBar>

QString currentFilePath = "";
bool isChanged = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetWidget(this);


    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    AddRequest();
    Sort();
    UpdateTable();

}

void MainWindow::on_actionOpen_triggered()
{
    QString tmp = currentFilePath;
    currentFilePath = QFileDialog::getOpenFileName(this,
                                                       tr("Open student list"),
                                                       "",
                                                       tr("Data files (*.dat)"));
    if (!OpenFile(currentFilePath) || currentFilePath == "")
    {
        currentFilePath = tmp;
        return;
    }
    isChanged = false;
    ui->comboBox->setCurrentIndex(0);
    MainWindow::setWindowTitle(currentFilePath);
    UpdateTable();
}

void MainWindow::on_actionNew_triggered()
{
    ClearTable();
    Clear();
    ui->comboBox->setCurrentIndex(0);
    currentFilePath = "";
    MainWindow::setWindowTitle("Students Manager");
    isChanged = false;
}

void MainWindow::UpdateTable()
{
    ui->tableWidget->setEnabled(false);
    PrintTable(ui->tableWidget);
    ui->tableWidget->setEnabled(true);
    if (ui->tableWidget->rowCount() == 0){
        ui->tableWidget->setStyleSheet("QTableWidget"
                                       "{"
                                       "background-color: white;"

                                       "background-position: center;"
                                       "background-repeat: no-repeat;"
                                        "}");
    }
    else
    {
        ui->tableWidget->setStyleSheet("QTableWidget"
                                       "{"
                                       "alternate-background-color: #dbdbdb;"
                                       "background-color: white;"
                                        "}");
    }
}

void MainWindow::ClearTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::Sort()
{
    switch (ui->comboBox->currentIndex())
    {
    case 1: SortList(SortingMode::NORMAL);
        break;
    case 2: SortList(SortingMode::REVERSED);
        break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSave_triggered()
{
    if (currentFilePath == "") currentFilePath = QFileDialog::getSaveFileName(this,
                                                           tr("Save student list file"),
                                                           "New_StudentList.dat",
                                                           tr("Data files (*.dat)"));
    if (currentFilePath != "")
    {
        SynchWithFile(currentFilePath);
        MainWindow::setWindowTitle(currentFilePath);
        isChanged = false;
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    ui->removeButton->setEnabled(!ui->tableWidget->selectedItems().isEmpty());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 1: SortList(SortingMode::NORMAL);
        break;
    case 2: SortList(SortingMode::REVERSED);
        break;
    }
    UpdateTable();
    isChanged = true;
}

void MainWindow::on_removeButton_clicked()
{
    RemoveStudent(ui->tableWidget);
    UpdateTable();
    isChanged = true;
}


void MainWindow::on_removeAllButton_clicked()
{
    on_actionRemove_all_triggered();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QRegExp textValidator("[A-Za-z]{0," + QString::number(NAME_SIZE) + "}");
    if (ui->tableWidget->isEnabled())
    {
        switch (item->column())
        {
        case 0:
        {
            if (item->text() != "" && textValidator.exactMatch(item->text()))
            {
                SetSurname(item->text(), item->row());
                Sort();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Invalid surname");
            }
            UpdateTable();
            break;
        }
        case 1:
        {
            if (item->text() != "" && textValidator.exactMatch(item->text()))
            {
                SetName(item->text(), item->row());
                Sort();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Invalid name");
            }
            UpdateTable();
            break;
        }
        case 2:
        {
            Birthday b;
            b.day = 0;
            b.month = 0;
            b.year = 0;
            QStringList strList = item->text().split('.');
            if (strList.size() == 3)
            {
                b.day = strList[0].toUInt();
                b.month = strList[1].toUInt();
                b.year = strList[2].toUInt();
            }
            if (IsBirthdayCorrect(&b))
            {
                SetBirthday(item->text(), item->row());
            }
            else
            {
                QMessageBox::critical(this, "Error", "Invalid birthday date");
            }
            UpdateTable();
            break;
        }
        default:
        {
            int arr[COUNT_OF_MARKS];
            for (int i = 3; i < 3+COUNT_OF_MARKS; ++i)
            {
                QString str = ui->tableWidget->item(item->row(), i)->text();
                bool ok = false;
                arr[i-3] = ui->tableWidget->item(item->row(), i)->text().toInt(&ok);
                if (!ok || arr[i-3] < MIN_MARK || arr[i-3] > MAX_MARK)
                {
                    QMessageBox::critical(this, "Error", "Invalid mark. It must be from 0 to 5");
                    UpdateTable();
                    return;
                }
            }
            SetMarks(arr, item->row());
            break;
        }
        }
        isChanged = true;
    }
}

void MainWindow::on_actionRemove_all_triggered()
{
    QMessageBox msgBox(QMessageBox::Warning,
                       "Warning",
                       "Are you want to remove all students from the list?",
                       QMessageBox::Yes | QMessageBox::No,
                       this);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        Clear();
        ClearTable();
        UpdateTable();
        isChanged = true;
    }
}

void MainWindow::on_openButton_clicked()
{
    on_actionOpen_triggered();
}

void MainWindow::on_saveButton_clicked()
{
    on_actionSave_triggered();
}

void MainWindow::on_actionSave_as_triggered()
{
    currentFilePath = QFileDialog::getSaveFileName(this,
                                                               tr("Save student list file"),
                                                               "New_StudentList.dat",
                                                               tr("Data files (*.dat)"));
    if (currentFilePath != "")
    {
        MainWindow::setWindowTitle(currentFilePath);
        SynchWithFile(currentFilePath);
        isChanged = false;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "Students Manager v.2.0.\n"
                                            "Development environment: Qt Creator 4.11.1.");
}

void MainWindow::on_restoreButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning,
                       "Warning",
                       "Are you want to restore list from the last saved file? ",
                       QMessageBox::Yes | QMessageBox::No,
                       this);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        isChanged = false;
        if (!OpenFile(currentFilePath) || currentFilePath == "")
        {
            currentFilePath = "";
            Clear();
            UpdateTable();
        }
        else
        {
            ui->comboBox->setCurrentIndex(0);
            MainWindow::setWindowTitle(currentFilePath);
            UpdateTable();
        }
    }
}
