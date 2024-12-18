#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopButton_clicked()
{
    static bool started = false;
    started = !started;
    if(started){
        ui->startStopButton->setText("停止服务器");
        logMessages("服务器已启动");
    }else{
        ui->startStopButton->setText( "启动服务器");
        logMessages("服务器已停止");
    }
}

void MainWindow::logMessages(const QString &msg)
{
    ui->logEditer->append(msg);

}

