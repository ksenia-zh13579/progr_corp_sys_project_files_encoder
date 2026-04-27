#include "decodedialog.h"
#include "ui_decodedialog.h"

DecodeDialog::DecodeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DecodeDialog)
{
    ui->setupUi(this);
}

DecodeDialog::~DecodeDialog()
{
    delete ui;
}
