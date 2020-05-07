#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "student.h"
#include <QPropertyAnimation>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr, Student *student = nullptr);
    ~AddDialog();

private slots:
    void accept() override;

    void on_helpButton_clicked();

//    void on_buttonBox_accepted();

private:
    Ui::AddDialog *ui;
    int page;
    Student *student;

    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
};

#endif // ADDDIALOG_H
