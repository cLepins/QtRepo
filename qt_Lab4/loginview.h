#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_btSignIn_clicked();

signals:
    void loginSuccess();
    void loginFailed();
    void goToWelcomeView(bool isAdmin);//当符合权限时发送信号

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
