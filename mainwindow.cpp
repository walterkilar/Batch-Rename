#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupTabview();

    ui->tableView->setModel(tableModel);
    ui->tableView->setColumnWidth(0,650);
    //ui->tableView->setColumnWidth(1,180);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->hide();

    //ui->le_Version->setText(getCurDay());
    ui->le_Before->setText(tr("File_"));

    setWindowState(Qt::WindowMaximized);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog::Options options;
    QString openFilesPath;
    QString selectedFilter;
    QStringList files = QFileDialog::getOpenFileNames(
                                this, tr("QFileDialog::getOpenFileNames()"),
                                openFilesPath,
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (files.count()) {
         for(QStringList::Iterator it=files.begin();it!=files.end();it++)
         {
             QString strFileName = *it;
             QStandardItem* item1 = new QStandardItem(strFileName);
             //QStandardItem* item2 = new QStandardItem(tr("0"));
             QList<QStandardItem*> item;
             item << item1 ;//<< item2;
             tableModel->appendRow(item);
         }
    }
}

void MainWindow::on_pushButton_clicked()
{
    int rowCount = tableModel->rowCount();

    if(0 == rowCount) {
        QMessageBox::information(this,"Warning","Please select files first!",QMessageBox::Ok);
        return;
    }

    QString fBefore=ui->le_Before->text();

    if(0 == fBefore.length()){
        QMessageBox::information(this,"Warning","Please input file before",QMessageBox::Ok);
        return;
    }

    QString n1 = ui->le_Before->text();
    bool bSuccess=true;

    for(int i=0;i<rowCount;i++){
        QModelIndex index0 = tableModel->index(i,0);
        QString real_fileName = tableModel->data(index0).toString();

        QFileInfo fileInfo(real_fileName);
        QString filePath = fileInfo.absoluteDir().absolutePath();
        QString ext = fileInfo.suffix();
        QString newFileName = QString("%1%2.%3").arg(n1,QString::number(i+1,10),ext);
        QString fullPath = QString("%1%2%3").arg(filePath,QDir::separator(),newFileName);

        //QMessageBox::information(this,"Warning",fullPath,QMessageBox::Ok);
        bSuccess = QFile::rename(real_fileName,fullPath);
    }

    if(bSuccess)
        QMessageBox::information(this,"Warning","rename success!",QMessageBox::Ok);
    else
        QMessageBox::information(this,"Warning","rename faile!some wrong occured!",QMessageBox::Ok);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
