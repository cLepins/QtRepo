#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent,QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    this->pTextEdit = textEdit;
    //ui->btnFindNext->setCheckable(true);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btnFindNext_clicked()
{
    QString target = ui->searchText->text();
    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();

    qDebug()<<c.position();
    int index = -1;
    if(ui->btnDown->isChecked()){

        int startPos = (c.position() >= text.length()) ? 0 : c.position();
        index = text.indexOf(target, startPos,
                             ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        qDebug()<<index;
        if(index >= 0)
        {
            c.setPosition(index);
            c.setPosition(index + target.length(),QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->btnUp->isChecked()){
        index = text.lastIndexOf(target, c.position() - 1,
                                 ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0)
        {
            c.setPosition(index + target.length());
            c.setPosition(index,QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }


    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("fidn");
        msg.setText(QString("cannotfind") + target);
        msg.exec();
    }
}


void SearchDialog::on_btnCancel_clicked()
{
    accept();
}

