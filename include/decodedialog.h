#ifndef DECODEDIALOG_H
#define DECODEDIALOG_H

#include <QDialog>
#include "decoder.h"

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

    QString inPath;
    QString outPath;
    QByteArray key;
    Decoder* decoder;

signals:
    void allEntered();

private slots:
    void onAllEntered();
    void onError(QString message);
    void setIndicator(QString message);
    void on_downloadFileBtn_clicked();
    void on_chooseSaveBtn_clicked();
    void on_keyInput_editingFinished();
    void on_decodeBtn_clicked();
    void on_keyInput_returnPressed();
};

#endif // DECODEDIALOG_H
