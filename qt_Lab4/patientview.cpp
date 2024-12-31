#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"
#include <QDebug>

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


void PatientView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void PatientView::on_btEdit_clicked() // 修改按钮点击事件
{
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex(); // 获取当前选中行
    int curRow = curIndex.row();

    if (curRow >= 0) {
        emit goPatientEditView(curRow); // 跳转到编辑界面，传递当前行号
    } else {
        qDebug() << "No patient selected for editing!";
    }
}


void PatientView::on_comboBox_activated(int index)
{
    QString sortField;
    switch (index) {
    case 0:
        qDebug()<<"i love nana";
        sortField = "CREATEDTIMESTAMP"; // 数据库字段名
        break;
    case 1:
        qDebug()<<"forever";
        sortField = "AGE"; // 数据库字段名
        break;
    default:
        sortField = "CREATEDTIMESTAMP";
        break;
    }
    if (IDatabase::getInstance().sortPatientList(sortField, true)) {
        IDatabase &iDatabase = IDatabase::getInstance();

        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->reset();
    } else {
        qDebug() << "Sorting failed!";
    }
}




