#include "recordeditview.h"
#include "ui_recordeditview.h"
#include "idatabase.h"

RecordEditView::RecordEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::RecordEditView)
{
    ui->setupUi(this);


    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().recordTabModel;


    dataMapper->setModel(IDatabase::getInstance().recordTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);


    dataMapper->addMapping(ui->dbEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbPatientName,tabModel->fieldIndex("PATIENTNAME"));
    dataMapper->addMapping(ui->dbDoctorName,tabModel->fieldIndex("DOCTORNAME"));
    dataMapper->addMapping(ui->dbDiagnosis,tabModel->fieldIndex("DIAGNOSIS"));
    dataMapper->addMapping(ui->dbMedicine,tabModel->fieldIndex("MEDICINE"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp,tabModel->fieldIndex("CREATEDTIMESTAMP"));


    dataMapper->setCurrentIndex(index);


    ui->dbEditID->setEnabled(false);
}

RecordEditView::~RecordEditView()
{
    delete ui;
}



void RecordEditView::on_pushButton_clicked() // 完成
{
    if (IDatabase::getInstance().submitRecordEdit()) {
        qDebug() << "Record information updated successfully!";
    } else {
        qDebug() << "Failed to update record information!";
    }
    emit goPreviousView(); // 返回上一界面
}

void RecordEditView::on_pushButton_2_clicked() // 取消
{
    IDatabase::getInstance().revertRecordEdit();
    emit goPreviousView();
}

