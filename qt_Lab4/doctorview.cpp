// doctorview.cpp
#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"
#include <QFileDialog>
#include <QMessageBox>

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    // 初始化界面和数据库交互
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initDoctorModel()) {
        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->setAlternatingRowColors(true);
    }
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btAdd_clicked()
{
    qDebug()<<"Nana i llloveee you";
    int curRow = IDatabase::getInstance().addNewDoctor();
    emit goDoctorEditView(curRow);
}

void DoctorView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchDoctor(filter);
}

void DoctorView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentDoctor();
}

void DoctorView::on_btEdit_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (currentIndex.isValid()) {
        emit goDoctorEditView(currentIndex.row());
    }
}

void DoctorView::on_comboBox_activated(int index)
{
    QString sortField;
    switch (index) {
    case 0:
        sortField = "CREATEDTIMESTAMP"; // 按时间排序
        break;
    case 1:
        sortField = "AGE"; // 按年龄排序
        break;
    default:
        sortField = "CREATEDTIMESTAMP"; // 默认按时间排序
        break;
    }

    if (IDatabase::getInstance().sortDoctorList(sortField, true)) {
        IDatabase &iDatabase = IDatabase::getInstance();

        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->reset();
    } else {
        qDebug() << "Sorting failed!";
    }
}

void DoctorView::on_btImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "", "CSV 文件 (*.csv);;所有文件 (*.*)");

    if (!fileName.isEmpty()) {
        if (IDatabase::getInstance().importDoctorData(fileName)) {
            QMessageBox::information(this, "导入成功", "医生信息已成功导入！");

            // 刷新模型和视图
            IDatabase &iDatabase = IDatabase::getInstance();
            if (iDatabase.initDoctorModel()) {  // 重新初始化医生信息模型
                ui->tableView->setModel(iDatabase.doctorTabModel); // 绑定到tableView
                ui->tableView->reset(); // 刷新视图
            }
        } else {
            QMessageBox::warning(this, "导入失败", "导入失败，请检查文件格式！");
        }
    }
}


