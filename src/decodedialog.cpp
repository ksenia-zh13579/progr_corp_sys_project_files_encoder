#include "decodedialog.h"
#include "ui_decodedialog.h"
#include <QMessageBox>
#include <QFileDialog>

DecodeDialog::DecodeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DecodeDialog)
{
    ui->setupUi(this);
    decoder = new Decoder();

    ui->decodeBtn->setEnabled(false);
    ui->indicatorLabel->hide();
    ui->keyInput->setEchoMode(QLineEdit::Password);

    connect(this, SIGNAL(allEntered()), SLOT(onAllEntered()));
    connect(decoder, SIGNAL(errorMessage(QString)), this, SLOT(onError(QString)));
    connect(decoder, SIGNAL(sendIndicator(QString)), this, SLOT(setIndicator(QString)));
}

DecodeDialog::~DecodeDialog()
{
    delete ui;
    delete decoder;
}

void DecodeDialog::onError(QString message)
{
    setIndicator("Ошибка!");
    QMessageBox::critical(this, "Результат дешифрования", "Ошибка: " + message);
}

void DecodeDialog::setIndicator(QString message)
{
    ui->indicatorLabel->setText(message);
}

void DecodeDialog::onAllEntered()
{
    ui->decodeBtn->setEnabled(true);
}

void DecodeDialog::on_downloadFileBtn_clicked()
{
    ui->decodeBtn->setEnabled(false);
    ui->indicatorLabel->hide();

    inPath = QFileDialog::getOpenFileName(this, "Выбрете файл...", "C:/");

    if (inPath != QString())
    {
        QFileInfo fileInfo(inPath);
        ui->fileName->setText(fileInfo.fileName());
    }

    if (inPath != QString() && outPath != QString() && !ui->keyInput->text().isEmpty())
        emit allEntered();
}


void DecodeDialog::on_chooseSaveBtn_clicked()
{
    outPath = QFileDialog::getSaveFileName(this, "Сохранить файл...", "C:/PCS_Project_decoded/decoded.txt", "Text files (*.txt)");

    if (outPath != QString())
    {
        QFileInfo fileInfo(outPath);
        ui->resultName->setText(fileInfo.fileName());
    }

    if (inPath != QString() && outPath != QString() && !ui->keyInput->text().isEmpty())
        emit allEntered();
}


void DecodeDialog::on_keyInput_editingFinished()
{
    if (!ui->keyInput->text().isEmpty())
    {
        QByteArray key = QByteArray::fromHex(ui->keyInput->text().toUtf8());
        decoder->setKey(key);

        if (inPath != QString() && outPath != QString())
            emit allEntered();
    }
}


void DecodeDialog::on_decodeBtn_clicked()
{
    ui->indicatorLabel->show();

    bool result = decoder->decryptFile(inPath, outPath);

    QString inputFileName = ui->fileName->text();
    QString outFileName = ui->resultName->text();

    if (result)
    {
        QMessageBox::information(this, "Результат дешифрования", "Файл " + inputFileName + " был успешно дешифрован.\nРезультат дешифрования был сохранен в файле " + outFileName + ".");
    }
    else
    {
        QMessageBox::critical(this, "Результат дешифрования", "Ошибка! Не удалось дешифровать файл " + inputFileName + ".");
    }
}


void DecodeDialog::on_keyInput_returnPressed()
{
    on_keyInput_editingFinished();
}

