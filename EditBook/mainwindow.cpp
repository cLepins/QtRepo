#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>

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

    ui->actionCopy->setEnabled(false);

    //初始化自动换行
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if(mode == QTextEdit::NoWrap ){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionLineWrap->setChecked(false);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionLineWrap->setChecked(true);
    }


    ui->actionStatusbar->setEnabled(true);
    ui->actionShowToolbar->setEnabled(true);
    //ui->actionShowLine->setEnabled(false);
    //on_actionShowLine_triggered(false);
   // connect(ui->actionShowLine,SIGNAL(triggered(bool)),ui->TextEdit,SLOT(hideLineNumberArea(bool)));
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
    SearchDialog s_dlg(this,ui->TextEdit);
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

    statusLabel.setText("length: " + QString::number(ui->TextEdit->toPlainText().length())
                        +" lines:" +
                        QString::number(ui->TextEdit->document()->lineCount()));
}


void MainWindow::on_actionleftBack_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionPaste_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_actionrightBack_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionleftBack->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionrightBack->setEnabled(b);
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid())
    {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionFontBackgroundColor_triggered()
{

}



void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid())
    {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->TextEdit->setFont(font);
    }
}


void MainWindow::on_actionLineWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if(mode == QTextEdit::NoWrap ){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionLineWrap->setChecked(true);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionLineWrap->setChecked(false);
    }
}


void MainWindow::on_actionShowToolbar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionShowToolbar->setEnabled(!visible);
}


void MainWindow::on_actionStatusbar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusbar->setEnabled(!visible);
}


void MainWindow::on_actionExit_triggered()
{
    if(this->userEditConfirmed())
    {
        exit(0);
    }

}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->TextEdit->selectAll();
}


void MainWindow::on_TextEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui->TextEdit->textCursor().position();
    QString text = ui->TextEdit->toPlainText();
    for(int i = 0;i<pos;i++)
    {
        if(text[i] == '\n'){
            ln++;
            flg = i;
        }
    }
    flg++;
    col = pos - flg;
    statusCursorLabel.setText("Ln: " + QString::number(ln+1) + " Col:" + QString::number(
                                  col + 1));
}


void MainWindow::on_actionShowLine_triggered(bool checked)
{
    ui->TextEdit->hideLineNumberArea(checked);
}


void MainWindow::on_actionBo_triggered()
{

}

