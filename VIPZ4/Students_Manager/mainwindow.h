#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QTableWidgetItem>

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
    void on_addButton_clicked();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_tableWidget_itemSelectionChanged();

    void on_comboBox_currentIndexChanged(int index);

    void on_removeButton_clicked();

    void on_removeAllButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_actionRemove_all_triggered();

    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_actionSave_as_triggered();

    void on_actionAbout_triggered();

    void on_restoreButton_clicked();

private:
    Ui::MainWindow *ui;

    void UpdateTable();

    void ClearTable();

    void Sort();
};
#endif // MAINWINDOW_H
