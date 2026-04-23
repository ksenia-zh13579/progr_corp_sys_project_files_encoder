#include "encodedialog.h"
#include "ui_encodedialog.h"

EncodeDialog::EncodeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EncodeDialog)
{
    ui->setupUi(this);
}

EncodeDialog::~EncodeDialog()
{
    delete ui;
}
