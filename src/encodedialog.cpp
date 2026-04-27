#include "encodedialog.h"
#include "ui_encodedialog.h"
#include <QFileDialog>
#include <QMessageBox>

EncodeDialog::EncodeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EncodeDialog)
{
    ui->setupUi(this);

    ui->encodeBtn->setEnabled(false);
    ui->IndicatorLabel->hide();
    ui->keyLabel->hide();
    ui->keyInput->hide();

    connect(this, SIGNAL(filesChosen()), SLOT(onFilesChosen()));
}

EncodeDialog::~EncodeDialog()
{
    delete ui;
    delete encoder;
}

void EncodeDialog::on_downloadFileBtn_clicked()
{
    ui->encodeBtn->setEnabled(false);
    ui->IndicatorLabel->hide();
    ui->keyLabel->hide();
    ui->keyInput->hide();
    outPath = QString();

    inPath = QFileDialog::getOpenFileName(this, "Выбрете файл...", "C:/");
    if (inPath != QString())
    {
        ui->fileName->setText(inPath);
    }

    if (inPath != QString() && outPath != QString())
        emit filesChosen();
}


void EncodeDialog::on_chooseSaveBtn_clicked()
{
    outPath = QFileDialog::getSaveFileName(this, "Сохранить файл...", "C:/PCS_Project_encoded/encoded.txt", "Text files (*.txt)");
    if (outPath != QString())
    {
        ui->resultName->setText(outPath);
    }

    if (inPath != QString() && outPath != QString())
        emit filesChosen();
}

void EncodeDialog::onFilesChosen()
{
    ui->encodeBtn->setEnabled(true);
}


void EncodeDialog::on_encodeBtn_clicked()
{
    ui->IndicatorLabel->show();

    encoder = new Encoder();
    bool result = encoder->encryptFile(inPath, outPath);

    if (result)
    {
        ui->keyLabel->show();
        ui->keyInput->show();
        ui->keyInput->setText(encoder->getKey());

        QMessageBox::information(this, "Результат шифрования", "Файл был успешно зашифрован.\nРезультат шифрования был сохранен в выбранном для него файле.");
    }
    else
    {
        QMessageBox::critical(this, "Результат шифрования", "Ошибка! Не удалось зашифровать файл.");
    }
}

