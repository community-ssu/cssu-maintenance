#ifndef PACKAGELISTDIALOG_H
#define PACKAGELISTDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QDebug>

namespace Ui {
    class PackageListDialog;
}

class PackageListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageListDialog(QWidget *parent = 0);
    ~PackageListDialog();
    void populateForString(QString string);

private:
    Ui::PackageListDialog *ui;

};

#endif // PACKAGELISTDIALOG_H
