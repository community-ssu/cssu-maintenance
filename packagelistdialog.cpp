#include "packagelistdialog.h"
#include "ui_packagelistdialog.h"

PackageListDialog::PackageListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageListDialog)
{
    ui->setupUi(this);
}

PackageListDialog::~PackageListDialog()
{
    delete ui;
}

void PackageListDialog::populateForString(QString string)
{
    QStringList itemsList = string.split(", ");

    foreach (QString packageString, itemsList) {
        QString packageStringTrimmed = packageString.remove("(").remove(")");
        QStringList itemDataList = packageStringTrimmed.split(" ");

        itemDataList.removeOne("");

        qDebug() << itemDataList;

        QTableWidgetItem *packageName = new QTableWidgetItem();
        packageName->setText(itemDataList.first());

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, packageName);

        if (itemDataList.count() > 1) {
            QTableWidgetItem *inequality = new QTableWidgetItem();
            inequality->setText(itemDataList.at(1));
            inequality->setTextAlignment(Qt::AlignCenter);

            ui->tableWidget->setItem(row, 1, inequality);

            QTableWidgetItem *version = new QTableWidgetItem();
            version->setText(itemDataList.last());

            ui->tableWidget->setItem(row, 2, version);
        }
    }

    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);
}
