#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>

namespace Ui {
    class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QWidget *parent = 0);
    ~PreviewDialog();

public slots:
    void setText(QString text);

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H
