#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thresholdsetupdialog.h"
#include "databackupdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSetup_triggered()
{
    ThresholdSetupDialog mThresholdDialog;
    mThresholdDialog.setModal(true);
    mThresholdDialog.exec();
    mThresholdDialog.setWindowTitle("Setup Threshold");
    mThresholdDialog.initThresholds();

}

void MainWindow::on_actionBackup_triggered()
{
    DataBackupDialog mDataBackupDialog;
    mDataBackupDialog.setModal(true);
    mDataBackupDialog.exec();
    mDataBackupDialog.setWindowTitle("Data Backup");
}
