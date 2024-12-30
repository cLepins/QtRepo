#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug()<<"goLoginView";
    loginView = new LoginView(this);

    pushWidgetToStackView(loginView);

    //登录成功则进入欢迎界面
    //connect(loginView,SIGNAL(loginSuccess()),this, SLOT(goWelcomeView()));
    connect(loginView, &LoginView::goToWelcomeView, this, &MasterView::goWelcomeView);
}

// void MasterView::goWelcomeView()
// {
//     qDebug()<<"goWelcomeView";
//     welcomeView = new WelcomeView(this);
//     pushWidgetToStackView(welcomeView);

//     connect(welcomeView,SIGNAL(goDoctorView()),this, SLOT(goDoctorView()));
//     connect(welcomeView,SIGNAL(goPatientView()),this, SLOT(goPatientView()));
//     //connect(welcomeView,SIGNAL(goDepartmentView()),this, SLOT(goDepartmentView()));
//     connect(welcomeView,SIGNAL(goMedicineView()),this,SLOT(goMedicineView()));
// }


void MasterView::goWelcomeView(bool isAdmin) {
    welcomeView = new WelcomeView(isAdmin, this);
    // pushWidgetToStackView(welcomeView);
    qDebug()<<"goWelcomeView";
    pushWidgetToStackView(welcomeView);

    connect(welcomeView,SIGNAL(goDoctorView()),this, SLOT(goDoctorView()));
    connect(welcomeView,SIGNAL(goPatientView()),this, SLOT(goPatientView()));
    //connect(welcomeView,SIGNAL(goDepartmentView()),this, SLOT(goDepartmentView()));
    connect(welcomeView,SIGNAL(goMedicineView()),this,SLOT(goMedicineView()));
}


void MasterView::goDoctorView()
{
    qDebug()<<"goDoctorView";
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);
}

void MasterView::goMedicineView()
{
    qDebug()<<"goMedicineView";
    medicineView = new MedicineView(this);
    pushWidgetToStackView(medicineView);
}



void MasterView::goPatientEditView(int rowNo)
{
    qDebug()<<"goPatientEditView";
    patientEditView = new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);
    //把编辑页面的返回前页面信号和master里面的返回前页面函数关联起来
    //这个信号将在patientEditView里面发送，master作为收到信号的主体，收到信号就执行这个函数
    connect(patientEditView,SIGNAL(goPreviousView()),this, SLOT(goPreviousView()));
}

void MasterView::goPatientView()
{
    qDebug()<<"goPatientView";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);
    //关联两个信号，在PatientView 里面发送信号，一旦发送，则调用goPatientEditView这个函数
    connect(patientView,SIGNAL(goPatientEditView(int)),this, SLOT(goPatientEditView(int)));
}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();

    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count -1);
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if(count>1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);
    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    if(title == "欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);

    }else
        ui->btLogout->setEnabled(false);
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

