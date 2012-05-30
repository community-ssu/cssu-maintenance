#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "packagelistdialog.h"
#include "previewdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void connectSignals();
    void processControlFileContents(QString contents);

    QString m_currentFilePath;

    QString prepareControlFileAsString();

private slots:
    void openFile();
    void onDependsLineEditClicked();
    void preview();
    void onDependsLineChanged(QString);
};

#endif // MAINWINDOW_H
