#include "adddialog.h"
#include "ui_adddialog.h"
#include "student.h"
#include <qmessagebox.h>
#include <QCloseEvent>
#include <QString>

AddDialog::AddDialog(QWidget *parent, Student *student) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    this->setFixedSize(500, 500);
    ui->setupUi(this);

    this->page = 1;
    ui->groupBox2->hide();

    this->student = student;

    QRegExpValidator *validator =
            new QRegExpValidator(QRegExp("[A-Za-z]{0," + QString::number(NAME_SIZE) + "}"));
    ui->surnameLineEdit->setValidator(validator);
    ui->nameLineEdit->setValidator(validator);

    animation1 = new QPropertyAnimation(ui->groupBox1, "geometry");
    animation1->setDuration(300);
    animation1->setEasingCurve(QEasingCurve::InOutCubic);
    animation1->setStartValue(ui->groupBox1->geometry());
    animation1->setEndValue(QRect(ui->groupBox1->x() + 400,
                                 ui->groupBox1->y(),
                                 ui->groupBox1->width(),
                                 ui->groupBox1->height()));

    animation2 = new QPropertyAnimation(ui->groupBox2, "geometry");
    animation2->setDuration(300);
    animation2->setEasingCurve(QEasingCurve::InOutCubic);
    animation2->setStartValue(QRect(ui->groupBox2->x() - 400,
                                    ui->groupBox2->y(),
                                    ui->groupBox2->width(),
                                    ui->groupBox2->height()));
    animation2->setEndValue(QRect(ui->groupBox2->x(),
                                 ui->groupBox2->y(),
                                 ui->groupBox2->width(),
                                 ui->groupBox2->height()));
}

AddDialog::~AddDialog()
{
    delete animation1;
    delete animation2;
    delete ui;
}

void AddDialog::accept()
{
    switch (page)
    {
    case 1:
        {
            if (ui->surnameLineEdit->text() == "" || ui->nameLineEdit->text() == "")
            {
                QMessageBox::warning(this, "Warning", "Fields 'Surname' and 'Name' cannot be empty");
                return;
            }
            memcpy(this->student->surname,
                   ui->surnameLineEdit->text().toStdString().c_str(),
                   ui->surnameLineEdit->text().size()+1);
            memcpy(this->student->name,
                   ui->nameLineEdit->text().toStdString().c_str(),
                   ui->nameLineEdit->text().size()+1);
            QDate date = ui->calendar->selectedDate();
            Birthday b;
            b.day = date.day();
            b.month = date.month();
            b.year = date.year();
            if (!IsBirthdayCorrect(&b))
            {
                QMessageBox::critical(this, "Error", "Birthday date is invalid");
                return;
            }

            this->student->birthday.day = date.day();
            this->student->birthday.month = date.month();
            this->student->birthday.year = date.year();

            animation1->start();
            ui->groupBox2->show();
            animation2->start();
            page = 2;
            break;
        }
    case 2:
        {
            this->student->marks[0] = ui->spinBox_1->value();
            this->student->marks[1] = ui->spinBox_2->value();
            this->student->marks[2] = ui->spinBox_3->value();
            this->student->marks[3] = ui->spinBox_4->value();
            this->student->marks[4] = ui->spinBox_5->value();
            done(QDialog::Accepted);
            break;
        }
    default: close();
    }

}

void AddDialog::on_helpButton_clicked()
{
    QMessageBox::information(this, "Help", "Surname and name of the student can contain "
                             "only letters of the Latin alphabet."
                             "All marks must be from 0 to 5.");
}
