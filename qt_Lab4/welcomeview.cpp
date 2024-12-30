#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>
#include <QMessageBox>

WelcomeView::WelcomeView(bool isAdmin, QWidget *parent)
    : QWidget(parent), ui(new Ui::WelcomeView) {
    ui->setupUi(this);

    // 根据权限控制按钮状态


    if (!isAdmin) {
        ui->btDoctor->setEnabled(false); // 普通医生禁用“管理医生”按钮
    }
}


WelcomeView::~WelcomeView()
{
    qDebug()<<"destroy WelcomeView";
    delete ui;
}




void WelcomeView::on_btDoctor_clicked()
{
    QMessageBox::information(this, "权限验证", "进入医生管理界面");
    emit goDoctorView();
}


void WelcomeView::on_btPatient_clicked()
{
    emit goPatientView();
}


void WelcomeView::on_btRecord_clicked()
{
    emit goRecordView();
}


void WelcomeView::on_btMedicine_clicked()
{
    emit goMedicineView();
}

