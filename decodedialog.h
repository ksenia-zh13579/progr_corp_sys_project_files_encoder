#ifndef DECODEDIALOG_H
#define DECODEDIALOG_H

#include <QDialog>

namespace Ui {
class DecodeDialog;
}

class DecodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecodeDialog(QWidget *parent = nullptr);
    ~DecodeDialog();

private:
    Ui::DecodeDialog *ui;
};

#endif // DECODEDIALOG_H
