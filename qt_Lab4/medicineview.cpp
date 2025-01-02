#include "medicineview.h"
#include "ui_medicineview.h"
#include "idatabase.h"
#include <QFileDialog>
#include <QMessageBox>
MedicineView::MedicineView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicineView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initMedicineModel()){
        ui->tableView->setModel(iDatabase.medicineTabModel);
        ui->tableView->setSelectionModel(iDatabase.theMedicineSelection);
    }
}

MedicineView::~MedicineView()
{
    delete ui;
}

void MedicineView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewMedicine();
    emit goMedicineEditView(currow); // 跳转到编辑界面
}

void MedicineView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchMedicine(filter);
}

void MedicineView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentMedicine();
}

void MedicineView::on_btEdit_clicked()
{
    QModelIndex curIndex = ui->tableView->currentIndex();
    emit goMedicineEditView(curIndex.row());
}

void MedicineView::on_comboBox_activated(int index)
{
    QString sortField;
    switch (index) {
    case 0:
        sortField = "CREATEDTIMESTAMP"; // 按药品名称排序
        break;
    case 1:
        sortField = "STOCK"; // 按库存数量排序
        break;
    default:
        sortField = "CREATEDTIMESTAMP"; // 默认按创建时间排序
        break;
    }
    IDatabase::getInstance().sortMedicineList(sortField, true);
}

void MedicineView::on_btExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存为CSV", "", "CSV 文件 (*.csv);;所有文件 (*.*)");
    if (!fileName.isEmpty()) {
        IDatabase::getInstance().exportMedicineData(fileName);
    }
}

void MedicineView::on_btImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "", "CSV 文件 (*.csv);;所有文件 (*.*)");
    if (!fileName.isEmpty()) {
        if (IDatabase::getInstance().importMedicineData(fileName)) {
            QMessageBox::information(this, "导入成功", "药品信息已成功导入！");


            // 刷新模型和视图
            IDatabase &iDatabase = IDatabase::getInstance();
            if (iDatabase.initMedicineModel()) {  // 重新初始化医生信息模型
                ui->tableView->setModel(iDatabase.medicineTabModel); // 绑定到tableView
                ui->tableView->reset(); // 刷新视图
            }
        } else {
            QMessageBox::warning(this, "导入失败", "导入失败，请检查文件格式！");
        }
    }
}
