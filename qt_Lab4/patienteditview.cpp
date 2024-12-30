#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"


PatientEditView::PatientEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;


    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);


    dataMapper->addMapping(ui->dbEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp,tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->addMapping(ui->dbEditAge,tabModel->fieldIndex("Age"));

    dataMapper->setCurrentIndex(index);


    ui->dbEditID->setEnabled(false);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()//这是完成按钮
{
    if (IDatabase::getInstance().submitPatientEdit()) {
        qDebug() << "Patient information updated successfully!";
    } else {
        qDebug() << "Failed to update patient information!";
    }

    emit goPreviousView(); // 返回上一界面
}


void PatientEditView::on_pushButton_2_clicked()//这是取消按钮
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}

