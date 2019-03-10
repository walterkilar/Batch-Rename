#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *tableModel;



    void SetupTabview()
    {
         tableModel = new QStandardItemModel();

        
         tableModel->setColumnCount(1);
         tableModel->setHeaderData(0,Qt::Horizontal,tr("File"));
         //tableModel->setHeaderData(1,Qt::Horizontal,tr("Is Register?"));

         //tableModel->sort(0,Qt::DescendingOrder);
         tableModel->setSortRole(1);

         


    }
};

#endif // MAINWINDOW_H
