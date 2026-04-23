#ifndef ENCODEDIALOG_H
#define ENCODEDIALOG_H

#include <QDialog>

namespace Ui {
class EncodeDialog;
}

class EncodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EncodeDialog(QWidget *parent = nullptr);
    ~EncodeDialog();

private:
    Ui::EncodeDialog *ui;
};

#endif // ENCODEDIALOG_H
