#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_2_clicked(const QDate &date2);

    void on_pushButton_clicked();


    void on_pushButton_Find_Customer_clicked();

    void on_pushButton_Book_clicked();


    void on_pushButton_LiveLongest_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
