#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"
#include <QDebug>

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()
{
    //由于全局变量getInstance() -> 直接访问IDatabase类里面的userLogin
    QString status = IDatabase::getInstance().userLogin(ui->inputUserName->text(),
                                                        ui->inputUserPassword->text());
    if(status =="loginOK")
    emit loginSuccess();
}

