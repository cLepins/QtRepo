#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length: " + QString::number(0)+" lines"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("ln: " + QString::number(0)+" lines"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("lzx"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    SearchDialog s_dlg;
    s_dlg.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog r_dlg;
    r_dlg.exec();
}


bool MainWindow::userEditConfirmed()
{
    if(EditChanged)
    {
        QString path = (FILEPATH != "") ? FILEPATH : "无标题.txt";
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("waiting..");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("changed save?\n") + "\"" + path +"\"?");
        msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        int r = msg.exec();
        switch(r)
        {
        case QMessageBox::Yes:
            this->on_actionSaveAs_triggered();
            break;
        case QMessageBox::No:
            EditChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }

    }
    return true;
}



void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存文件",
                                                    ".",tr("Text files(*.txt)"));

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"nofile","can not open file");
        return;
    }
    FILEPATH = filename;
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
    this->setWindowTitle(QFileInfo(FILEPATH).absoluteFilePath());

    EditChanged = false;
}


void MainWindow::on_actionSave_triggered()
{

    if(FILEPATH == "")
    {
        QMessageBox::warning(this,"nofile","can not open file");
        QString filename = QFileDialog::getOpenFileName(this,
                                                        "保存文件",".",tr("Text files(*.txt)"));

        QFile file2(filename);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"nofile","can not open file");
            return ;
        }
        file2.close();
        FILEPATH = filename;
    }

    QFile file(FILEPATH);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"nofile","can not open file");
        QString filename = QFileDialog::getOpenFileName(this,
                                    "保存文件",".",tr("Text files(*.txt)"));

        QFile file2(filename);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"nofile","can not open file");
            return ;
        }
        FILEPATH = filename;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(FILEPATH).absoluteFilePath());
    EditChanged = false;
}


void MainWindow::on_actionNew_triggered()
{
    if(!userEditConfirmed())
        return;

    FILEPATH = "";

    ui->TextEdit->clear();
    this->setWindowTitle("新建文本");
    EditChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed())
    {
        return;
    }
    QString filePath = QFileDialog::getOpenFileName(this,"打开文件",".txt");
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::WriteOnly))
    {
        QMessageBox::warning(this,"warin","can not open file correctly");
        return;
    }
    this->FILEPATH = filePath;
    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();
    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_TextEdit_textChanged()
{
    if(!EditChanged){
        this->setWindowTitle("*" + this->windowTitle());
        EditChanged = true;
    }
}

