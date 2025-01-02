#include "medicineeditview.h"
#include "ui_medicineeditview.h"
#include "idatabase.h"

MedicineEditView::MedicineEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::MedicineEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().medicineTabModel;

    dataMapper->setModel(IDatabase::getInstance().medicineTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditDosage, tabModel->fieldIndex("DOSAGE"));
    dataMapper->addMapping(ui->dbEditStock, tabModel->fieldIndex("STOCK"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);

    ui->dbEditID->setEnabled(false);
}

MedicineEditView::~MedicineEditView()
{
    delete ui;
}

void MedicineEditView::on_pushButton_clicked() // 完成
{
    if (IDatabase::getInstance().submitMedicineEdit()) {
        qDebug() << "Medicine information updated successfully!";
    } else {
        qDebug() << "Failed to update medicine information!";
    }
    emit goPreviousView(); // 返回上一界面
}

void MedicineEditView::on_pushButton_2_clicked() // 取消
{
    IDatabase::getInstance().revertMedicineEdit();
    emit goPreviousView();
}
