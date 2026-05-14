#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    encodew = new EncodeDialog(this);
    decodew = new DecodeDialog(this);

    encodew->hide();
    decodew->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete encodew;
    delete decodew;
}

void MainWindow::on_encodeBtn_clicked()
{
    encodew->show();
}


void MainWindow::on_decodeBtn_clicked()
{
    decodew->show();
}

