#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    btnNums = {
                {Qt::Key_1,ui->oneButton},
               {Qt::Key_2,ui->twoButton},
               {Qt::Key_3,ui->threeButton},
               {Qt::Key_4,ui->fourButton},
               {Qt::Key_5,ui->fiveButton},
               {Qt::Key_6,ui->sixButton},
               {Qt::Key_7,ui->sevenButton},
               {Qt::Key_8,ui->eightButton},
               {Qt::Key_9,ui->nineButton}};
    for(auto btnKey : btnNums.keys())
    {
        QPushButton* button = btnNums[btnKey];
        if (button)  // 检查按钮是否为 nullptr
        {
            connect(button, &QPushButton::clicked, this, [=]() {
                if (ui->lineEdit) {  // 检查 lineEdit 是否初始化
                    ui->lineEdit->insert(button->text());  // 在 lineEdit 中插入按钮文本
                } else {
                    qDebug() << "lineEdit is null!";
                }
            });
        }
        else
        {
            qDebug() << "Button for key" << btnKey << "is null!";
        }
    }

    // btnOps = {
    //     {Qt::Key_Plus, ui->plusButton},
    //     {Qt::Key_Minus, ui->minusButton},
    //     {Qt::Key_Asterisk, ui->mutiplyButton},
    //     {Qt::Key_Slash, ui->divideButton},
    //     {Qt::Key_Equal, ui->equalButton}
    // };
    // 连接运算符按钮
    // for (auto btnKey : btnOps.keys()) {
    //     QPushButton* button = btnOps[btnKey];
    //     if (button) {
    //         connect(button, &QPushButton::clicked, this, [=]() {
    //             if (ui->lineEdit) {
    //                 ui->lineEdit->insert(button->text());
    //             } else {
    //                 qDebug() << "lineEdit is null!";
    //             }
    //         });
    //     } else {
    //         qDebug() << "Button for key" << btnKey << "is null!";
    //     }
    // }



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
    connect(ui->divideButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
    connect(ui->plusButton,SIGNAL(clicked()),this,SLOT(btnOperandClicked()));
    connect(ui->pushButton_25,SIGNAL(clicked()),this,SLOT(btnSigleOperandClicked()));
    connect(ui->pushButton_11,SIGNAL(clicked()),this,SLOT(btnSigleOperandClicked()));
    connect(ui->fenshuButton,SIGNAL(clicked()),this,SLOT(btnSigleOperandClicked()));
    connect(ui->doubleXButton,SIGNAL(clicked()),this,SLOT(btnSigleOperandClicked()));
    connect(ui->modeButton,SIGNAL(clicked()),this,SLOT(btnSigleOperandClicked()));

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
    double result = 0;
    double num1,num2;
    //有两个数字
    if(this->operands_.size() > 1 && this->opercodes_.size() > 0)
    {
        num1 = this->operands_.top().toDouble();
        this->operands_.pop();
        num2 = this->operands_.top().toDouble();
        this->operands_.pop();
        auto elem = this->opercodes_.top();
        this->opercodes_.pop();
        if(elem == "+"){
            result = num1 + num2;
        }else if(elem == "-"){
            result = num2 - num1;
        }else if(elem == "×"){
            result = num2 * num1;
        }else if(elem == "/"){
            result = num2 / num1;
        }
        this->operands_.push(QString::number(result));
        return QString::number(result);
    }
    else return this->operands_.top();
}

void MainWindow::btnOperandClicked()
{
    if(this->Edit != "")
    {
        //数字入栈
        this->operands_.push_back(this->Edit);
        this->Edit.clear();
    }

    //直接进行判断 是否有结果
    QString result = this->calculation();
    //输出结果
    ui->lineEdit->setText(result);

    if(this->operands_.size()){//数字队列不为空 符号才入栈
        QString fuhao = qobject_cast<QPushButton *>(sender())->text();
        this->opercodes_.push(fuhao);
    }
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


void MainWindow::btnSigleOperandClicked()
{
    if(ui->lineEdit->text() != "")
    {
        double result = ui->lineEdit->text().toDouble();
        QString fuhao = qobject_cast<QPushButton *>(sender())->text();
        if(fuhao == "%"){
            result /= 100.0;
        }else if(fuhao == "1/x"){
            result = 1/result;
        }else if(fuhao == "x^2"){
            result *= result;
        }
        else if(fuhao == "√"){
            result = sqrt(result);
        }
        ui->lineEdit->setText(QString::number(result));
    }
}

void MainWindow::on_equalButton_clicked()
{
    if(this->Edit != "")
    {
        //数字入栈
        this->operands_.push_back(this->Edit);
        this->Edit.clear();
    }

    //直接进行判断 是否有结果
    QString result = this->calculation();
    //输出结果
    ui->lineEdit->setText(result);
}



void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();

    // 处理数字按钮
    if (btnNums.contains(key))
    {
        QPushButton* button = btnNums[key];
        if (button)
        {
            button->animateClick();  // 模拟按钮点击
        }
    }

    if (event->key() == Qt::Key_Plus) {
        ui->plusButton->animateClick();
    } else if (event->key() == Qt::Key_Minus) {
        ui->minusButton->animateClick();
    } else if (event->key() == Qt::Key_Asterisk) {
        ui->mutiplyButton->animateClick();
    } else if (event->key() == Qt::Key_Slash) {
        ui->divideButton->animateClick();
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        ui->equalButton->animateClick();
    }
}

