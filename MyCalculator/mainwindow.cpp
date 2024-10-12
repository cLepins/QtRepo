#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->oneButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->twoButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->threeButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->fourButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->fiveButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->sixButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->sevenButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->eightButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->nineButton,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->mutiplyButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
    connect(ui->minusButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
    connect(ui->delButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
    connect(ui->plusButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::btnNumClicked()
{
    if(this->Edit == "0")
        this->Edit.clear();
    this->Edit += qobject_cast<QPushButton *>(sender())->text();
    ui->lineEdit->setText(this->Edit);
}

QString MainWindow::calculation()
{
    //计算
    double num1,num2;
    QString res;
    if(this->operands_.size() > 1 && this->opercodes_.size() > 0)
    {
        num1 = this->operands_.top().toDouble();
        this->operands_.pop();
        num2 = this->operands_.top().toDouble();
        this->operands_.pop();
    }
    return res;
}

void MainWindow::btnOperandClicked()
{
    QString fuhao = qobject_cast<QPushButton *>(sender())->text();
    if(this->Edit != "")
    {
        this->operands_.push_back(this->Edit);
        this->Edit.clear();
        this->opercodes_.push(fuhao);
    }

    //点击了一个操作符
    //判断操作符栈 是否有操作符
    //有则计算
    QString result = this->calculation();

}




void MainWindow::on_mutiplyButton_clicked()
{
    if(this->Edit != "")
    {
        this->Edit.clear();
        ui->lineEdit->setText(this->Edit);
    }
}


void MainWindow::on_minusButton_clicked()
{
    this->Edit += '-';
    ui->lineEdit->setText(this->Edit);
}


void MainWindow::on_plusButton_clicked()
{


}


void MainWindow::on_divideButton_clicked()
{
    this->Edit += '/';
    ui->lineEdit->setText(this->Edit);
}

void MainWindow::on_equalButton_clicked()
{

}



void MainWindow::on_delButton_clicked()
{
    this->Edit.chop(1);
    ui->lineEdit->setText(this->Edit);
}


void MainWindow::on_clearButton_clicked()
{
    this->Edit.clear();
    ui->lineEdit->setText(this->Edit);
}


void MainWindow::on_CeButton_clicked()
{
    this->Edit.clear();
    ui->lineEdit->setText(this->Edit);
}


void MainWindow::on_modeButton_clicked()
{
    this->Edit += '%';
    ui->lineEdit->setText(this->Edit);
}

//一个数字只能有一个dot
void MainWindow::on_dotButton_clicked()
{

    if(!ui->lineEdit->text().contains('.'))
    {
        this->Edit += '.';
        ui->lineEdit->setText(this->Edit);
    }
}


void MainWindow::on_zeroButton_clicked()
{
    if(this->Edit == "0")
        this->Edit.clear();
    this->Edit += '0';
    ui->lineEdit->setText(this->Edit);
}

void MainWindow::on_fenshuButton_clicked()
{
    this->Edit += "^-1";
    ui->lineEdit->setText(this->Edit);
}


void MainWindow::on_doubleXButton_clicked()
{
    this->Edit += "^2";
    ui->lineEdit->setText(this->Edit);
}



