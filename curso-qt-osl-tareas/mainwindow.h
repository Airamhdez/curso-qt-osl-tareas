#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "dbconnection.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlQueryModel>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
};

#endif // MAINWINDOW_H
