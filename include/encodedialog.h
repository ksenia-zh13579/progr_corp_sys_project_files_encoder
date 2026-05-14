#ifndef ENCODEDIALOG_H
#define ENCODEDIALOG_H

#include "encoder.h"
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

    QString inPath;
    QString outPath;
    QByteArray key;
    Encoder* encoder;

signals:
    void filesChosen();
private slots:
    void onFilesChosen();
    void onError(QString message);
    void setIndicator(QString message);

    void on_downloadFileBtn_clicked();
    void on_chooseSaveBtn_clicked();
    void on_encodeBtn_clicked();
};

#endif // ENCODEDIALOG_H
