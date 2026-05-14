#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "encodedialog.h"
#include "decodedialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_encodeBtn_clicked();

    void on_decodeBtn_clicked();

private:
    Ui::MainWindow *ui;

    EncodeDialog* encodew;
    DecodeDialog* decodew;
};
#endif // MAINWINDOW_H
