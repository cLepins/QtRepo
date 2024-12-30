#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"
#include <QDebug>
#include <QMessageBox>

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

// void LoginView::on_btSignIn_clicked()
// {
//     //由于全局变量getInstance() -> 直接访问IDatabase类里面的userLogin
//     QString status = IDatabase::getInstance().userLogin(ui->inputUserName->text(),
//                                                         ui->inputUserPassword->text());
//     if(status =="loginOK")
//     emit loginSuccess();
// }


void LoginView::on_btSignIn_clicked() {
    QString username = ui->inputUserName->text();
    QString password = ui->inputUserPassword->text();


    //数据库新增：role，在userLogin()里返回result 判断是否是管理员
    QString result = IDatabase::getInstance().userLogin(username, password);

    if (result == "wrongUsername") {
        QMessageBox::warning(this, "登录失败", "用户名不存在！");
    } else if (result == "wrongPassword") {
        QMessageBox::warning(this, "登录失败", "密码错误！");
    } else if (result.startsWith("loginOK")) {
        // 登录成功，提取角色信息
        bool isAdmin = result == "loginOK:admin";
        emit goToWelcomeView(isAdmin); // 传递权限信息
    } else {
        QMessageBox::critical(this, "登录失败", "未知错误，请联系管理员！");
    }
}

