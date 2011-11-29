#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}

void PreviewDialog::setText(QString text)
{
    ui->textBrowser->setText(text);
}
