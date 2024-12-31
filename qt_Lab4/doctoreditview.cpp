#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"

DoctorEditView::DoctorEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel;

    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbEditAge, tabModel->fieldIndex("AGE"));
    dataMapper->addMapping(ui->dbEditLicense, tabModel->fieldIndex("LICENSE"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->addMapping(ui->dbEditSpecialization, tabModel->fieldIndex("SPECIALIZATION"));

    dataMapper->setCurrentIndex(index);

    ui->dbEditID->setEnabled(false);
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

void DoctorEditView::on_pushButton_clicked()//完成
{
    if (IDatabase::getInstance().submitDoctorEdit()) {
        qDebug() << "Doctor information updated successfully!";
    } else {
        qDebug() << "Failed to update doctor information!";
    }

    emit goPreviousView();
}

void DoctorEditView::on_pushButton_2_clicked()//取消
{
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}

