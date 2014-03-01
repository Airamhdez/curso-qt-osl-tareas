#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup database
        ConecToDb(db_, "tareas");

        db_.exec("CREATE TABLE IF NOT EXISTS categorias ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "name TEXT,"
                  "descripcion TEXT"
                  ");");
        db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "name TEXT,"
                  "date TEXT,"
                  "descripcion TEXT,"
                  "realizada NUMERIC,"
                  "id_categ INTEGER,"
                  "FOREIGN KEY(id_categ) REFERENCES categorias(id)"
                  ");");
        db_.exec("CREATE TABLE IF NOT EXISTS etiquetas ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "name TEXT"
                  ");");
        db_.exec("CREATE TABLE IF NOT EXISTS tar_etiq ("
                  "id_tar INTEGER,"
                  "id_etiq INTEGER,"
                  "PRIMARY KEY (id_tar, id_etiq),"
                  "FOREIGN KEY(id_tar) REFERENCES tareas(id)"
                  "FOREIGN KEY(id_etiq) REFERENCES etiquetas(id)"
                  ");");

        /*QSqlQuery q(db_);
        q.exec("Select id, name, date, descripcion, (case realizada when '0' then 'No' else 'Si' END), (case when id_categ IS NULL then ('Sin categoría') else (select name from categorias where id = id_categ) END) from tareas;");
        QSqlQueryModel *modelo = new QSqlQueryModel(this);
        modelo->setQuery(q);
        modelo->setHeaderData(0, Qt::Horizontal, tr("Id"));
        modelo->setHeaderData(1, Qt::Horizontal, tr("Nombre"));
        modelo->setHeaderData(2, Qt::Horizontal, tr("Fecha límite"));
        modelo->setHeaderData(3, Qt::Horizontal, tr("Descripción"));
        modelo->setHeaderData(4, Qt::Horizontal, tr("Realizada"));
        modelo->setHeaderData(5, Qt::Horizontal, tr("Categoría"));
        ui->tlbView->setModel(modelo);*/
        QSqlRelationalTableModel *modelo = new QSqlRelationalTableModel(this, db_);
        modelo->setTable("tareas");
        modelo->setRelation(5, QSqlRelation("categorias", "id", "name"));
        modelo->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        modelo->setHeaderData(0, Qt::Horizontal, tr("Id"));
        modelo->setHeaderData(1, Qt::Horizontal, tr("Nombre"));
        modelo->setHeaderData(2, Qt::Horizontal, tr("Fecha límite"));
        modelo->setHeaderData(3, Qt::Horizontal, tr("Descripción"));
        modelo->setHeaderData(4, Qt::Horizontal, tr("Realizada"));
        modelo->setHeaderData(5, Qt::Horizontal, tr("Categoría"));
        modelo->select();
        ui->tlbView->setModel(modelo);
}

MainWindow::~MainWindow()
{
    delete ui;
}
