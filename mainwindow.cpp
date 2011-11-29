#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSignals();

    QStringList list;
    list << "user/desktop" << "user/development" << "user/education" << "user/games"
         << "user/graphics" << "user/multimedia" << "user/navigation" << "user/network"
         << "user/office" << "user/science" << "user/system" << "user/utilities";
    ui->sectionsBox->addItems(list);

    openFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->dependsLineEdit, SIGNAL(clicked()), this, SLOT(onDependsLineEditClicked()));
    connect(ui->actionPreview, SIGNAL(triggered()), this, SLOT(preview()));
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open control file"),
                                                    QString(),
                                                    "Debian control files (control)");

    qDebug() << QString("Opening control file: %1").arg(fileName);

    QFile controlFile(fileName);
    if (!controlFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open control file"));
        return;
    }

    m_currentFilePath = fileName;

    QString controlFileContents = controlFile.readAll();
    controlFile.close();

    processControlFileContents(controlFileContents);
}

void MainWindow::processControlFileContents(QString fileContents)
{
    QStringList controlLines = fileContents.split("\n");
    QString sourceName;
    QString sourceSection;
    QString maintainerName;
    QString buildDeps;
    QString packageName;
    QString arch;
    QString replaces;
    QString conflicts;
    QString depends;
    QString maemoDisplayName;
    QString maemoFlags;
    QString description;

    foreach (QString line, controlLines) {
        if (line.startsWith("Depends")) {
            depends = line.remove("Depends: ");
        }

        if (line.startsWith("Source")) {
            sourceName = line.remove("Source: ");
        }

        if (line.startsWith("Section")) {
            sourceSection = line.remove("Section: ");
        }

        if (line.startsWith("Maintainer")) {
            maintainerName = line.remove("Maintainer: ");
        }

        if (line.startsWith("Conflicts")) {
            conflicts = line.remove("Conflicts: ");
        }

        if (line.startsWith("XB-Maemo-Display-Name", Qt::CaseInsensitive)) {
            maemoDisplayName = line.remove("XB-Maemo-Display-Name: ", Qt::CaseInsensitive);
        }

        if (line.startsWith("Description")) {
            description = line.remove("Description: ");
        }

        if (line.startsWith("Architecture")) {
            arch = line.remove("Architecture: ");
        }

        if (line.startsWith("Build-Depends")) {
            buildDeps = line.remove("Build-Depends: ");
        }

        if (line.startsWith("Package")) {
            packageName = line.remove("Package: ");
        }

        if (line.startsWith("Replaces")) {
            replaces = line.remove("Replaces: ");
        }

        if (line.contains("XB-Maemo-Flags")) {
            maemoFlags = line.remove("XB-Maemo-Flags:  ", Qt::CaseInsensitive);
            qDebug() << maemoFlags;
        }
    }

    ui->sourceLineEdit->setText(sourceName);
    ui->maintainerEdit->setText(maintainerName);
    ui->buildDepsEdit->setText(buildDeps);
    ui->packageLineEdit->setText(packageName);
    ui->archLineEdit->setText(arch);
    ui->replacesLineEdit->setText(replaces);
    ui->conflictsLineEdit->setText(conflicts);
    ui->dependsLineEdit->setText(depends);
    ui->maemoDisplayNameEdit->setText(maemoDisplayName);
    ui->maemoFlagsEdit->setText(maemoFlags);
    ui->descriptionEdit->setText(description);
    ui->sectionsBox->setCurrentIndex(ui->sectionsBox->findText(sourceSection));
}

void MainWindow::onDependsLineEditClicked()
{
    PackageListDialog *dependsDialog = new PackageListDialog(this);
    dependsDialog->setAttribute(Qt::WA_DeleteOnClose);
    dependsDialog->populateForString(ui->dependsLineEdit->text());
    dependsDialog->show();
}

QString MainWindow::prepareControlFileAsString()
{
    QString control;
    control.append(QString("Source: %1").arg(ui->sourceLineEdit->text()) + "\n");
    control.append(QString("Section: %1").arg(ui->sectionsBox->currentText()) + "\n");
    control.append(QString("Priority: required") + "\n");
    control.append(QString("Maintainer: %1").arg(ui->maintainerEdit->text()) + "\n");
    control.append(QString("Build-Depends: %1").arg(ui->buildDepsEdit->text() + "\n"));
    control.append(QString("Standards-Version: 3.7.2") + "\n");
    control.append("\n");
    control.append(QString("Package: %1").arg(ui->packageLineEdit->text()) + "\n");
    control.append(QString("Architecture: %1").arg(ui->archLineEdit->text()) + "\n");
    control.append(QString("Replaces: %1").arg(ui->replacesLineEdit->text()) + "\n");
    control.append(QString("Conflicts: %1").arg(ui->conflictsLineEdit->text()) + "\n");
    control.append(QString("XB-Maemo-Display-Name: %1").arg(ui->maemoDisplayNameEdit->text() + "\n"));
    control.append(QString("Description: %1").arg(ui->descriptionEdit->text()) + "\n");
    control.append(QString("Depends: %1").arg(ui->dependsLineEdit->text()) + "\n");
    control.append(QString("Pre-Depends: maemo-optify-runonce") + "\n");
    control.append(QString("XB-Maemo-Flags: %1").arg(ui->maemoFlagsEdit->text()) + "\n");
    return control;
}

void MainWindow::preview()
{
    PreviewDialog *dialog = new PreviewDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setText(prepareControlFileAsString());
    dialog->show();
}
