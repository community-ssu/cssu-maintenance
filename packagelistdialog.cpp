#include "packagelistdialog.h"
#include "ui_packagelistdialog.h"

PackageListDialog::PackageListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageListDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(accept()));
}

PackageListDialog::~PackageListDialog()
{
    delete ui;
}

void PackageListDialog::populateForString(QString string)
{
    m_originalDependsLine = string;

    QStringList itemsList = string.split(", ");

    foreach (QString packageString, itemsList) {
        QString packageStringTrimmed = packageString.remove("(").remove(")");
        QStringList itemDataList = packageStringTrimmed.split(" ");

        itemDataList.removeOne("");

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

QString PackageListDialog::dependsLine()
{
    QStringList packagesList;
    for (int i; i < ui->tableWidget->rowCount(); i++) {
        QString packageName;
        QString inequalityString;
        QString versionString;

        QTableWidgetItem *packageItem = ui->tableWidget->item(i, 0);
        if (packageItem)
            packageName = packageItem->text();

        QTableWidgetItem *inequality = ui->tableWidget->item(i, 1);
        if (inequality)
            inequalityString = inequality->text();

        if (!inequalityString.isEmpty()) {
            QTableWidgetItem *version = ui->tableWidget->item(i, 2);
            if (version)
                versionString = version->text();
        }

        QString finalLine;
        if (!inequalityString.isEmpty() && !versionString.isEmpty())
            finalLine = packageName + " (" + inequalityString + " " + versionString + ")";
        else
            finalLine = packageName;

        if (!finalLine.isEmpty())
            packagesList.append(finalLine);
    }

    QString dependsLine = packagesList.join(", ");
    qDebug() << dependsLine;
    return dependsLine;
}

void PackageListDialog::accept()
{
    QString line = dependsLine();
    if (line != m_originalDependsLine)
        emit dependsLineChanged(line);

    close();
}
